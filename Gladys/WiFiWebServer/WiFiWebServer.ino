#include <ESP8266WiFi.h>

const char* ssid = "Livebox-2663.2";
const char* password = "uASXG9a8gN78Z92xrt8c";
bool etat = true;
int Relais1 = D1;
int Relais2 = D2;

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(4200);

void setup() {
  Serial.begin(115200);
  delay(10);

  // prepare GPIO2
  pinMode(Relais1, OUTPUT);
  digitalWrite(Relais1, HIGH);
  pinMode(Relais2, OUTPUT);
  digitalWrite(Relais2, HIGH);
  
  // Connect to WiFi network
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
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  if (req.indexOf("/r=2") != -1)
    etat =! etat;
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  // Set GPIO2 according to the request
  digitalWrite(Relais1, etat);
  digitalWrite(Relais2, etat);
  
  client.flush();
  delay(1);
  Serial.println("Client disonnected");
}

