const int bouton = 2;
const int Led = 13;

int etatbouton;

void setup() 
{
   pinMode(bouton, INPUT);
   pinMode(Led, OUTPUT);
   etatbouton = HIGH ;
}

void loop() 
{
  etatbouton = digitalRead(bouton);
  
  if(etatbouton == HIGH)
  {
    digitalWrite(Led, HIGH);
  }
  else
  {
    digitalWrite(Led, LOW);
  }
}
