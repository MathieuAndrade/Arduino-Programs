//  _ ___ _______     ___ ___ ___  ___ _   _ ___ _____ ___ 
// / |_  )__ /   \   / __|_ _| _ \/ __| | | |_ _|_   _/ __| 
// | |/ / |_ \ |) | | (__ | ||   / (__| |_| || |  | | \__ \ 
// |_/___|___/___/   \___|___|_|_\\___|\___/|___| |_| |___/ 
// 
// The Unnamed Circuit
// 
// Made by Mathieu Andrade
// License: CC-BY-SA 3.0
// Downloaded from: https://123d.circuits.io/circuits/1310312-the-unnamed-circuit

void setup() {
  Serial.begin(9600); // initialise la communication série
  // vérifier que le débit utiliser est le même dans le Terminal Série

  pinMode(2, INPUT); // met la broche 2 en sortie
}

void loop() {
  int sensorValue = digitalRead(2); // lit l'état de la broche 2 et met le résultat dans la variable
  
  if((sensorValue) == 1 )
  {
    Serial.println("allumer");
  }
  
  if((sensorValue) == 0 )
  {
    Serial.println("Eteint");
  }
}
