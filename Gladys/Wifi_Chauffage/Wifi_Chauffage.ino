#include <ESP8266WiFi.h>

const char* ssid = "Livebox-2663.2";
const char* password = "uASXG9a8gN78Z92xrt8c";
bool etat = true;
int Button = D1;
int Led = D2;
int maj = 0;
int sensor_value;
int sensor_test = 0;

String requete = "GET /devicestate/create?devicetype=79&value=";
String token = "&token=cf1769547e3378b6cbe530c8499fad5bc6fe9a2b";
const char * gladys_ip = "192.168.1.17";
const uint16_t gladys_port = 8080;

WiFiServer server(4200);

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(Button, OUTPUT);
  digitalWrite(Button, LOW);
  pinMode(Led, INPUT);
  digitalWrite(Led, LOW);
  
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
  
  WiFiClient client = server.available();
  if (!client) {
    if(maj == 0){
      testLed();
      }
    return;
  }
  
  while(!client.available()){
    delay(1);
  }
  
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  if (req.indexOf("/?r=0") != -1){
    if(etat != false){
          etat = false;
          digitalWrite(Button, HIGH);
          Serial.println(HIGH);
          delay(100);
          digitalWrite(Button, LOW);
          Serial.println(LOW);
      }

    }else if (req.indexOf("/?r=1") != -1){
      if(etat != true){
        etat = true;
        digitalWrite(Button, HIGH);
        Serial.println(HIGH);
        delay(100);
        digitalWrite(Button, LOW);
        Serial.println(LOW);
        }
      }else {
        Serial.println("invalid request");
        client.stop();
        return;
        }
  
  client.flush();
  delay(1);
  Serial.println("Client disonnected");
}

void testLed(){
  sensor_value = digitalRead(Led);
  if (sensor_value != sensor_test){
    sensor_value = digitalRead(Led);
      if (sensor_value == sensor_test){
        sensor_value = digitalRead(Led);
          if (sensor_value != sensor_test){
            sensor_value = digitalRead(Led);
              if (sensor_value == sensor_test){
                sensor_value = digitalRead(Led);
                if (sensor_value == sensor_test){
                    sensor_test == sensor_value;
                    rafraichir;
                  }
                }
            }
        }
    }
}

void rafraichir(){
  WiFiClient client;
  if(client.connect(gladys_ip, gladys_port)){
    client.print(requete);
    client.print(sensor_value);
    client.println(token);
    client.println();
    client.stop();
    Serial.println("Envoyé!");   
    }
    else(Serial.println("Erreur!"));
  }

