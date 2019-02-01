#include <IRremote.h>

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Initialise le recepteur
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, DEC);
    irrecv.resume(); // Recoit la valeur suivante
  }
}
