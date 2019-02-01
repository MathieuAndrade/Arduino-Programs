#include <math.h>
 
void setup() {
 Serial.begin(9600); // ce taux dépend de votre carte Arduino
}
 
void loop() {
  // 0 est le port analogique sur lequel est branché mon capteur de température
  Serial.println( int( getTemp( analogRead( 0 ) ) ) ); 
  // On attend 1 seconde
  delay(1000);
}
 
double getTemp(int rawData) {
  double temperature = log( ( ( 10240000 / rawData ) - 10000 ) );
  temperature = 1 / (0.001129148 + (0.000234125 * temperature) +
                      (0.0000000876741 * temperature * temperature * temperature));
  // Convert Kelvin to Celcius
  temperature = temperature - 273.15;
  return temperature;
}
