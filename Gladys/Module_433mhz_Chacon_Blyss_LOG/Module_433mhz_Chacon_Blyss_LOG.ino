// include librairie
#include <RCSwitch.h>
#include <ArduinoJson.h>
RCSwitch mySwitch = RCSwitch();

/**
 * Blyss protocol spoofer
 */

/* Transmitter pinmap */
const byte RF_TX_VCC = 5;
const byte RF_TX_SIG = 4;
const byte RF_TX_GND = 3;

/* -------------------------------------------------------- */
/* ----                Blyss Spoofer API               ---- */
/* -------------------------------------------------------- */

/* Time constants */
const unsigned long H_TIME = 2400; // Header delay
const unsigned long T_TIME = 400;  // 1/3 frame delay
const byte nb_frames = 13; // Numbers of frames per command

/* RF signal usage macro */
#define SIG_HIGH() digitalWrite(RF_TX_SIG, HIGH)
#define SIG_LOW() digitalWrite(RF_TX_SIG, LOW)

/** "Rolling code" (normally avoid frame spoofing) */
byte RF_ROLLING_CODE[] = {
  0x98, 0xDA, 0x1E, 0xE6, 0x67
};

/** Transmission channels and status enumeration */
enum {
  OFF, ON, 
  CH_1 = 8, CH_2 = 4, CH_3 = 2, CH_4 = 1, CH_5 = 3, CH_ALL = 0,
  CH_A = 0, CH_B = 1, CH_C = 2, CH_D = 3
};

/**
 * Send header over RF
 */
inline void send_header(void) {
  SIG_HIGH();
  delayMicroseconds(H_TIME);
}

/**
 * Send footer over RF
 */
inline void send_footer(void) {
  SIG_LOW();
  delay(H_TIME * 10 / 1000);
}

/**
 * Send logical "1" over RF
 */
inline void send_one(void) {
  SIG_LOW();
  delayMicroseconds(T_TIME);
  SIG_HIGH();
  delayMicroseconds(T_TIME * 2);
}

/**
 * Send logical "0" over RF
 */
inline void send_zero(void) {
  SIG_LOW();
  delayMicroseconds(T_TIME * 2);
  SIG_HIGH();
  delayMicroseconds(T_TIME);
}

/**
 * Send a bits quarter (4 bits = MSB from 8 bits value) over RF
 *
 * @param data Source data to process and sent
 */
inline void send_quarter_MSB(byte data) {
  (bitRead(data, 7)) ? send_one() : send_zero();
  (bitRead(data, 6)) ? send_one() : send_zero();
  (bitRead(data, 5)) ? send_one() : send_zero();
  (bitRead(data, 4)) ? send_one() : send_zero();
}

/**
 * Send a bits quarter (4 bits = LSB from 8 bits value) over RF
 *
 * @param data Source data to process and sent
 */
inline void send_quarter_LSB(byte data) {
  (bitRead(data, 3)) ? send_one() : send_zero();
  (bitRead(data, 2)) ? send_one() : send_zero();
  (bitRead(data, 1)) ? send_one() : send_zero();
  (bitRead(data, 0)) ? send_one() : send_zero();
}

/**
 * Generate next valid token for RF transmission
 *
 * @param data Pointer to a RF frame-data buffer
 */
void generate_token(byte *data) {
  static byte last_token = 0x7D;
  data[5] = (data[5] & 0xF0) | ((last_token & 0xF0) >> 4);
  data[6] = (last_token & 0x0F) << 4;
  last_token += 10;
}

/**
 * Generate next valid rolling code for RF transmission
 *
 * @param data Pointer to a RF frame-data buffer
 */
void generate_rolling_code(byte *data) {
  static byte i = 0;
  data[4] = (data[4] & 0xF0) | ((RF_ROLLING_CODE[i] & 0xF0) >> 4);
  data[5] = (data[5] & 0x0F) |(RF_ROLLING_CODE[i] & 0x0F) << 4;
  if(++i >= sizeof(RF_ROLLING_CODE)) i = 0;
}

/**
 * Change the status (ON / OFF) of the transmitter
 *
 * @param data Pointer to a RF frame-data buffer
 * @param status Status to use (ON or OFF)
 */
inline void set_status(byte *data, byte status) {
  if(!status) data[4] = (data[4] & 0x0F) | 0x10;
  else data[4] &= 0x0F;
}

/**
 * Send a complete frame-data buffer over RF
 *
 * @param data Pointer to a RF frame-data buffer
 */
void send_buffer(byte *data) {
  send_header();
  for(byte i = 0; i < 6; ++i) {
    send_quarter_MSB(data[i]);
    send_quarter_LSB(data[i]);
  }
  send_quarter_MSB(data[6]);
  send_footer();
}

/**
 * Send a complete frame-data buffer n times to be hooked by the target receiver
 *
 * @param data Pointer to a RF frame-data buffer
 */
inline void send_command(byte *data) {
  for(byte i = 0; i < nb_frames; ++i)
    send_buffer(data);
}

/**
 * Copy a RF key ID into a frame-data buffer
 *
 * @param data Pointer to a RF frame-data buffer
 * @param key Pointer to a RF key-data buffer
 * @param overwrite Set to true if you want to overwrite channel data and use data from key buffer
 */
inline void set_key(byte *data, byte *key, byte overwrite) {
  data[0] = 0xFE;
  if(overwrite)
    data[1] = key[0];
  else
    data[1] = (data[1] & 0xF0) | (key[0] & 0x0F);
  data[2] = key[1];
  if(overwrite)
    data[3] = key[2];
  else
    data[3] = (data[3] & 0x0F) | (key[2] & 0xF0);
}

/**
 * Set the target sub-channel of the transmitter 
 *
 * @param data Pointer to a RF frame-data buffer
 * @param channel Target channel
 */
inline void set_channel(byte *data, byte channel) {
  data[3] = (data[3] & 0xF0) | (channel & 0x0F);
}

/**
 * Set the target global channel of the transmitter
 *
 * @param data Pointer to a RF frame-data buffer
 * @param channel Target channel
 */
inline void set_global_channel(byte *data, byte channel) {
  data[1] = (data[1] & 0x0F) | ((channel << 4) & 0xF0);
}

/* -------------------------------------------------------- */
/* ----                  RF function                   ---- */
/* -------------------------------------------------------- */

void SendRadioCode(long code) {
  mySwitch.send(code, 24);
  Serial.print("\"Commande Chacon envoyée\"\n"); 
  }

// Serial buffer
String command = "";

// End of command marker
char endMarker = '%';

/*
* Execute the right function
*/
void executeFunction(String json_data) {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& v = jsonBuffer.parseObject(json_data);
  //on décompose la chaine de cartère
  if ( v["function_name"] == String("SendRadioCode") ) {
    chaconOrBlyss(v["code"]);
    } 
 }

/**
* This function is automatically called when data is received on serial port
*/
void serialEvent() {
  //lit toutes les données (vide le buffer de réception)
  char last_readed_char = Serial.read();
  if ( last_readed_char == endMarker ) {
    Serial.print("\"Commande décodée\"\n");
    delay(1000);
    executeFunction(command);  
    command = "";
    } else {
      command += last_readed_char;
      }
  }


/* -------------------------------------------------------- */
/* ----                   Progamme                     ---- */
/* -------------------------------------------------------- */


byte RF_KEY1[] = {
  0x03, 0x09, 0x48   //Clé RF de la premier bouton
};
long code_1 = 0x030948; //Variable bouton 1

byte RF_KEY2[] = {
  0x03, 0x09, 0x44  //Clé RF de la deusieme bouton
};
long code_2 = 0x030944;  //Variable bouton 2

byte RF_KEY3[] = {
  0x03, 0x09, 0x42  //Clé RF de la troisieme bouton
};
long code_3 = 0x030942;  //Variable bouton 3

/** Frame-data buffer (key ID + status flag + rolling code + token */
byte RF_BUFFER[7];

/** setup() */
void setup() {

  /* Transmitter pins as output */
  pinMode(RF_TX_VCC, OUTPUT);
  pinMode(RF_TX_SIG, OUTPUT);
  pinMode(RF_TX_GND, OUTPUT);

  /* Fast powerring tips */
  digitalWrite(RF_TX_VCC, HIGH);
  digitalWrite(RF_TX_GND, LOW);

  Serial.begin(9600);

  mySwitch.enableTransmit(RF_TX_SIG);
  mySwitch.enableReceive(12);
  
  // Optional set pulse length.
  mySwitch.setPulseLength(310);
  
  // Optional set protocol (default is 1, will work for most outlets)
  mySwitch.setProtocol(1);
  
  // Optional set number of transmission repetitions.
  mySwitch.setRepeatTransmit(15);
   
  /* Kill RF signal for now */
  SIG_LOW();

  /* Copy key Id to spoof into frame-data buffer */
  //set_key(RF_BUFFER, RF_KEY, true);
  
  /* Change channel to CH_ALL (broadcast) */
  //set_global_channel(RF_BUFFER, CH_D); 
  set_channel(RF_BUFFER, CH_ALL);
}

/** loop() */
void loop() {
    if (mySwitch.available()) {
    int value = mySwitch.getReceivedValue();
    
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
      Serial.print("{\"action\":\"received\",\"value\":");
      Serial.print( mySwitch.getReceivedValue() );
      Serial.println("}");
    }
    delay(200); 
    mySwitch.resetAvailable();
  }
}

//Test du protocole a utiliser
void chaconOrBlyss(long code){

  Serial.print("\"Commande Blyss ou Chacon\"\n");  

  if( code == code_1){                                           // Si le code reçu correspond a celui de la première touche a l'état bas ou a l'état haut
    set_key(RF_BUFFER, RF_KEY1, true);                           // Alors on utilise la clé RF de le première touche
    Serial.print("\"Commande Blyss 1\"\n");  
    blyss();                                                     // Puis on fait appel a la fonction qui utilise le protocol blyss
  } 
  else if( code == code_2){                                      // Sinon si le code reçu correspond a celui de la seconde touche a l'état bas ou a l'état haut
    set_key(RF_BUFFER, RF_KEY2, true);                           // Alors on utilise la clé RF de le seconde touche
    Serial.print("\"Commande Blyss 2\"\n");  
    blyss();                                                     // Puis on fait appel a la fonction qui utilise le protocol blyss
  }
  else if( code == code_3){                                      // Sinon si le code reçu correspond a celui de la troisième touche a l'état bas ou a l'état haut
    set_key(RF_BUFFER, RF_KEY3, true);                           // Alors on utilise la clé RF de le troisième touche
    Serial.print("\"Commande Blyss 3\"\n");  
    blyss();                                                     // Puis on fait appel a la fonction qui utilise le protocol blyss
  }
  else {
    Serial.print("\"Commande Chacon\"\n");  
    SendRadioCode(code);}                                    // Sinon si il ne correspond a aucun d'entre eux on fait appel a la fonction qui utilise le protocol chacon
}

//Protocole Blyss 
void blyss(){
    /* Virtual switch state */
  static byte state = false;
  digitalWrite(13, state);

  /* Apply switch state to frame-data buffer */
  set_status(RF_BUFFER, state);

  /* Insert rolling code and token into frame-data buffer */
  generate_rolling_code(RF_BUFFER);
  generate_token(RF_BUFFER);

  /* Output switch state for debug */
  Serial.print("\"State\"\n");
  Serial.print(state ? "\"ON\"\n" : "\"OFF\"\n");
  
  /* Send RF frame */
  send_command(RF_BUFFER);

  /* Wait some time (don't want to blow-up my ligth bulb !) */
  delay(1000);

  /* Toggle virtual switch state */
  state = !state;
  Serial.print("\"Commande Blyss envoyée\"\n"); 
 }
