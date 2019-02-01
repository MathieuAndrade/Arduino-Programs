#include "IRremote.h"

const int LED_1 = 3;
const int LED_2 = 4;
const int LED_3 = 5;
const int LED_4 = 6;
const int LED_5 = 7;
const int LED_6 = 8;

int nombre_LED = 0;

int recepteur = 2;

IRrecv irrece(recepteur);           
decode_results resultats;

void setup() 
{
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);
  irrece.enableIRIn();
}

void loop() 
{
  if (irrece.decode(&resultats)) // have we received an IR signal?
  {
    translateIR(); 
    irrece.resume(); // receive the next value
  }

  if(nombre_LED > 2)
  {
    nombre_LED = 2;
  }
  if(nombre_LED < 0)
  {
    nombre_LED = 0;
  }
  
  affiche(nombre_LED);
  
}

void translateIR()

{
  switch(resultats.value)
  {
    case 0x20DF609F : 
         nombre_LED++ ;    
         break;
  
    case 0x20DFE01F : 
         nombre_LED-- ;      
         break;
         
    case 0x20DF827D :
         nombre_LED=0;
         break;
         
    case 0xFFFFFFFF :
         break; 

  }
} 

void affiche(int valeur_recue)
{
    //on éteint toutes les LEDs
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
    digitalWrite(LED_5, HIGH);
    digitalWrite(LED_6, HIGH);

    //Puis on les allume une à une
    if(valeur_recue >= 1)
    {
      K3000();
    }
    if(valeur_recue >= 2)
    {
      K2000();
    }
}

void K3000()
{
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_6, LOW); 
  delay(80);
  digitalWrite(LED_2, LOW);  
  digitalWrite(LED_5, LOW);
  delay(80);
  digitalWrite(LED_3, LOW);  
  digitalWrite(LED_4, LOW);
  delay(80);
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_6, HIGH);  
  delay(80);
  digitalWrite(LED_2, HIGH);  
  digitalWrite(LED_5, HIGH); 
  delay(80); 
  digitalWrite(LED_3, HIGH);  
  digitalWrite(LED_4, HIGH);
  delay(80);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_4, LOW); 
  delay(80);
  digitalWrite(LED_2, LOW);  
  digitalWrite(LED_5, LOW);
  delay(80);
  digitalWrite(LED_1, LOW);  
  digitalWrite(LED_6, LOW);
  delay(80);
  digitalWrite(LED_3, HIGH);
  digitalWrite(LED_4, HIGH);  
  delay(80);
  digitalWrite(LED_2, HIGH);  
  digitalWrite(LED_5, HIGH); 
  delay(80); 
  digitalWrite(LED_1, HIGH);  
  digitalWrite(LED_6, HIGH);
  delay(80);      

}
 void K2000()
 {
   digitalWrite(LED_1, LOW);
   delay(80);
   digitalWrite(LED_2, LOW);
   delay(80);
   digitalWrite(LED_3, LOW);
   delay(80);
   digitalWrite(LED_4, LOW);
   digitalWrite(LED_1, HIGH);
   delay(80);
   digitalWrite(LED_5, LOW);
   digitalWrite(LED_2, HIGH);
   delay(80);
   digitalWrite(LED_6, LOW);
   digitalWrite(LED_3, HIGH);
   delay(80);
   digitalWrite(LED_4, HIGH);
   delay(80);
   digitalWrite(LED_5, HIGH);
   delay(80);
   digitalWrite(LED_6, HIGH);
   delay(80);
   digitalWrite(LED_6, LOW);
   delay(80);
   digitalWrite(LED_5, LOW);
   delay(80);
   digitalWrite(LED_4, LOW);
   delay(80);
   digitalWrite(LED_3, LOW);
   digitalWrite(LED_6, HIGH);
   delay(80);
   digitalWrite(LED_2, LOW);
   digitalWrite(LED_5, HIGH);
   delay(80);
   digitalWrite(LED_1, LOW);
   digitalWrite(LED_4, HIGH);
   delay(80);
   digitalWrite(LED_3, HIGH);
   delay(80);
   digitalWrite(LED_2, HIGH);
   delay(80);
   digitalWrite(LED_1, HIGH);
   delay(80);
 }


