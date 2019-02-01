int sensorvalue = 0;
int sensortest = 0;
int sensor = A0;
 
void setup()
{
  Serial.begin(9600); // starts the serial port at 9600
}
 
void loop()
{
  if(analogRead(sensor) < 300){
    sensorvalue = 0;
  }
  else if(analogRead(sensor) > 500){
    sensorvalue = 1;
  }
  if(sensorvalue != sensortest){
    Serial.println(sensorvalue);
    sensortest = sensorvalue;
    }

}
