int duration;
int distance;
int sensorpin = 7;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  pinMode(sensorpin, OUTPUT);
  digitalWrite(sensorpin, LOW);
  delayMicroseconds(2);
  digitalWrite(sensorpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorpin, LOW);
  pinMode(sensorpin, INPUT);
  duration = pulseIn(sensorpin, HIGH);
  distance = duration/58;
  Serial.println(distance);
  delay(100);  
}
