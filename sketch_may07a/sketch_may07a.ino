int m = 3;
int pourcent = 0;
int valeur = 0;

void setup()
{
  pinMode(m, OUTPUT);
}

void loop()
{
  pourcent = 50;
  valeur = ((pourcent * 255)/100);
  analogWrite(m, valeur);
}
