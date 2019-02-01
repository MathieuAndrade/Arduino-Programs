int Led1 = 2;
int Led2 = 6;
int Led3 = 11;

const int Delai = 100;
unsigned long Depart;

void setup()
{
  pinMode(Led1 ,OUTPUT);
  pinMode(Led2 ,OUTPUT);
  pinMode(Led3, OUTPUT);
  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  
  Depart = 10;
  Depart = millis();
}
 
void loop()
{
  if((millis()-Depart) >=Delai)
  {
    digitalWrite(Led1, HIGH);
    Depart=millis(); 
  }
 
  if((millis()-Depart) >=Delai)
  {
    digitalWrite(Led2, HIGH);
    Depart=millis();
  }
  
  if((millis()-Depart) >=Delai)
  {
    digitalWrite(Led3, HIGH);
    Depart=millis();
  }
//___________________________________________  
  if((millis()-Depart) >=Delai)
  {
    digitalWrite(Led1, LOW);
    Depart=millis();
  }
  
  if((millis()-Depart) >=Delai)
  {
    digitalWrite(Led2, LOW);
    Depart=millis();
  }
  
  if((millis()-Depart) >=Delai)
  {
    digitalWrite(Led3, LOW);
    Depart=millis();
  }
}
