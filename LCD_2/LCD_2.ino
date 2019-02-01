#include <LiquidCrystal.h> //on inclut la librairie

// initialise l'écran avec les bonnes broches
// ATTENTION, REMPLACER LES NOMBRES PAR VOS BRANCHEMENTS À VOUS !
LiquidCrystal lcd(11,10,9,8,7,6,5,4,3,2);

void setup() {
  // règle la  taille du LCD
  lcd.begin(16, 2);
  lcd.print("Hello World !");
}

void loop() {
  lcd.noDisplay();
  delay(500);
  lcd.display();
  delay(500);
}
