int OnOff = 2;                                                  // Sortie où sera branchée le boutton On/Off

void setup() {
  Serial.begin(9600);                                            // On initialise la connexion
  pinMode(OnOff, OUTPUT);                                       // Et la sortie du le boutton On/Off
}

void loop() {
  int received;                                                  // Variable servant à récupérer
                                                                 // les données reçues
  if (Serial.available()>0) 
    { 
      received = Serial.read();
                                                                 
    if(received == 'a') 
       {
       digitalWrite(OnOff, HIGH);
       delay(3000);
       Serial.println("On/Off");
    
       } 
  }
}
