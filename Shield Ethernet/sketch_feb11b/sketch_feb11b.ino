// Ces deux bibliothèques sont indispensables pour le shield
#include <SPI.h>
#include <Ethernet.h>

// L'adresse MAC du shield
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
// L'adresse IP que prendra le shield
IPAddress ip(192,168,1,16);

// Initialise notre serveur
// Ce dernier écoutera sur le port 4200
EthernetServer serveur(4200);

char *url = (char *)malloc(100); // L'url recu à stocker
//char url[100];
char index = 0; // index indiquant où l'on est rendu dans la chaîne
boolean etats[3] = {LOW, LOW, LOW}; // L'état des 3 sorties
unsigned char pwm = 0; // La valeur de la pwm

void setup()
{
  // On démarre la voie série pour déboguer
  Serial.begin(9600);

  // Configure et initialise les broches
  pinMode(3, OUTPUT); digitalWrite(3, LOW);
  pinMode(4, OUTPUT); digitalWrite(4, LOW);
  pinMode(5, OUTPUT); digitalWrite(5, LOW);
  pinMode(6, OUTPUT); analogWrite(6, 0);

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
          Serial.print(carlu);
          url[index] = carlu;
          index++;
        } else {
          // on a fini de lire ce qui nous interesse
          // on marque la fin de l'url (caractère de fin de chaîne)
          
          boolean ok = interpreter(); // essaie d'interpreter la chaîne
          if(ok) {
            // tout s'est bien passé = on met à jour les broches
            // On met à jour nos broches
            digitalWrite(3, etats[0]);
            digitalWrite(4, etats[1]);
            digitalWrite(5, etats[2]);
            // Et la PWM
            analogWrite(6, pwm);
          }
          // et dans tout les cas on répond au client
          repondre(client);
          // on quitte le while
          break;
        }
      }
    }
    // Donne le temps au client de prendre les données
    delay(10);
    // Ferme la connexion avec le client
    client.stop();
    Serial.println("Pong !");
  }
}

void rafraichir() {
  // Rafraichit l'etat des broches / PWM
  digitalWrite(3, etats[0]);
  digitalWrite(4, etats[1]);
  digitalWrite(5, etats[2]);
  analogWrite(6, pwm);
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

  // Puis on commence notre JSON par une accolade ouvrante
  client.println("{");
  // On envoie la première clé : "uptime"
  client.print("\t\"uptime\": ");
  // Puis la valeur de l'uptime
  client.print(millis());
  //Une petite virgule pour séparer les deux clés
  client.println(",");
  // Et on envoie la seconde nommée "analog 0"
  client.print("\t\"A0\": ");
  client.print(analogRead(A0));
  client.println(",");
  // Puis la valeur de la PWM sur la broche 6
  client.print("\t\"pwm\": ");
  client.print(pwm, DEC);
  client.println(",");
  // Dernières valeurs, les broches (elles mêmes dans un tableau)
  client.println("\t\"broches\": {");
  // La broche 3
  client.print("\t\t\"3\": ");
  client.print(digitalRead(3));
  client.println(",");
  // La broche 4
  client.print("\t\t\"4\": ");
  client.print(digitalRead(4));
  client.println(",");
  // La broche 5
  client.print("\t\t\"5\": ");
  client.println(digitalRead(5));
  client.println("\t}");
  // Et enfin on termine notre JSON par une accolade fermante
  client.println("}");
}

boolean interpreter() 
{
  // On commence par mettre à zéro tous les états
  etats[0] = LOW;
  etats[1] = LOW;
  etats[2] = LOW;
  pwm = 0;

  // Puis maintenant on va chercher les caractères/marqueurs un par un.
  index = 0; // Index pour se promener dans la chaîne (commence à 4 pour enlever "GET "
  while(url[index-1] != 'b' && url[index] != '=') { // On commence par chercher le "b="
    index++; // Passe au caractère suivant
    if(index == 100) {
      // On est rendu trop loin !
      Serial.println("Oups, probleme dans la recherche de 'b='");
      return false;
    }
  }
  // Puis on lit jusqu’à trouver le '&' séparant les broches de pwm
  while(url[index] != '&') { // On cherche le '&'
    if(url[index] >= '3' && url[index] <= '5') {
      // On a trouvé un chiffre identifiant une broche
      char broche = url[index]-'0'; // On ramène ça au format décimal
      etats[broche-3] = HIGH; // Puis on met la broche dans un futur état haut
    }
    index++; // Passe au caractère suivant
    if(index == 100) {
      // On est rendu trop loin !
      Serial.println("Oups, probleme dans la lecture des broches");
      return false;
    }
    // NOTE : Les virgules séparatrices sont ignorées
  }
  // On a les broches, reste plus que la valeur de la PWM
  // On cherche le "p="
 while(url[index-1] != 'p' && url[index] != '=' && index == '0' && url[index] <= '9') {
      // On a trouvé un chiffre !
      char val = url[index]-'0'; // On ramène ça au format décimal
      pwm = (pwm*10) + val; // On stocke dans la pwm
    }
    index++; // Passe au caractère suivant
    if(index == 100) {
      // On est rendu trop loin !
      Serial.println("Oups, probleme dans la lecture de la pwm");
      return false;
    }
   // NOTE : Les virgules séparatrices sont ignorées
   return true;
  }
  // Rendu ici, on a trouvé toutes les informations utiles !
  



