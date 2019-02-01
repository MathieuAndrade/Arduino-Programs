
/* Variable globales */
char buffer[8]; // Buffer qui stocke les 8 bits en ascii
byte index = 0; // Itérateur qui permet d'indexer le buffer
byte valeur;    // Valeur final

void setup() 
{
  Serial.begin(115200);
} 

/* Loop() */
void loop() {

  // Si les huits bits de la valeur ont été recu
  if(index == 8) {
    valeur = 0; // Initialisation de la valeur à zéro
	
	// Pour chaque bits
    for(byte i = 0; i < 8; ++i) {
	
	  // Si le bit est à "1" logique
	  if(buffer[i] == '1')
	    valeur |= 1 << i; // Mise à "1" du bit dans la valeur final
		// A |= B -> A = A (OU logique bit à bit) B
		// 1 << i -> 1 décalé de i bits vers la droite (ex: 1 << 4 = 16)
    }
	
	// Affichage de la valeur
	Serial.print("Valeur: ");
	Serial.println(valeur);
  }
  
  // Si des données sont disponible en lecture
  if(Serial.available() > 0) {
  
    // Lecture d'un octet depuis le port série
    char c = Serial.read();
	
	// Vérification de la validité du bit (caractére '1' ou '0')
	if(c != '0' && c != '1') {
	
	  // En cas d'erreur on reprend du début
	  index = 0;
	  Serial.println("Erreur !");
	  
	} else { // Si le bit est valide
	  buffer[index] = c; // On le stocke en mémoire
	  ++index;           // On prépare l'index pour le bit suivant
	}
  }
}
