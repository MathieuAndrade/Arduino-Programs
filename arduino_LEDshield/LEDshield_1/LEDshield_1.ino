//  _ ___ _______     ___ ___ ___  ___ _   _ ___ _____ ___ 
// / |_  )__ /   \   / __|_ _| _ \/ __| | | |_ _|_   _/ __| 
// | |/ / |_ \ |) | | (__ | ||   / (__| |_| || |  | | \__ \ 
// |_/___|___/___/   \___|___|_|_\\___|\___/|___| |_| |___/ 
// 
// LED shield
// 
// Made by Karel Bruneel
// License: CC-BY-SA 3.0
// Downloaded from: http://123d.circuits.io/circuits/19376-led-shield

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(0, OUTPUT);     
  pinMode(1, OUTPUT);     
  pinMode(2, OUTPUT);     
  pinMode(3, OUTPUT);     
  pinMode(4, OUTPUT);     
  pinMode(5, OUTPUT);     

  pinMode(8, INPUT);     
}

int led =0;
// the loop routine runs over and over again forever:
void loop() {
  if (digitalRead(8)) {
    for(int i=0; i<6;i++) {
      if(i==led) {
        digitalWrite(i,HIGH);
      } else {
        digitalWrite(i,LOW);
      }  
    }
    led++;
    if (led > 5) led = 0;
  } else {
    for(int i=0; i<6;i++) {
      digitalWrite(i,HIGH);
    }
  }
  delay(1000);               // wait for a second
}
