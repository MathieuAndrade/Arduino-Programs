#include <ESP8266WiFi.h>
#include <DHT.h>

const char* ssid = ""; // Your SSID 
const char* password = ""; // Tour wifi password

#define DHTPIN 2 // Pin of DHT sensor
#define DHTTYPE DHT11   // Type of your DHT sensor, by default DHT11
DHT dht(DHTPIN, DHTTYPE);

String requestTemperature = "GET /devicestate/create?token=YOUR_TOKEN&devicetype=YOUR_DEVICETYPE_ID&value=%VALUE";
String requestHumidity = "GET /devicestate/create?token=YOUR_TOKEN&devicetype=YOUR_DEVICETYPE_ID&value=%VALUE";

// Create an instance of the server
// Specify the port to listen on as an argument
WiFiServer server(4200);

void setup() {
  Serial.begin(115200);
  delay(10);
  
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
  
  WiFiClient client = server.available();

  while(!client.available()){
    delay(1);
  }

  /**
   * Temperature
   */

  float t = dht.readTemperature();
  // Check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.println("connecting...");
    // If you get a connection, report back via serial:
    if (client.connect(server, 80)) {
      Serial.println("connected");
      // Make a HTTP request:

      String temperature = String(t, 0);

      // Replacing URL with the value
      requestTemperature.replace("%VALUE", temperature);

      Serial.println(requestTemperature);

      client.println(requestTemperature);
      client.println(host);
      client.println("Connection: close");
      client.println();

      Serial.println();
      Serial.println("disconnecting.");
      client.stop();
    } else {
      // If you didn't get a connection to the server:
      Serial.println("connection failed");
    }
    delay(1000);
  }

   /**
   * Humidity
   */

  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.println("connecting...");
    // If you get a connection, report back via serial:
    if (client.connect(server, 80)) {
      Serial.println("connected");
      // Make a HTTP request:

      String humidity = String(h, 0);

      // Replacing URL with the value
      requestHumidity.replace("%VALUE", humidity);

      Serial.println(requestHumidity);

      client.println(requestHumidity);
      client.println(host);
      client.println("Connection: close");
      client.println();
      Serial.println();
      Serial.println("disconnecting.");
      client.stop();
    } else {
      // If you didn't get a connection to the server:
      Serial.println("connection failed");
    }
    delay(1000);
  }
  
  delay(10000);
}
