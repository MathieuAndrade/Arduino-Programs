#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
 
YunServer server;
 
void setup() {
  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();
}
 
void loop() {
  YunClient client = server.accept();
 
  if (client) {
    String command = client.readString();
    command.trim();
    if (command == "valeur") {
      int val = analogRead(A1);
      client.print(val);
    }
    client.stop();
  }
 
  delay(50);
}
