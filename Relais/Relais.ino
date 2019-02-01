int Relais_1 = 2;
int Relais_2 = 4;

bool etat = true;

void setup() 
{ 
  Serial.begin(9600);
  pinMode(Relais_1, OUTPUT); 
  pinMode(Relais_2, OUTPUT);
  digitalWrite(Relais_1, HIGH);
  digitalWrite(Relais_2, HIGH); 
}

void loop() {
  int received; 
  
  if (Serial.available()>0) 
    { 
      received = Serial.read();
                                                                 
    if(received == 'a') 
       {
        etat =! etat;
        digitalWrite(Relais_1, etat);
        digitalWrite(Relais_2, etat);
        delay(100);
        Serial.println("On/Off");
       } 

    }
}
