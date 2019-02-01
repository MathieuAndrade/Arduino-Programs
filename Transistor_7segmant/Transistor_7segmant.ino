const int T = 9;
const int A = 2;
const int B = 3;
const int C = 4;
const int D = 5;
const int E = 6;
const int F = 7;
const int G = 8;


void setup() 
{
   pinMode(T, OUTPUT);
   pinMode(A, OUTPUT);
   pinMode(B, OUTPUT);
   pinMode(C, OUTPUT);
   pinMode(D, OUTPUT);
   pinMode(E, OUTPUT);
   pinMode(F, OUTPUT);
   pinMode(G, OUTPUT);
   
   digitalWrite(A, LOW);
   digitalWrite(B, LOW);
   digitalWrite(C, LOW);
   digitalWrite(D, LOW);
   digitalWrite(E, LOW);
   digitalWrite(F, LOW);
   digitalWrite(G, LOW);


}

void loop() 
{
  digitalWrite(T, LOW);
  delay(1000);
  digitalWrite(T, HIGH);
  delay(1000);
}
