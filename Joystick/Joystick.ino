const byte pinX = A0;
const byte pinY = A1;
const byte pinButton = 7;
void setup(){
  Serial.begin(9600);
  pinMode(pinButton,INPUT); 
  digitalWrite(pinButton,HIGH);
  pinMode(pinX,INPUT); 
  pinMode(pinY,INPUT); 
}
 
void loop (){
  int coordX = analogRead(pinX);
  int coordY = analogRead(pinY);
  boolean buttonState = digitalRead(pinButton);
  Serial.print("Coordenada X: ");
  Serial.print(coordX);
  Serial.print(" Coordenada Y: ");
  Serial.print(coordY);
  Serial.print(" Pulsador: ");
  Serial.print(buttonState);
  Serial.println(" ");
}
