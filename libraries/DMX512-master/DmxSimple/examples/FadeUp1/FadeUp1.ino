/* Welcome to DmxSimple. This library allows you to control DMX stage and
** architectural lighting and visual effects easily from Arduino. DmxSimple
** is compatible with the Tinker.it! DMX shield and all known DIY Arduino
** DMX control circuits.
**
** DmxSimple is available from: http://code.google.com/p/tinkerit/
** Help and support: http://groups.google.com/group/dmxsimple       */

/* To use DmxSimple, you will need the following line. Arduino will
** auto-insert it if you select Sketch > Import Library > DmxSimple. */

#include <DmxSimple.h>

void setup() {
  /* The most common pin for DMX output is pin 3, which DmxSimple
  ** uses by default. If you need to change that, do it here. */
  DmxSimple.usePin(3);

  /* DMX devices typically need to receive a complete set of channels
  ** even if you only need to adjust the first channel. You can
  ** easily change the number of channels sent here. If you don't
  ** do this, DmxSimple will set the maximum channel number to the
  ** highest channel you DmxSimple.write() to. */
 //DmxSimple.maxChannel(6);
 DmxSimple.write(1, 255);
}

void loop() {
  int brightness;
  for (brightness = 0; brightness <= 255; brightness--) {
    DmxSimple.write(2,100); //Channel 2 to control red light 
    DmxSimple.write(3,brightness); //Channel 3 to control green light 
    DmxSimple.write(4,255); //Channel 2 to control blue light 
    DmxSimple.write(6,brightness); //Channel 6 to control motor
    /* Small delay to slow down the ramping */
    delay(5);
  }
  
  
}
