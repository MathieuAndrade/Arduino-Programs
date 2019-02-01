#include <DmxSimple.h>

int DMX = 3;

void setup() 
{
  Serial.begin(115200);
  pinMode(DMX, OUTPUT);
}

void loop() {
  int received;                                                  // Variable servant à récupérer
                                                                 // les données reçues
  if (Serial.available()>0) 
    { 
      received = Serial.read();
      analogWrite(DMX, received);
  }
}
