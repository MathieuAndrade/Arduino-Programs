const int A = 2;
const int B = 8;
const int C = 6;
const int D = 5;
const int E = 4;
const int F = 3;
const int G = 7;

void setup() 
{
   pinMode(A ,OUTPUT);
   pinMode(B ,OUTPUT);
   pinMode(C ,OUTPUT);
   pinMode(D ,OUTPUT);
   pinMode(E ,OUTPUT);
   pinMode(F ,OUTPUT);
   pinMode(G ,OUTPUT);
   
   digitalWrite(A, HIGH);
   digitalWrite(B, HIGH);
   digitalWrite(C, HIGH);
   digitalWrite(D, HIGH);
   digitalWrite(E, HIGH);
   digitalWrite(F, HIGH);
   digitalWrite(G, HIGH);
   
}

void loop() 
{
   digitalWrite(A, LOW);
   digitalWrite(B, LOW);
   digitalWrite(C, LOW);
   digitalWrite(D, LOW);
   digitalWrite(E, HIGH);
   digitalWrite(F, LOW);
   digitalWrite(G, LOW);
   delay(1000);
   digitalWrite(A, LOW);
   digitalWrite(B, LOW);
   digitalWrite(C, LOW);
   digitalWrite(D, LOW);
   digitalWrite(E, LOW);
   digitalWrite(F, LOW);
   digitalWrite(G, LOW);
   delay(1000);
   digitalWrite(A, LOW);
   digitalWrite(B, LOW);
   digitalWrite(C, LOW);
   digitalWrite(D, HIGH);
   digitalWrite(E, HIGH);
   digitalWrite(F, HIGH);
   digitalWrite(G, HIGH);
   delay(1000);
   digitalWrite(A, LOW);
   digitalWrite(B, HIGH);
   digitalWrite(C, LOW);
   digitalWrite(D, LOW);
   digitalWrite(E, LOW);
   digitalWrite(F, LOW);
   digitalWrite(G, LOW);
   delay(1000);
   digitalWrite(A, LOW);
   digitalWrite(B, HIGH);
   digitalWrite(C, LOW);
   digitalWrite(D, LOW);
   digitalWrite(E, HIGH);
   digitalWrite(F, LOW);
   digitalWrite(G, LOW);
   delay(1000);
   digitalWrite(A, HIGH);
   digitalWrite(B, LOW);
   digitalWrite(C, LOW);
   digitalWrite(D, HIGH);
   digitalWrite(E, HIGH);
   digitalWrite(F, LOW);
   digitalWrite(G, LOW);
   delay(1000);
   digitalWrite(A, LOW);
   digitalWrite(B, LOW);
   digitalWrite(C, LOW);
   digitalWrite(D, LOW);
   digitalWrite(E, HIGH);
   digitalWrite(F, HIGH);
   digitalWrite(G, LOW);
   delay(1000);
   digitalWrite(A, LOW);
   digitalWrite(B, LOW);
   digitalWrite(C, HIGH);
   digitalWrite(D, LOW);
   digitalWrite(E, LOW);
   digitalWrite(F, HIGH);
   digitalWrite(G, LOW);
   delay(1000);
   digitalWrite(A, HIGH);
   digitalWrite(B, LOW);
   digitalWrite(C, LOW);
   digitalWrite(D, HIGH);
   digitalWrite(E, HIGH);
   digitalWrite(F, HIGH);
   digitalWrite(G, HIGH);
   delay(1000);
   digitalWrite(A, LOW);
   digitalWrite(B, LOW);
   digitalWrite(C, LOW);
   digitalWrite(D, LOW);
   digitalWrite(E, LOW);
   digitalWrite(F, LOW);
   digitalWrite(G, HIGH);
   delay(5000);
}

