#include <LiquidCrystal.h>


//Vérifier les broches !

LiquidCrystal lcd(11,10,5,4,3,2); //liaison 4 bits de données

  byte smiley[8] = {       
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B11111
};

byte smiley2[8] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B11111,
    B11111
};
byte smiley3[8] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B11111,
    B11111,
    B11111
};
byte smiley4[8] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B11111,
    B11111,
    B11111,
    B11111
};
byte smiley5[8] = {
    B00000,
    B00000,
    B00000,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
};
byte smiley6[8] = {
    B00000,
    B00000,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
};
byte smiley7[8] = {
    B00000,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
};

void setup()
{
   lcd.begin(16,2); //utilisation d'un écran 16 colonnes et 2 lignes
   lcd.createChar(0, smiley);
   lcd.createChar(1, smiley2);
   lcd.createChar(2, smiley3);
   lcd.createChar(3, smiley4);
   lcd.createChar(4, smiley5);
   lcd.createChar(5, smiley6); //petit test pour vérifier que tout marche
}
void loop() 
{
  lcd.setCursor(0,0);
  lcd.print("CPU: 33c");
  lcd.setCursor(0,1);
  lcd.print("GPU: 33c");
  lcd.setCursor(11,0);
  lcd.print("FAN");
  lcd.setCursor(10,1);
  lcd.write((uint8_t) 0);
  lcd.setCursor(11,1);
  lcd.write((uint8_t) 1);
  lcd.setCursor(12,1);
  lcd.write((uint8_t) 2);
  lcd.setCursor(13,1);
  lcd.write((uint8_t) 3);
  lcd.setCursor(14,1);
  lcd.write((uint8_t) 4);
  lcd.setCursor(15,1);
  lcd.write((uint8_t) 5);

}

