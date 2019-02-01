#include <VirtualWire.h> // inclusion de la librairie VirtualWire
 
uint8_t buf[VW_MAX_MESSAGE_LEN]; // Tableau qui va contenir le message reçu (de taille maximum VW_MAX_MESSAGE_LEN)
uint8_t buflen = VW_MAX_MESSAGE_LEN; // Taille maximum de notre tableau

 
void setup() // Fonction setup()
{
    Serial.begin(9600); // Initialisation du port série pour avoir un retour sur le serial monitor
    Serial.println("Tuto VirtualWire"); // Petit message de bienvenue

    vw_set_rx_pin(2);
    vw_setup(2000); // initialisation de la librairie VirtualWire à 2000 bauds (note: je n'utilise pas la broche PTT)
    vw_rx_start();  // Activation de la partie réception de la librairie VirtualWire
}
 
void loop() // Fonction loop()
{
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
    }
}
