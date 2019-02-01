#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

// Host of your Raspberry Pi hosting Gladys
String host = "Host: 192.168.1.17";
IPAddress server(192, 168, 1, 17); // numeric IP

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 1, 177);

// Your request
String requestTemperature = "GET /devicestate/create?token=2a9e573e82e618785830b1b557bc1ead2c258f39&devicetype=6&value=%VALUE";
String requestHumidity = "GET /devicestate/create?token=2a9e573e82e618785830b1b557bc1ead2c258f39&devicetype=7&value=%VALUE";

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetClient client;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
}

void loop() {
  temperature();
  humidity();
  delay(10000);
}

void temperature(){ 
  
    float t = dht.readTemperature();
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t)) {
    Serial.println("Failed to read from DHT");
  } 
  else {
    Serial.println("connecting...");
    // if you get a connection, report back via serial:
    if (client.connect(server, 80)) {
      Serial.println("connected");
      // Make a HTTP request:

      String temperature = String(t, 0);

      // replacing URL with the value
      requestTemperature.replace("%VALUE", temperature);

      Serial.println(requestTemperature);

      client.println(requestTemperature);
      client.println(host);
      client.println("Connection: close");
      client.println();

      Serial.println();
      Serial.println("disconnecting.");
      client.stop();
    } 
    
    else {
      // if you didn't get a connection to the server:
      Serial.println("connection failed");
    }
    delay(1000);
  }
}

void humidity () {
  
    float h = dht.readHumidity();
      if (isnan(h)) {
    Serial.println("Failed to read from DHT");
  } 
  
  else {
    Serial.println("connecting...");
    // if you get a connection, report back via serial:
    if (client.connect(server, 80)) {
      Serial.println("connected");
      // Make a HTTP request:

      String humidity = String(h, 0);

      // replacing URL with the value
      requestHumidity.replace("%VALUE", humidity);

      Serial.println(requestHumidity);

      client.println(requestHumidity);
      client.println(host);
      client.println("Connection: close");
      client.println();
      Serial.println();
      Serial.println("disconnecting.");
      client.stop();
    } 
    
    else {
      // if you didn't get a connection to the server:
      Serial.println("connection failed");
    }

    delay(1000);

  }
}
