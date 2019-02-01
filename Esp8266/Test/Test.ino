/*
 *  Simple HTTP get webclient test
 */
 
#include <ESP8266WiFi.h>
 
const char* ssid     = "Livebox-2663.2";
const char* password = "uASXG9a8gN78Z92xrt8c";
 
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(100);
 
  // We start by connecting to a WiFi network
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void loop() {
  
  WiFiClient client = server.available();
  if (!client) {
  return;
  }

  Serial.println("new client");
  while(!client.available()){
  delay(1);
  }

  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
}
