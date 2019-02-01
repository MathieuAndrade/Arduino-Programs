#include <RCSwitch.h>
 
RCSwitch mySwitch = RCSwitch();
 
unsigned long Tele_Salon_ON = 1381717;
unsigned long Tele_Salon_OFF = 1381716;
 
unsigned long Tele_Chambre_ON = 1394005;
unsigned long Tele_Chambre_OFF = 1394004;
 
void setup() {
  Serial.begin(9600);
  // Emetteur connecté au pin #10 de l'Arduino  
  mySwitch.enableTransmit(10);
  Serial.println("init ");
}
 
void loop() {
  Serial.print("allume ");
  mySwitch.send(Tele_Salon_ON, 24);
  delay(1000);  
  Serial.println("eteint ");
  mySwitch.send(Tele_Salon_OFF, 24);
  delay(1000);  
  Serial.println("allume ");
  mySwitch.send(Tele_Chambre_ON, 24);
  delay(1000);  
  Serial.println("eteint ");
  mySwitch.send(Tele_Chambre_OFF, 24);
  delay(5000);
}
