#include <LiquidCrystal.h>

// initialise l'écran avec les bonnes broches
// ATTENTION, REMPLACER LES NOMBRES PAR VOS BRANCHEMENTS À VOUS !
LiquidCrystal lcd(11,10,9,8,7,6,5,4,3,2);

void setup()
{
  lcd.begin(16, 2);   
  lcd.setCursor(0,0);        //place le curseur aux coordonnées (2,1)
  lcd.print("L'Auto ecole St  "); //texte centré sur la ligne 2
  lcd.setCursor(0,1);
  lcd.print("Charles ?");
  delay(4000);
  lcd.clear();
  lcd.setCursor(0,0);        //place le curseur aux coordonnées (2,1)
  lcd.print("C'est la"); //texte centré sur la ligne 2
  lcd.setCursor(0,1);
  lcd.print("meilleur !!");
  
}

void loop() {}
