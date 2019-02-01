int sensorValue;
 
void setup()
{
  Serial.begin(9600); // starts the serial port at 9600
}
 
void loop()
{
  sensorValue = analogRead(A0); // read analog input pin 0
  Serial.println(sensorValue);
  delay(3000); // wait 100ms for next reading
}
