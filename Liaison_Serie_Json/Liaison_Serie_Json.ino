void setup() 
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("{\"devicetype\":\"111\",\"value\":"); 
  Serial.print(1); 
  Serial.print("}\n");

	delay(5000); //on attend 5 secondes avant de renvoyer l'alphabet
}  

