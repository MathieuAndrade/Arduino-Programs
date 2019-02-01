#include <SPI.h>
#include <Ethernet.h>

// L'adresse MAC du shield
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
// L'adresse IP que prendra le shield
IPAddress ip(192,168,1,16);
// L'objet qui nous servira à la communication
EthernetClient client;
// Le serveur à interroger
char serveur[] = "eskimon.fr";

char carlu = 0; // pour lire les caractères
long derniereRequete = 0; // moment de la dernière requête
const long updateInterval = 10000; // temps minimum entre deux requêtes
bool etaitConnecte = false; // mémorise l'état de la connexion entre deux tours de loop

void setup() {
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
  Serial.println("Pret !");
  printIPAddress();
   
}


void loop() {
  // on lit les caracteres s'il y en a de disponibles
  if(client.available()) {
    carlu = client.read();
    Serial.print(carlu);
  }
 
  // SI on etait connecté au tour précédent
  // ET que maintenant on est plus connecté
  // ALORS on ferme la connexion
  if (etaitConnecte && !client.connected()) {
    Serial.println();
    Serial.println("Deconnexion !");
    // On ferme le client
    client.stop();
  }
 
  // Si on est déconnecté
  // et que cela fait plus de xx secondes qu'on a pas fait de requete
  if(!client.connected() && ((millis() - derniereRequete) > updateInterval)) {
    requete();
  }
 
  // enregistre l'etat de la connexion (ouvert ou fermé)
  etaitConnecte = client.connected();
}

void requete() {
  // On connecte notre Arduino sur "perdu.com" et le port 80 (defaut pour l'http)
  char erreur = client.connect(serveur, 80);
 
  if(erreur == 1) {
      // Pas d'erreur ? on continu !
      Serial.println("Connexion OK, envoi en cours...");
 
      // On construit l'en-tete de la requete
      client.println("GET /public/arduino.php");
      client.println(" HTTP/1.1");
      client.println("Host: eskimon.fr");
      client.println("Connection: close");
      client.println();
 
      // On enregistre le moment d'envoi de la dernière requete
      derniereRequete = millis();
  } else {
    // La connexion a échoué :(
    // On ferme notre client
    client.stop();
    // On avertit l'utilisateur
    Serial.println("Echec de la connexion");
    switch(erreur) {
      case(-1):
        Serial.println("Time out");
        break;
      case(-2):
        Serial.println("Serveur invalide");
        break;
      case(-3):
        Serial.println("Tronque");
        break;
      case(-4):
        Serial.println("Reponse invalide");
        break;
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
