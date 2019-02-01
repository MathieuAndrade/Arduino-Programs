** <number>c : Select DMX channel
** <number>v : Set DMX channel to new value
**
** These can be combined. For example:
** 100c355w : Set channel 100 to value 255.
**
** For more details, and compatible Processing sketch,
** visit http://code.google.com/p/tinkerit/wiki/SerialToDmx
**
** Help and support: http://groups.google.com/group/dmxsimple       */

#include <DmxSimple.h>

void setup() {
  Serial.begin(9600);
}

int value = 0;
int channel;

void loop() {
  int c;

  while(!Serial.available());
  c = Serial.read();
  
  if ((c>='0') && (c<='9')) 
  {
    value = 10*value + c - '0';
  } 
  
  else {
    if (c=='c') channel = value;
    else if (c=='w') {
      DmxSimple.write(channel, value);
      Serial.println();
    }
    value = 0;
  }
}
