const int LED_1 = 2;
const int LED_2 = 3;
const int LED_3 = 4;
const int LED_4 = 5;
const int LED_5 = 6;
const int LED_6 = 7;
const int LED_7 = 8;
const int LED_8 = 9;
const int LED_9 = 10;
const int LED_10 = 11;
const int LED_11 = 12;
const int LED_12 = 13;

const int bouton = 1; 
int etatbouton ;

void setup() {
  
  pinMode(bouton, INPUT);
  pinMode(LED_1 , OUTPUT);
  pinMode(LED_2 , OUTPUT);
  pinMode(LED_3 , OUTPUT);
  pinMode(LED_4 , OUTPUT);
  pinMode(LED_5 , OUTPUT);
  pinMode(LED_6 , OUTPUT);
  pinMode(LED_7 , OUTPUT);
  pinMode(LED_8 , OUTPUT);
  pinMode(LED_9 , OUTPUT);
  pinMode(LED_10 , OUTPUT);
  pinMode(LED_11 , OUTPUT);
  pinMode(LED_12 , OUTPUT);
  
  digitalWrite(LED_1, HIGH);  
  digitalWrite(LED_2, HIGH);  
  digitalWrite(LED_3, HIGH);  
  digitalWrite(LED_4, HIGH);  
  digitalWrite(LED_5, HIGH);  
  digitalWrite(LED_6, HIGH);  
  digitalWrite(LED_7, HIGH);  
  digitalWrite(LED_8, HIGH);  
  digitalWrite(LED_9, HIGH);  
  digitalWrite(LED_10, HIGH);  
  digitalWrite(LED_11, HIGH);
  digitalWrite(LED_12, HIGH);
}

void loop() 
{
 etatbouton = digitalRead(bouton);
  
  if (etatbouton == HIGH)
  {     
    K3000();
  } 
  else 
  {
    K2000();
  }
}
 
void K3000()
{
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_12, LOW); 
  delay(80);
  digitalWrite(LED_2, LOW);  
  digitalWrite(LED_11, LOW);
  delay(80);
  digitalWrite(LED_3, LOW);  
  digitalWrite(LED_10, LOW);
  delay(80);
  digitalWrite(LED_4, LOW);  
  digitalWrite(LED_9, LOW);
  delay(80);
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_12, HIGH);  
  delay(80);
  digitalWrite(LED_5, LOW);  
  digitalWrite(LED_8, LOW); 
  delay(80); 
  digitalWrite(LED_2, HIGH);  
  digitalWrite(LED_11, HIGH); 
  delay(80); 
  digitalWrite(LED_6, LOW);  
  digitalWrite(LED_7, LOW); 
  delay(80);
  digitalWrite(LED_3, HIGH);  
  digitalWrite(LED_10, HIGH);
  delay(80);   
  digitalWrite(LED_4, HIGH);  
  digitalWrite(LED_9, HIGH);
  delay(80);  
  digitalWrite(LED_5, HIGH);  
  digitalWrite(LED_8, HIGH);
  delay(80);  
  digitalWrite(LED_6, HIGH);  
  digitalWrite(LED_7, HIGH);
  delay(80); 
  digitalWrite(LED_6, LOW);
  digitalWrite(LED_7, LOW); 
  delay(80);
  digitalWrite(LED_5, LOW);  
  digitalWrite(LED_8, LOW);
  delay(80);
  digitalWrite(LED_4, LOW);  
  digitalWrite(LED_9, LOW);
  delay(80);
  digitalWrite(LED_3, LOW);  
  digitalWrite(LED_10, LOW);
  delay(80);
  digitalWrite(LED_6, HIGH);
  digitalWrite(LED_7, HIGH);  
  delay(80);
  digitalWrite(LED_2, LOW);  
  digitalWrite(LED_11, LOW); 
  delay(80); 
  digitalWrite(LED_5, HIGH);  
  digitalWrite(LED_8, HIGH); 
  delay(80); 
  digitalWrite(LED_1, LOW);  
  digitalWrite(LED_12, LOW); 
  delay(80);
  digitalWrite(LED_4, HIGH);  
  digitalWrite(LED_9, HIGH);
  delay(80);   
  digitalWrite(LED_3, HIGH);  
  digitalWrite(LED_10, HIGH);
  delay(80);  
  digitalWrite(LED_2, HIGH);  
  digitalWrite(LED_11, HIGH);
  delay(80);  
  digitalWrite(LED_1, HIGH);  
  digitalWrite(LED_12, HIGH);
  delay(80);
}
 void K2000()
 {
   digitalWrite(LED_1, LOW);
   delay(80);
   digitalWrite(LED_2, LOW);
   delay(80);
   digitalWrite(LED_3, LOW);
   delay(80);
   digitalWrite(LED_4, LOW);
   digitalWrite(LED_1, HIGH);
   delay(80);
   digitalWrite(LED_5, LOW);
   digitalWrite(LED_2, HIGH);
   delay(80);
   digitalWrite(LED_6, LOW);
   digitalWrite(LED_3, HIGH);
   delay(80);
   digitalWrite(LED_7, LOW);
   digitalWrite(LED_4, HIGH);
   delay(80);
   digitalWrite(LED_8, LOW);
   digitalWrite(LED_5, HIGH);
   delay(80);
   digitalWrite(LED_9, LOW);
   digitalWrite(LED_6, HIGH);
   delay(80);
   digitalWrite(LED_10, LOW);
   digitalWrite(LED_7, HIGH);
   delay(80);
   digitalWrite(LED_11, LOW);
   digitalWrite(LED_8, HIGH);
   delay(80);
   digitalWrite(LED_12, LOW);
   digitalWrite(LED_9, HIGH);
   delay(80);
   digitalWrite(LED_10, HIGH);
   digitalWrite(LED_11, HIGH);
   delay(80);
   digitalWrite(LED_12, LOW);
   delay(80);
   digitalWrite(LED_11, LOW);
   delay(80);
   digitalWrite(LED_10, LOW);
   delay(80);
   digitalWrite(LED_9, LOW);
   digitalWrite(LED_12, HIGH);
   delay(80);
   digitalWrite(LED_8, LOW);
   digitalWrite(LED_11, HIGH);
   delay(80);
   digitalWrite(LED_7, LOW);
   digitalWrite(LED_10, HIGH);
   delay(80);
   digitalWrite(LED_6, LOW);
   digitalWrite(LED_9, HIGH);
   delay(80);
   digitalWrite(LED_5, LOW);
   digitalWrite(LED_8, HIGH);
   delay(80);
   digitalWrite(LED_4, LOW);
   digitalWrite(LED_7, HIGH);
   delay(80);
   digitalWrite(LED_3, LOW);
   digitalWrite(LED_6, HIGH);
   delay(80);
   digitalWrite(LED_2, LOW);
   digitalWrite(LED_5, HIGH);
   delay(80);
   digitalWrite(LED_1, LOW);
   digitalWrite(LED_4, HIGH);
   delay(80);
   digitalWrite(LED_3, HIGH);
   digitalWrite(LED_2, HIGH);
   delay(80);
 }

