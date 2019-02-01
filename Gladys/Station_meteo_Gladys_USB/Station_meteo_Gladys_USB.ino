#include <DHT.h>
#include <DHT_U.h>


#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE); 

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {GetHumidityAndTeperature();}

void GetHumidityAndTeperature() 
{
int humidity = dht.readHumidity();  
int temperature = dht.readTemperature();  

Serial.print("{\"devicetype\":\"77\",\"value\":");  
Serial.print(temperature);  
Serial.print("}\n");  

Serial.print("{\"devicetype\":\"78\",\"value\":");  
Serial.print(humidity);  
Serial.print("}\n");  

delay(60000);
}
