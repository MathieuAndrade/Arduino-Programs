// Ces deux bibliothèques sont indispensables pour le shield
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
IPAddress ip(192,168,1,16);
EthernetServer serveur(4200);
boolean reading;

void setup()
{
  // On démarre la voie série pour déboguer
  Serial.begin(9600);
  reading = false;
  char erreur = 0;
  // On démarre le shield Ethernet SANS adresse ip (donc donnée via DHCP)
  erreur = Ethernet.begin(mac);

  if (erreur == 0) {
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

void loop()
{
  // Regarde si un client est connecté et attend une réponse
  EthernetClient client = serveur.available();
  if (client) {
    char c = 0;
    c = client.read();
    Serial.println(c);
     if(reading && c == ' '){reading = false;}
                if(c == '?'){reading = true;}
                if(reading){
                    
                    switch(c){
                        case 'value=1':
                            Serial.println("on allume");
                            break;
                        case 'value=0':
                            Serial.println("on eteint");
                            break;
                    }
                }
    client.println("HTTP/1.1 200 OK");
    delay(10);
    // Ferme la connexion avec le client
    client.stop();
  }
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
