#include <VirtualWire.h> // Vous devez télécharger et installer la librairie VirtualWire.h dans votre dossier "/libraries" !


void setup()
{
    Serial.begin(9600);
    vw_setup(2000);               // Bits par seconde (vous pouvez le modifier mais cela modifiera la portée). Voir la documentation de la librairie VirtualWire.
    vw_set_tx_pin(12);             // La broche 3 sera utilisée pour transmettre la DATA, vous pouvez changez de broche si vous le désirez.
}

void loop()
{
  if (Serial.read() == 'A' ){
   const char *msg="on";                        // C'est le message à envoyer.
   vw_send((uint8_t *)msg, strlen(msg));
   vw_wait_tx();
delay(200);   // On attend que le message complet soit envoyé.
 }
 
 else if (Serial.read() == 'B' ){
   const char *msg="off";
   vw_send((uint8_t *)msg, strlen(msg));
   vw_wait_tx(); 
   delay(200);
 }
 else{
 }
}
