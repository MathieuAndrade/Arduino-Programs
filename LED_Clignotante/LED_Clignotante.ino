const int led_rouge = 2;

void setup() 
{
  pinMode(led_rouge, OUTPUT);
}

void loop() 
{
  digitalWrite(led_rouge, LOW);
  delay(1000);
  digitalWrite(led_rouge, HIGH);
  delay(1000); 
}
