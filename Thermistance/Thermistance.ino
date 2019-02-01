#include <math.h>
#define PIN_NTC 0
 
double Rref = 3850.0; //Résistance de référence à 25°C
double V_IN = 5.0; //Alimentation électrique
 
//Information de la thermistance
double A_1 = 3.354016E-3;
double B_1 = 2.569850E-4;
double C_1 = 2.620131E-6;
double D_1 = 6.383091E-8;
 
double SteinhartHart(double R)
{
  //Division de l'équation en 4 parties. La premiere est 
  //uniquement A1
  double equationB1 = B_1 * log(R/Rref);
  double equationC1 = C_1 * pow(log(R/Rref), 2);
  double equationD1 = D_1 * pow(log(R/Rref), 3);
  double equation = A_1 - equationB1 - equationC1 - equationD1;
  return pow(equation, -1);
 
}
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  //Calcul de la tension sur la borne analogique
  double valeurAnalog = analogRead(PIN_NTC);
  double V =  valeurAnalog / 1024 * V_IN;
 
  //Calcul de la résistance de la thermistance
  double Rth = (Rref * V ) / (V_IN - V);
  Serial.print("Rth = ");
  Serial.print(Rth);
 
  //Calcul de la température en kelvin( Steinhart and Hart)
  double kelvin = SteinhartHart(Rth);
  double celsius = kelvin - 273.15; //Conversion en celsius
  Serial.print("Ohm  -  T = ");
  Serial.print(celsius);
  Serial.print("C\n");
  delay(400);
}
