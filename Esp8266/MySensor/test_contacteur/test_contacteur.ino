
#define MY_DEBUG
#define MY_BAUD_RATE 9600
#define MY_GATEWAY_ESP8266
#define MY_ESP8266_SSID "Livebox-2663.2"
#define MY_ESP8266_PASSWORD "uASXG9a8gN78Z92xrt8c"
#define MY_PORT 9999

#define MY_GATEWAY_MAX_CLIENTS 2

#include <ESP8266WiFi.h>
#include <MySensors.h>

#define CHILD_ID_CONTACTEUR 0
#define CONTACTEUR_PIN 13          // Broche sur laquelle est attaché le contacteur 
MyMessage msgContacteur(CHILD_ID_CONTACTEUR, V_TRIPPED);

#define RELAY_ON 1  // GPIO value to write to turn on attached relay
#define RELAY_OFF 0
 
void setup() {
  pinMode(CONTACTEUR_PIN, INPUT);
  digitalWrite(CONTACTEUR_PIN, HIGH);
}
 
void presentation() {
  sendSketchInfo("Relai_Lumiere_Chambre", "1.0");
  present(CHILD_ID_CONTACTEUR, S_BINARY); 
}
 
 
void loop(const MyMessage& message) 
{
    // We only expect one type of message from controller. But we better check anyway.
  if (message.type==V_STATUS) {
    // Change relay state
    digitalWrite(message.sensor-1+CONTACTEUR_PIN, message.getBool()?RELAY_ON:RELAY_OFF);
    // Store state in eeprom
    saveState(message.sensor, message.getBool());
    // Write some debug info
    Serial.print("Incoming change for sensor:");
    Serial.print(message.sensor);
    Serial.print(", New status: ");
    Serial.println(message.getBool());
  }
}


