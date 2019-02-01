/*
 * Chenillard pour Leds branchées sur Pin 6 -> 13 (8 leds)
 */
 
 int NbrLed = 12; // nbre de Leds dans le tableau
 int ledPins[] = { 2,3,4,5,6,7,8,9,10,11,12,13 };  // Tableau contenant les Pins pour les leds
 
 int interval = 80; // // Interval entre deux actions LEDS, 100 ms
 
 void setup(){
   // Activer les pins pour les leds en sortie
   for( int i=0; i<NbrLed; i++ )
     pinMode( ledPins[i], OUTPUT );
 }
 
 void loop(){
   K2000();
 }
 
 
 // Allume et éteind les leds à la façon K2000
 // Un aller retour complet
 void K2000(){
   for( int i=0; i<NbrLed; i++) {
      // Allume uniquement la led, la précédente et la suivante
      // éteind toutes les autres.
      for( int iBrowser=0; iBrowser<NbrLed; iBrowser++ ) 
        if( iBrowser==(i-1) || iBrowser==(i+1) || iBrowser==i )
          digitalWrite( ledPins[iBrowser], LOW );
        else
          digitalWrite( ledPins[iBrowser], HIGH );
      delay( interval );
   }

   for( int i=NbrLed-1; i>=0; i--) {
      // Allume uniquement la led, la précédente et la suivante
      // éteind toutes les autres.
      for( int iBrowser=0; iBrowser<NbrLed; iBrowser++ ) 
        if( iBrowser==(i-1) || iBrowser==(i+1) || iBrowser==i )
          digitalWrite( ledPins[iBrowser], LOW );
        else
          digitalWrite( ledPins[iBrowser], HIGH );
      delay( interval );
   }
   
   // eteind les deux dernières led
   digitalWrite( ledPins[0], HIGH );
   digitalWrite( ledPins[1], HIGH );
}
