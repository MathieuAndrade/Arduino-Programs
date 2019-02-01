// Ces deux bibliothèques sont indispensables pour le shield
#include <SPI.h>
#include <Ethernet.h>

// L'adresse MAC du shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xA5, 0x7E };
// L'adresse IP que prendra le shield
IPAddress ip(192,168,0,143);

// Initialise notre serveur
// Ce dernier écoutera sur le port 4200
EthernetServer serveur(4200);

char *url = (char *)malloc(100); // L'url recu à stocker
//char url[100];
char index = 0; // index indiquant où l'on est rendu dans la chaîne

int OnOff = 2;


void setup()
{
  pinMode(OnOff, OUTPUT);
  
  digitalWrite(OnOff, LOW);
  
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
  Serial.println(Ethernet.localIP());
}

void loop() {
  // Regarde si un client est connecté et attend une réponse
  EthernetClient client = serveur.available();
  if (client) { // Un client est là ?
    Serial.println("Ping !");
    url = ""; // on remet à zéro notre chaîne tampon
    index = 0;
    while(client.connected()) { // Tant que le client est connecté
      if(client.available()) { // A-t-il des choses à dire ?
        // traitement des infos du client
        char carlu = client.read(); //on lit ce qu'il raconte
        if(carlu != '\n') { // On est en fin de chaîne ?
          // non ! alors on stocke le caractère
          url[index] = carlu;
          index++;
          Serial.print(carlu);
        } else {
          // on a fini de lire ce qui nous intéresse
          // on marque la fin de l'url (caractère de fin de chaîne)
          url[index] = '\0';
          boolean ok = interpreter(); // essaie d'interpréter la chaîne
          // et dans tout les cas on répond au client
          repondre(client);
          // on quitte le while
          break;
        }
      }
    }
    // Donne le temps au client de prendre les données
    // Ferme la connexion avec le client
    client.stop();
    Serial.println("Pong !");
  }
}


void repondre(EthernetClient client) {
  // La fonction prend un client en argument

  Serial.println("\nRepondre"); // debug
  // On fait notre en-tête
  // Tout d'abord le code de réponse 200 = réussite
  client.println("HTTP/1.1 200 OK");
  // Puis le type mime du contenu renvoyé, du json
  client.println("Content-Type: application/json");
  // Autorise le cross origin
  client.println("Access-Control-Allow-Origin: *");
  // Et c'est tout !
  // On envoi une ligne vide pour signaler la fin du header
  client.println();
}

boolean interpreter() {
  // On commence par mettre à zéro tous les états

  // Puis maintenant on va chercher les caractères/marqueurs un par un.
  index = 4; // Index pour se promener dans la chaîne (commence à 4 pour enlever "GET "
  while(url[index-1] != 'r' && url[index] != '=') { // On commence par chercher le "b="
    index++; // Passe au caractère suivant
    if(index == 100) {
      // On est rendu trop loin !
      Serial.println("Oups, probleme dans la recherche de 'b='");
      return false;
    }
  }
  // Puis on lit jusqu’à trouver le '&' séparant les broches de pwm
  while(url[index] != '&') { // On cherche le '&'
    if(url[index] >= '0' && url[index] <= '3') {
      // On a trouvé un chiffre identifiant une broche
      char broche = url[index]; // On ramène ça au format décimal
      switch (broche){
  case '2':
     digitalWrite(OnOff, HIGH);
     delay(100);
     digitalWrite(OnOff, LOW);
     Serial.println("on allume");
  break;
    case '1':
     Serial.println("nul");
  break;
}
    }
    index++; // Passe au caractère suivant
    if(index >= 100) {
      // On est rendu trop loin !
      Serial.println("Oups, probleme dans la lecture des broches");
      return false;
    }
    // NOTE : Les virgules séparatrices sont ignorée
  }
  // Rendu ici, on a trouvé toutes les informations utiles !
  return true;
}


