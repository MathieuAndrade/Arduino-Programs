// Ces deux bibliothèques sont indispensables pour le shield
#include <SPI.h>
#include <Ethernet.h>

// L'adresse MAC du shield
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
// L'adresse IP que prendra le shield
IPAddress ip(192,168,1,40);

// Initialise notre serveur
// Ce dernier écoutera sur le port 4200
EthernetServer serveur(4200);

char carlu = 0;

void setup()
{
  // On démarre la voie série pour déboguer
  Serial.begin(9600);

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
  Serial.println("Pret !");
  printIPAddress();
}

void loop()
{
  // Regarde si un client est connecté et attend une réponse
  EthernetClient client = serveur.available();
  if (client) {
    // Quelqu'un est connecté !
    Serial.println("Un client est connecte!");
    // On fait notre en-tetecarlu = client.read();
    carlu = client.read();
    Serial.println(carlu);
    if (carlu == 'C')
    {
      Serial.println("Envoi de la reponse");
      client.print('ok');
    }
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
