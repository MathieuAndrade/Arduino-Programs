#include <ArduinoJson.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void SendRadioCode(long code) {
   mySwitch.send(code, 24);
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
    SendRadioCode(v["code"]);
  } 
}

/**
 * This function is automatically called when data is received on serial port
 */
void serialEvent() {
    //lit toutes les données (vide le buffer de réception)
    char last_readed_char = Serial.read();
    Serial.print("\"Commande reçu\"\n"); 
    if ( last_readed_char == endMarker ) {
      executeFunction(command);
      command = "";
    } else {
      command += last_readed_char;
    }
}


void setup() {
  
  // Open serial communications and wait for port to open: 
  Serial.begin(9600);

  // Receiver is connected on Arduino Pin #2
  mySwitch.enableReceive(0);

  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);
  
  // Optional set pulse length.
  mySwitch.setPulseLength(310);
  
  // Optional set protocol (default is 1, will work for most outlets)
  mySwitch.setProtocol(1);
  
  // Optional set number of transmission repetitions.
  mySwitch.setRepeatTransmit(15);

  delay(1000);
}

void loop() {
  

}
