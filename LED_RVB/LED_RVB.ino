const int B = 2;
const int V = 3;
const int R = 4;

void setup() 
{
  digitalWrite(R, LOW);
  digitalWrite(V, LOW);
  digitalWrite(B, LOW);
}

void loop() 
{
  digitalWrite(R, HIGH);
  digitalWrite(V, LOW);
  digitalWrite(B, LOW);
  delay(1000);
  digitalWrite(R, LOW);
  digitalWrite(V, HIGH);
  digitalWrite(B, LOW);
  delay(1000);
  digitalWrite(R, LOW);
  digitalWrite(V, LOW);
  digitalWrite(B, HIGH);
  delay(1000);
  digitalWrite(R, HIGH);
  digitalWrite(V, HIGH);
  digitalWrite(B, LOW);
  delay(1000);
  digitalWrite(R, HIGH);
  digitalWrite(V, LOW);
  digitalWrite(B, HIGH);
  delay(1000);
  digitalWrite(R, LOW);
  digitalWrite(V, HIGH);
  digitalWrite(B, HIGH);
  delay(1000);
}
