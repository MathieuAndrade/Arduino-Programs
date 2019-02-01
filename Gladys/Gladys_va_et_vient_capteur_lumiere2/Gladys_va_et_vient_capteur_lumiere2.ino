#include <ESP8266WiFi.h>

const char* ssid = "Livebox-2663.2";
const char* password = "uASXG9a8gN78Z92xrt8c";

String requete = "GET /devicestate/create?devicetype=109&value=";
String token = "&token=c654aba88e14c89d0066806601759f01c997aae7";

const char * iprp = "192.168.1.17";
const uint16_t portrp = 8080;

bool etat = true;
int Relais1 = D1;
int Relais2 = D2;

int sensor = A0;
int sensorvalue = 0;
int sensortest = 0;

WiFiServer server(4200);

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(sensor, INPUT);
  pinMode(Relais1, OUTPUT);
  digitalWrite(Relais1, HIGH);
  pinMode(Relais2, OUTPUT);
  digitalWrite(Relais2, HIGH);
  
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
  
  server.begin();
  Serial.println("Server started");

  Serial.println(WiFi.localIP());
}

void loop() {

   WiFiClient client = server.available();
   if (!client) {
    test();
    return;
  }
  
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  if (req.indexOf("/?r=0") != -1 || req.indexOf("/?r=1") != -1)
    etat =! etat;
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  digitalWrite(Relais1, etat);
  digitalWrite(Relais2, etat);
  maj();
  client.flush();
  delay(1);
  Serial.println("Client disonnected");

}

void test(){
  if(analogRead(sensor) < 300){
    sensorvalue = 0;
  }
  else if(analogRead(sensor) > 500){
    sensorvalue = 1;
  }
  if(sensorvalue != sensortest){
    Serial.println(sensorvalue);
    rafraichir();
    sensortest = sensorvalue;
    }
   delay(100);
  }

  
void rafraichir(){
  WiFiClient client;
  if(client.connect(iprp, portrp)){
    client.print(requete);
    client.print(sensorvalue);
    client.println(token);
    client.println();
    client.stop();
    Serial.println("Envoyé!");   
    }
    else(Serial.println("Erreur!"));
  }

void maj(){
  if(analogRead(sensor) < 300){
    sensorvalue = 0;
  }
  else if(analogRead(sensor) > 500){
    sensorvalue = 1;
  }
  if(sensorvalue != sensortest){
    sensortest = sensorvalue;
    }
   delay(100);
  }
