const int Led_rouge1 = 2;
const int Led_jaune1 = 3;
const int Led_verte1 = 4;
const int Led_rouge2 = 7;
const int Led_jaune2 = 6;
const int Led_verte2 = 5;

void setup()
{
  pinMode(Led_rouge1, OUTPUT); 
  pinMode(Led_rouge2, OUTPUT);
  pinMode(Led_jaune1, OUTPUT);
  pinMode(Led_jaune2, OUTPUT);
  pinMode(Led_verte1, OUTPUT);
  pinMode(Led_verte2, OUTPUT);
  
  digitalWrite(Led_rouge1, LOW);
  digitalWrite(Led_jaune1, HIGH);
  digitalWrite(Led_verte1, HIGH);
  digitalWrite(Led_rouge2, LOW);
  digitalWrite(Led_jaune2, HIGH);
  digitalWrite(Led_verte2, HIGH);
}


void loop() 
{
  digitalWrite(Led_rouge2, HIGH);
  digitalWrite(Led_rouge1, LOW);
  digitalWrite(Led_verte2, LOW);
  delay(3000);
  digitalWrite(Led_verte2, HIGH);
  digitalWrite(Led_jaune2, LOW);
  delay(1000);
  digitalWrite(Led_jaune2, HIGH);
  digitalWrite(Led_rouge2, LOW);
  delay(3000);
  digitalWrite(Led_rouge1, HIGH);
  digitalWrite(Led_verte1, LOW);
  delay(3000);
  digitalWrite(Led_verte1, HIGH);
  digitalWrite(Led_jaune1, LOW);
  delay(1000);
  digitalWrite(Led_jaune1, HIGH);
  digitalWrite(Led_rouge1, LOW);
  delay(1000);
}




