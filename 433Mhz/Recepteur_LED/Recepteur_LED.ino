#include <VirtualWire.h> // Vous devez télécharger et installer la librairie VirtualWire.h dans votre dossier "/libraries" !
int led=13;

void setup()
{
    Serial.begin(9600);    
    vw_setup(2000);               // Bits par seconde (vous pouvez le modifier mais cela modifiera la portée). Voir la documentation de la librairie VirtualWire.
    vw_set_rx_pin(2);             // C'est sur cette broche que l'on reliera les broches DATA du récepteur, vous pouvez changez de broche si vous le désirez.
    vw_rx_start();                // On démarre le récepteur.
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
     if (vw_wait_rx_max(200)) // Si un message est reçu dans les 200ms qui viennent
    {
        if (vw_get_message(buf, &buflen)) // On copie le message, qu'il soit corrompu ou non
        {
            Serial.print("RX : ");
            for (byte i = 0; i < buflen; i++) // Si il n'est pas corrompu on l'affiche via Serial
             //Serial.print(buf[i]);   //Conversion ASCII
             {Serial.print(buf[i]- '0');   //Conversion ASCII des chiffres 0-9
             }
             Serial.println("");
        }
    
            
    if (buf[1] == '1' ){
      digitalWrite(led, HIGH);
    }
    
    if (buf[1] == '2' ){
      digitalWrite(led, LOW);
    }
  
  }
}
