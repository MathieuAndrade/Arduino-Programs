#include <IRremote.h>

int receiver = 2; 

IRrecv irrecv(receiver);           // create instance of 'irrecv'
decode_results results;            // create instance of 'decode_results'
/*-----( Declare Variables )-----*/


void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
//    Serial.println(results.value, HEX);  UN Comment to see raw values
    translateIR(); 
    irrecv.resume(); // receive the next value
  }  
}/* --(end main loop )-- */

/*-----( Declare User-written Functions )-----*/
void translateIR() // takes action based on IR code received

// describing KEYES Remote IR codes 

{

  switch(results.value)

  {

  case 0x20DF02FD: Serial.println(" FLECHE DU HAUT"); break;
  case 0x20DF609F: Serial.println(" FLECHE DU DROITE");    break;
  case 0x20DF827D: Serial.println(" FLECHE DU BAS");    break;
  case 0x20DFE01F: Serial.println(" FLECHE DE GAUCHE");   break;
  case 0x2F0: Serial.println(" FLECHE DU HAUT"); break;
  case 0xCD0: Serial.println(" FLECHE DE DROITE");    break;
  case 0xAF0: Serial.println(" FLECHE DU BAS");    break;
  case 0x2D0: Serial.println(" FLECHE DE GAUCHE");    break;

  case 0xFFFFFFFF: Serial.println("REPEAT");break;  

  default: 
    Serial.println(" other button   ");

  }// End Case

  delay(500); // Do not get immediate repeat


} //END translateIR



/* ( THE END ) */


