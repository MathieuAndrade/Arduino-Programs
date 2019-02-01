
int receiver = 2;
const int LED_DROITE = 5;
const int LED_GAUCHE = 6;

IRrecv irrecv(receiver); 
decode_results results; 


void setup()
{
  pinMode(LED_DROITE, OUTPUT);
  pinMode(LED_GAUCHE, OUTPUT);
  digitalWrite(LED_DROITE, HIGH);
  digitalWrite(LED_GAUCHE, HIGH);
  irrecv.enableIRIn();
}

void loop()
{
  if (irrecv.decode(&results))
  {
    translateIR(); 
    irrecv.resume(); 
   }
}

void translateIR()

{
  switch(results.value)
  {
  case 0x20DF02FD: Serial.println(" FLECHE DU HAUT"); break;
  case 0x20DF609F: digitalWrite(LED_DROITE, LOW);
                   digitalWrite(LED_GAUCHE, HIGH);     break;
  case 0x20DF827D: Serial.println(" FLECHE DU BAS");    break;
  case 0x20DFE01F: digitalWrite(LED_GAUCHE, LOW);
                   digitalWrite(LED_DROITE, HIGH);      break;
  case 0x2F0: Serial.println(" FLECHE DU HAUT"); break;
  case 0xCD0: Serial.println(" FLECHE DE DROITE");    break;
  case 0xAF0: Serial.println(" FLECHE DU BAS");    break;
  case 0x2D0: Serial.println(" FLECHE DE GAUCHE");    break;

  case 0xFFFFFFFF: Serial.println(" REPEAT");break;
  }

  delay(500);
} 
