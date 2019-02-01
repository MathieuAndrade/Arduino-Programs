//Broche connectée au ST_CP du 74HC595
const int verrou = 11;
//Broche connectée au SH_CP du 74HC595
const int horloge = 12;
//Broche connectée au DS du 74HC595
const int data = 10;

void setup() {
  //On met les broches en sortie
  pinMode(verrou, OUTPUT);
  pinMode(horloge, OUTPUT);
  pinMode(data, OUTPUT);
}

void loop() {
  //on affiche les nombres de 0 à 255 en binaire
  for (char i = 0; i < 256; i++) {
    //On active le verrou le temps de transférer les données
    digitalWrite(verrou, LOW);
    //on envoi toutes les données grâce à notre belle fonction
    envoi_ordre(data, horloge, 1, ~i);
    //et enfin on relâche le verrou
    digitalWrite(verrou, HIGH);
    //une petite pause pour constater l'affichage
    delay(1000);
  }
}

void envoi_ordre(int dataPin, int clockPin, boolean sens, char donnee)
{
  for(int i=0; i<8; i++) //on va parcourir chaque bit de l'octet
  {
     //on met l'horloge à l'état bas
     digitalWrite(clockPin, LOW);
     //on met le bit de donnée courante en place
     if(sens)
        digitalWrite(dataPin, donnee & 0x01<<i);
     else
        digitalWrite(dataPin, donnee & 0x80>>i);
     //enfin on remet l'horloge à l'état haut pour faire prendre en compte cette dernière
     digitalWrite(clockPin, HIGH);
  } 
}
