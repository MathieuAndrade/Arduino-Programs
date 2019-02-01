const byte pinX = A0;
const byte pinY = A1;
const byte pinButton = 7;
const int LED_1 = 2;
const int LED_2 = 3;
const int LED_3 = 4;
const int LED_4 = 5;

void setup(){
  Serial.begin(9600);
  pinMode(pinButton,INPUT); 
  digitalWrite(pinButton,HIGH);
  pinMode(pinX,INPUT); 
  pinMode(pinY,INPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);
  digitalWrite(LED_3, HIGH);
  digitalWrite(LED_4, HIGH);
}
 
void loop (){
  int coordX = analogRead(pinX);
  int coordY = analogRead(pinY);
  boolean buttonState = digitalRead(pinButton);
  
  if(coordX > 600)
  {
    digitalWrite(LED_3, LOW);
  }
  else
  {
    digitalWrite(LED_3, HIGH);
  }
  
  
  if(coordX < 460)
  {
    digitalWrite(LED_2, LOW);
  }
  else
  {
    digitalWrite(LED_2, HIGH);
  }
  
  
  if(coordY > 600)
  {
    digitalWrite(LED_4, LOW);
  }
  else
  {
    digitalWrite(LED_4, HIGH);
  }
  
  
  if(coordY < 460)
  {
    digitalWrite(LED_1, LOW);
  }
  else
  {
    digitalWrite(LED_1, HIGH);
  }
  
  if(buttonState == LOW)
  {
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
  }
  else
  {
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
  }
}
