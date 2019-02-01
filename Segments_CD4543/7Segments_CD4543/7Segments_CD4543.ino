const int bit_A = 2;
const int bit_B = 3;
const int bit_C = 4;
const int bit_D = 5;


void setup()
{
   //on met les broches en sorties
   pinMode(bit_A, OUTPUT);
   pinMode(bit_B, OUTPUT);
   pinMode(bit_C, OUTPUT);
   pinMode(bit_D, OUTPUT);

   //on commence par écrire le chiffre 0, donc toutes les sorites à l'état bas
   digitalWrite(bit_A, HIGH);
   digitalWrite(bit_B, HIGH);
   digitalWrite(bit_C, HIGH);
   digitalWrite(bit_D, HIGH);
}

void loop() 
{
  digitalWrite(bit_A, LOW);
  digitalWrite(bit_B, LOW);
  digitalWrite(bit_C, HIGH);
  digitalWrite(bit_D, HIGH);
}
