#include "Ethernet.h"
#include "SPI.h"

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xA5, 0x7E };
IPAddress ip(192,168,0,27);
EthernetServer serveur(4200);

void setup() {
	Serial.Begin(9600);
	char erreur = 0;
	erreur = Ethernet.begin(mac);

	if (erreur == 0) 
	{
    Serial.println("Parametrage avec ip fixe...");
    // si une erreur a eu lieu cela signifie que l'attribution DHCP
    // ne fonctionne pas. On initialise donc en forçant une IP
    Ethernet.begin(mac, ip);
    }
  Serial.println("Init...");
  // Donne une seconde au shield pour s'initialiser
  delay(1000);
  // On lance le serveur
  serveur.begin();
  Serial.print("Pret !");
  printIPAddress();
}

void loop() {

}

void printIPAddress()
{
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }

  Serial.println();
}

