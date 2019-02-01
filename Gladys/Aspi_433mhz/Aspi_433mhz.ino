#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

int mCode = Your_Code; // Variable qui enregistre ton code
int button = PIN_OF_YOUR_BUTTON; // Variable qui enregistre sur quel pin est branché ton bouton

// Fonction d'initialisation du programme
void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Recepteur sur le pin 2
  pinMode(button, OUTPUT); // Initialisation du pin "button" comme pin sortant
  digitalWrite(button, LOW); //Mise a l'etat bas du pin "button"
}

// Boucle du programme
void loop() {

  // Si un code est recu
  if (mySwitch.available()) {

    // On stock ce code dans la variable "value"
    int value = mySwitch.getReceivedValue();

    // Si le code recu est le meme que celui enregistré
    if (value == mCode) {

      // On cree une impulsion pour simuler un appui sur le bouton
      digitalWrite(button, HIGH); // Mise a l'etat haut du pin "button"
      delay(10); // Pause de 10 millisecondes
      digitalWrite(button, LOW); // Mise a l'etat bas du pin "button"
    } 
    else {} // Si le code recu n'est pas le meme que celui enregistré ici on ne fait rien

    mySwitch.resetAvailable();
  }
}
