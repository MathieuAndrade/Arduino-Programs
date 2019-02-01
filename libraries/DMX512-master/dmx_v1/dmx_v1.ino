/* Controle d'un projecteur DMX512 à leds 4 cannaux DMX
   canal 1 : puissance globale; canal 2 : rouge; canal 3 : vert; canal 4 : bleu
   Une sequence de touches commande séparement chaque canal :
 * m diminue; p augemnte la puissance générale du projecteur
 * a diminue; z augmente; e blackout le canal 2
 * q diminue; s augmente; d blackout le canal 3
 * w diminue; x augmente; c blackout le canal 4
PS : le canal de consigne du projecteur doit etre sur la valeur 1
Si vous souhaitez une autre valeur de début de canal, 
il faut changer les valeurs du code source en conséquence

By François
 */

#include <DmxSimple.h>

byte byteRead;

int puissance = 255; 
int couleurRouge = 0;
int couleurVert = 0;  
int couleurBleu = 0;

void setup() {
    Serial.begin(9600); // 115200 Reactivité.
    DmxSimple.usePin(5);


    DmxSimple.write(1, 255);
    DmxSimple.write(2, couleurRouge);
    DmxSimple.write(3, couleurVert);
    DmxSimple.write(4, couleurBleu);
    delay(50);
    DmxSimple.write(1, 0);
    delay(100);
    DmxSimple.write(1, 255);
}

void loop() {

    if (Serial.available()) {

        byteRead = Serial.read();


        // Puissance générale
        if(byteRead == 109) { // m
            Serial.println("Puissance : diminuer");      
            puissance-=10;
            if(puissance>0) {
                DmxSimple.write(1,puissance);
            }
        }
        if(byteRead == 112){ // p
            Serial.println("Puissance : augmenter");

            puissance+=10;
            if (puissance < 255) {
                DmxSimple.write(1,puissance);
            }
        }


        // Couleur Rouge
        if(byteRead == 97) { // a
            Serial.println("Rouge : diminuer");      
            couleurRouge-=10;
            if(couleurRouge>0) {
                DmxSimple.write(2,couleurRouge);
            }
        }
        if(byteRead == 122){ // z
            Serial.println("Rouge : augmenter");

            couleurRouge+=10;
            if (couleurRouge < 255) {
                DmxSimple.write(2,couleurRouge);
            }
        }

        if(byteRead == 101) { // e
            Serial.println("Rouge : arret");      
            couleurRouge=0;

            DmxSimple.write(2,couleurRouge);

        }


        // Couleur Vert
        if(byteRead == 113) { // q
            Serial.println("Vert : diminuer");      
            couleurVert-=10;
            if(couleurVert>0) {
                DmxSimple.write(3,couleurVert);
            }
        }
        if(byteRead == 115){ // s
            Serial.println("Vert  augmenter");

            couleurVert+=10;
            if (couleurVert < 255) {
                DmxSimple.write(3,couleurVert);
            }
        }

        if(byteRead == 100) { // d
            Serial.println("Vert : arret");      
            couleurVert=0;

            DmxSimple.write(3,couleurVert);

        }

        // Couleur Bleu
        if(byteRead == 119) { // w
            Serial.println("Bleu : diminuer");      
            couleurBleu-=10;
            if(couleurBleu>0) {
                DmxSimple.write(4,couleurBleu);
            }
        }
        if(byteRead == 120){ // x
            Serial.println("Bleu : augmenter");

            couleurBleu+=10;
            if (couleurBleu < 255) {
                DmxSimple.write(4,couleurBleu);
            }
        }
        if(byteRead == 99) { // c
            Serial.println("bleu : arret");      
            couleurBleu=0;

            DmxSimple.write(4,couleurBleu);

        }





    }


}
