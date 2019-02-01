
int oldValue;
int newValue;

int sensor = 12; 

void setup() {
  
  Serial.begin(9600);
  pinMode(sensor, INPUT);
}

void loop() {
  newValue = digitalRead(sensor);

  if(oldValue != newValue){
    sendData(newValue);
    oldValue = newValue;
  }
  
  delay(100);
}

void sendData(int value){
  Serial.print("{\"devicetype\":251, \"value\":");
  Serial.print(value);
  Serial.print("}\n");
}

  
