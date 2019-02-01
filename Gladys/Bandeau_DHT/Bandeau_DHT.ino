#include <ESP8266WiFi.h>
#include <DHT.h>

const char* ssid = "Livebox-2663.2";
const char* password = "uASXG9a8gN78Z92xrt8c";

const char * gladys_ip = "192.168.1.17";
const uint16_t gladys_port = 8080;

WiFiServer server(4200);
WiFiClient client;

#define DHTPIN 2
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

float oldValueTemp;
float oldValueHum;

long humidityTime;
long humidityDelay = 3600000;

String requestTemperature = "GET /devicestate/create?token=1fac9697a079944e7215b9c892a6fa801a826fff&devicetype=2&value=%VALUE";
String requestHumidity = "GET /devicestate/create?token=1fac9697a079944e7215b9c892a6fa801a826fff&devicetype=3&value=%VALUE";

void setup() {
  Serial.begin(115200);
  humidityTime = millis();
  
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
  
  server.begin();
  Serial.println("Server started");
  
  Serial.println(WiFi.localIP());
}

void loop() {

  client = server.available();
  if (!client) {
    testTemperature();
    //testHumidity();
    return;
  }
  
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  Serial.println("Client disonnected");
}

void testTemperature(){

   float t = dht.readTemperature();
   if (isnan(t)) {
    Serial.println("Failed to read from DHT");
  } else if (t != oldValueTemp){
    Serial.println(t);
    oldValueTemp = t;
    //sendTemperature(t);
  }
  delay(2000);
}

void testHumidity(){

   float h = dht.readHumidity();
   if (isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else if (h != oldValueHum && millis() - humidityTime > humidityDelay) {
    oldValueHum = h;
    humidityTime = millis();
    sendHumidity(h);
  }
  delay(2000);
}

void sendTemperature(float t){
  
  Serial.println("connecting...");
  
  if (client.connect(gladys_ip, gladys_port)) {
    
    Serial.println("connected");
    String temperature = String(t, 0);
    requestTemperature.replace("%VALUE", temperature);
    Serial.println(requestTemperature);
    client.println(requestTemperature);
    client.println("Connection: close");
    client.println();
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    
  }else {
    Serial.println("connection failed");
  }
  delay(1000);
}

void sendHumidity (float h) {
  
  Serial.println("connecting...");
  
  if (client.connect(gladys_ip, gladys_port)) {
    
    Serial.println("connected");
    String humidity = String(h, 0);
    requestHumidity.replace("%VALUE", humidity);
    Serial.println(requestHumidity);
    client.println(requestHumidity);
    client.println("Connection: close");
    client.println();
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    
  }else {
    Serial.println("connection failed");
  }
  delay(1000);
}
