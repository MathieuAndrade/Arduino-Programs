const int bouton_moin = 2;
const int bouton_plus = 3;
const int LED_1 = 4;
const int LED_2 = 5;
const int LED_3 = 6;
const int LED_4 = 7;

int nombre_LED = 0;
int etatbouton;
int memoire_moin = HIGH;
int memoire_plus = HIGH;


void setup() 
{
  pinMode(bouton_moin, INPUT);
  pinMode(bouton_plus, INPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  
}

void loop() 
{
  etatbouton = digitalRead(bouton_plus);
  
  if((etatbouton != memoire_plus) && (etatbouton == LOW))
  {
    nombre_LED++;
  }
  
  memoire_plus = etatbouton;
  
  etatbouton = digitalRead(bouton_moin);
  
  if((etatbouton != memoire_moin) && (etatbouton == LOW))
  {
    nombre_LED--;
  }
  
  memoire_moin = etatbouton;
  
  if(nombre_LED > 4)
  {
    nombre_LED = 4;
  }
  if(nombre_LED < 0)
  {
    nombre_LED = 0;
  }
  
 affiche(nombre_LED);
}

void affiche(int valeur_recue)
{
    //on éteint toutes les LEDs
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);

    //Puis on les allume une à une
    if(valeur_recue >= 1)
    {
        digitalWrite(LED_1, LOW);
    }
    if(valeur_recue >= 2)
    {
        digitalWrite(LED_2, LOW);
    }
    if(valeur_recue >= 3)
    {
        digitalWrite(LED_3, LOW);
    }
    if(valeur_recue >= 4)
    {
        digitalWrite(LED_4, LOW);
    }
}
