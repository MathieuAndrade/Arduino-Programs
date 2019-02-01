int LED_1 = 5;
int LED_2 = 3;
int LED_3 = 6;
int LED_4 = 9;
void setup() 
{
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
}

void loop() 
{
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5)
  {
    analogWrite(LED_1, fadeValue);
    delay(30);
  }
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5)
  {
    analogWrite(LED_2, fadeValue);
    delay(30);
  }
  
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5)
  {
    analogWrite(LED_1, fadeValue);
    digitalWrite(LED_1, HIGH);
    delay(30);
  }
  
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5)
  {
    analogWrite(LED_3, fadeValue);
    delay(30);
  }
  
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5)
  {
    analogWrite(LED_2, fadeValue);
    digitalWrite(LED_2, HIGH);
    delay(30);
  }
  
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5)
  {
    analogWrite(LED_4, fadeValue);
    delay(30);
  }
  
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5)
  {
    analogWrite(LED_3, fadeValue);
    digitalWrite(LED_3, HIGH);
    delay(30);
  }
  
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5)
  {
    analogWrite(LED_4, fadeValue);
    digitalWrite(LED_4, HIGH);
    delay(30);
  }
}

