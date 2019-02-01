#include <ArduinoJson.h>

String command = "";
char endMarker = '%';

int grand_portail = 2;
int petit_portail = 3;

int devicetype_grand_portail = 115; 
int devicetype_petit_portail = 116; 

void setup() {
  Serial.begin(9600);
  pinMode(grand_portail, OUTPUT);
  pinMode(petit_portail, OUTPUT);
}

void loop() {}

void devicetypeGrandPortail (int code) {
   if ( code == 1 || code == 0) {
      digitalWrite(grand_portail, HIGH);
      delay(1000);
      digitalWrite(grand_portail, LOW);
     } 
}

void devicetypePetitPortail (int code) {
   if ( code == 1 || code == 0) {
      digitalWrite(petit_portail, HIGH);
      delay(1000);
      digitalWrite(petit_portail, LOW);
     } 
}

void executeFunction(String json_data) {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json_received = jsonBuffer.parseObject(json_data);
  //on décompose la chaine de cartère
  if ( json_received["deviceType"] == int(devicetype_grand_portail) ) {
    devicetypeGrandPortail(json_received["value"]);
  } 
  else if (json_received["deviceType"] == int(devicetype_petit_portail) ) {
    devicetypePetitPortail(json_received["value"]);
  }
}

void serialEvent() {
    //lit toutes les données (vide le buffer de réception)
    char last_readed_char = Serial.read();
    if ( last_readed_char == endMarker ) {
      executeFunction(command);
      command = "";
    } else {
      command += last_readed_char;
    }
}


