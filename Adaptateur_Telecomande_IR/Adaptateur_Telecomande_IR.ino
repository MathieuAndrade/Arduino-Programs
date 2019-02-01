#include <IRremote.h>

int receiver = 2;

IRrecv irrecv(receiver); 
decode_results results;
IRsend irsend;



void setup() 
{
  irrecv.enableIRIn();
}

void loop() 
{
  if (irrecv.decode(&results))
  {
    translateIR(); 
    irrecv.resume(); 
   }
}

void translateIR()
{
  switch(results.value)
  {
    case 0x1CE338C7: irsend.sendSony(0x20DF10EF, 3); break;  // Marche/Arret
    case 0x1CE300FF: irsend.sendSony(0x20DF08F7, 3); break;  // 0
    case 0x1CE3807F: irsend.sendSony(0x20DF8877, 3); break;  // 1
    case 0x1CE340BF: irsend.sendSony(0x20DF48B7, 3); break;  // 2
    case 0x1CE3C03F: irsend.sendSony(0x20DFC837, 3); break;  // 3
    case 0x1CE320DF: irsend.sendSony(0x20DF28D7, 3); break;  // 4
    case 0x1CE3A05F: irsend.sendSony(0x20DFA857, 3); break;  // 5
    case 0x1CE3609F: irsend.sendSony(0x20DF6897, 3); break;  // 6
    case 0x1CE3E01F: irsend.sendSony(0x20DFE817, 3); break;  // 7
    case 0x1CE310EF: irsend.sendSony(0x20DF18E7, 3); break;  // 8
    case 0x1CE3906F: irsend.sendSony(0x20DF9867, 3); break;  // 9
    case 0x1CE3A857: irsend.sendSony(0x20DF906F, 3); break;  // Mute
    case 0x1CE36897: irsend.sendSony(0x20DF40BF, 3); break;  // Vol +
    case 0x1CE3E817: irsend.sendSony(0x20DFC03F, 3); break;  // Vol -
    case 0x1CE330CF: irsend.sendSony(0x20DF00FF, 3); break;  // Ch +
    case 0x1CE3B04F: irsend.sendSony(0x20DF807F, 3); break;  // Ch -
    case 0x1CE3D827: irsend.sendSony(0x20DFE01F, 3); break;  // Fleche Gauche
    case 0x1CE350AF: irsend.sendSony(0x20DF609F, 3); break;  // Fleche Droite
    case 0x1CE3F807: irsend.sendSony(0x20DF02FD, 3); break;  // Fleche Haut
    case 0x1CE37887: irsend.sendSony(0x20DF827D, 3); break;  // Flache Bas 
    case 0x1CE358A7: irsend.sendSony(0x20DF22DD, 3); break;  // OK
    case 0x1CE38877: irsend.sendSony(0x20DFC23D, 3); break;  // Menu
    case 0x1CE3B847: irsend.sendSony(0x20DFDA25, 3); break;  // Exit
    case 0x1CE328D7: irsend.sendSony(0x20DFD02F, 3); break;  // AV
    case 0x1CE308F7: irsend.sendSony(0x20DF708F, 3); break;  // Sleep 
    case 0x1CE318E7: irsend.sendSony(0x20DF55AA, 3); break;  // Info
    
    case 0xFFFFFFFF: Serial.print("ok"); break;
  }

}
