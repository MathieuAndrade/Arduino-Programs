#include <LiquidCrystal.h> //on inclut la librairie

// initialise l'écran avec les bonnes broches
// ATTENTION, REMPLACER LES NOMBRES PAR VOS BRANCHEMENTS À VOUS !
LiquidCrystal lcd(8,9,4,5,6,7);

void setup() {
  // règle la  taille du LCD
  lcd.begin(16, 2);
  lcd.print("Hello World !");
  delay(2000);
  lcd.clear();
}
