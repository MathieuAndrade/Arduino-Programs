const int L1 = 3;
const int L2 = 2;
const int L3 = 4;
const int L4 = 6;
const int L5 = 7;
const int L6 = 5;

void setup()
{
  pinMode(L1, OUTPUT); 
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
  pinMode(L5, OUTPUT);
  pinMode(L6, OUTPUT);
}

void loop() 
{
  digitalWrite(L1, LOW);
  digitalWrite(L4, LOW);
  delay(5000);
  digitalWrite(L1, HIGH);
  digitalWrite(L4, HIGH);
  digitalWrite(L2, LOW);
  digitalWrite(L5, LOW);
  delay(2000);
  digitalWrite(L2, HIGH);
  digitalWrite(L5, HIGH);
  digitalWrite(L3, LOW);
  digitalWrite(L6, LOW);
  delay(5000);
  digitalWrite(L3, HIGH);
  digitalWrite(L6, HIGH);
}




