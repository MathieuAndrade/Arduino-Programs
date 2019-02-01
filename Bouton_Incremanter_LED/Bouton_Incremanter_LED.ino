const int BTN_moins = 2;
const int BTN_plus = 3;
const int Led_0 = 10;
const int Led_1 = 11;
const int Led_2 = 12;
const int Led_3 = 13;

int nombre_led = 0;
int etatbouton;

int memoire_plus = HIGH;
int memoire_moins = HIGH;

void setup() 
{
  pinMode(BTN_moins, INPUT);
  pinMode(BTN_plus, INPUT);
  pinMode(Led_0, OUTPUT);
  pinMode(Led_1, OUTPUT);
  pinMode(Led_2, OUTPUT);
  pinMode(Led_3, OUTPUT);
}

void loop() 
{
  etatbouton = digitalRead(BTN_plus);
  
  if((etatbouton != memoire_plus) && ( etatbouton == LOW))
  {
    nombre_led++;
  }
  
  memoire_plus = etatbouton;
  
  etatbouton = digitalRead(BTN_moins);
  
  if((etatbouton != memoire_moins) && (etatbouton == LOW))
  {
    nombre_led--;
  }
  memoire_moins = etatbouton;
  
  if(nombre_led  > 4)
  {
    nombre_led = 4;
  }
  if(nombre_led < 0)
  {
    nombre_led = 0;
  }
}
void affiche(int = nombre_led)
{
  digitalWrite(Led_0, HIGH);
  digitalWrite(Led_1, HIGH);
  digitalWrite(Led_2, HIGH);
  digitalWrite(Led_3, HIGH);
  
  if(nombre_led >= 1)
  {
    digitalWrite(Led_0, LOW);
  }
  if(nombre_led >= 2)
  {
    digitalWrite(Led_1, LOW);
  }
  if(nombre_led >= 3)
  {
    digitalWrite(Led_2, LOW);
  }
  if(nombre_led >= 4)
  {
    digitalWrite(Led_3, LOW);
  }
}
