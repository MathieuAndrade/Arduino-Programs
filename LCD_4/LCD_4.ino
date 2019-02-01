#include <LiquidCrystal.h> //on inclut la librairie

//les branchements
const int boutonGauche = 12; //le bouton de gauche
const int boutonDroite = 13; //le bouton de droite

// initialise l'écran avec les bonnes broches
// ATTENTION, REMPLACER LES NOMBRES PAR VOS BRANCHEMENTS À VOUS !
LiquidCrystal lcd(11,10,9,8,7,6,5,4,3,2);

//------------------------------------------------------------------------------

void setup() {
  //règlage des entrées/sorties
  pinMode(boutonGauche, INPUT);
  pinMode(boutonDroite, INPUT);
  
  //on attache des fonctions aux deux interruptions externes (les boutons)
  attachInterrupt(0, aDroite, RISING);
  attachInterrupt(1, aGauche, RISING);

  //paramètrage du LCD
  lcd.begin(16, 2); // règle la  taille du LCD
  lcd.print("Hello les Zeros !");
}

void loop() {
  //pas besoin de loop pour le moment
}

//fonction appelée par l'interruption du premier bouton
void aGauche() {
  lcd.scrollDisplayLeft(); //on va à gauche !
}

//fonction appelé par l'interruption du deuxième bouton
void aDroite() {
  lcd.scrollDisplayRight(); //on va à droite !
}
