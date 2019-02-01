/* ------------------------------------------------------------------------------------------------------------------------------------------------------------

   thermostatduino.pde v1.0 - march 2010
   Temperature control for repraps machines hot-plates
   François Delègue - http://reprapide.fr
   
   CC-GNU GPL - Creative Commons GNU / General Public License
   http://creativecommons.org/licenses/GPL/2.0/deed.en
   
   -uses TMP36 IC to measure ambiant temperature
   -uses RepRap 100K thermistor (EPCOS 4085) to measure hot plate temperature
   -uses relay to power on/off heating resistors
   -uses 2 push buttons to set target temperature
   -uses standard 2x16 LCD to display information

   Imported libraries:
   -Bounce (push-buttons signal cleaning)
   -LiquidCrystal (LCD display)
   -WString (strings manipulation)

   Todo list:
   -implement a third button to register target temperature
   -implement a fourth button to power on/off heating resistors (instead of using setting temp buttons)
   -implement red led to be installed near the hot plate, signaling if plate is hot (> 45° for example)

------------------------------------------------------------------------------------------------------------------------------------------------------------ */

/*
   libraries
*/
#include <WString.h>
#include <LiquidCrystal.h>
#include <Bounce.h>
// #include <EEPROM.h>

/*
   setting pins
*/
const int relayCommandPin = 2;         // out
const int decreaseTempButtonPin = 3;   // in
const int increaseTempButtonPin = 4;   // in

const int TMP36Pin = 2;        // in
const int thermistorPin = 0;   // in

/*
   lcd init & string vars
*/
LiquidCrystal lcd (7,8,9,10,11,12);

String firstLCDLine;
String secondLCDLine;

/*
   bounce init
*/
Bounce increaseTempButton = Bounce (increaseTempButtonPin, 5);
Bounce decreaseTempButton = Bounce (decreaseTempButtonPin, 5);

/*
   temperatures vars
*/
int targetTemp = 105;
int oldTargetTemp;

const int maximumTemp = 130;
const int minimumTemp = 10;

float currentTemperature;
float previousTemperature;

const int tempAddressIntoMemory = 0;

// delays for setting/reading target temperature
const int longDelayTime = 400;   // when a button get into continuous setting temperature mode
const int shortDelayTime = 100;   // delay between 2 increments or decrements (continuous setting mode)

/*
   relay vars (no to set relay all time long)
*/
const unsigned long relayTimer = 100000;
unsigned long relayCounter;


/*
   thermistor lookup table
   see http://www.reprap.org/wiki/Temperature_Sensor_2_0#Upload_firmware_to_Arduino
*/
#define NUMTEMPS 20

// Thermistor lookup table for RepRap Temperature Sensor Boards (http://make.rrrf.org/ts)
// Made with createTemperatureLookup.py (http://svn.reprap.org/trunk/reprap/firmware/Arduino/utilities/createTemperatureLookup.py)
// ./createTemperatureLookup.py --r0=100000 --t0=25 --r1=0 --r2=4700 --beta=4066 --max-adc=1023
// r0: 100000
// t0: 25
// r1: 0
// r2: 4700
// beta: 4066
// max adc: 1023

short temptable[NUMTEMPS][2] = {
   {1, 841},
   {54, 255},
   {107, 209},
   {160, 184},
   {213, 166},
   {266, 153},
   {319, 142},
   {372, 132},
   {425, 124},
   {478, 116},
   {531, 108},
   {584, 101},
   {637, 93},
   {690, 86},
   {743, 78},
   {796, 70},
   {849, 61},
   {902, 50},
   {955, 34},
   {1008, 3}
};

void setup ()
{
   pinMode (relayCommandPin, OUTPUT);
   lcd.begin(16, 2);
   lcd.setCursor (0, 0);
   lcd.print ("Init...");
   //targetTemp = EEPROM.read (tempAddressIntoMemory);
   //oldTargetTemp = targetTemp;
}

void loop ()
{
   setTargetTemperature ();
   setTemperatureAndRelay ();
}

void setTargetTemperature ()
{
   increaseTempButton.update ();
   if (increaseTempButton.read () == LOW && targetTemp < maximumTemp)
   {
      targetTemp += 1;
      displayTemperaturesInformation ();
      delay (longDelayTime);      
      increaseTempButton.update ();
      while (increaseTempButton.read () == LOW && targetTemp < maximumTemp)
      {
         targetTemp += 1;
         displayTemperaturesInformation ();
         delay (shortDelayTime);
         increaseTempButton.update ();
      }
   }
   
   decreaseTempButton.update ();
   if (decreaseTempButton.read () == LOW && targetTemp > minimumTemp)
   {
      targetTemp -= 1;
      displayTemperaturesInformation ();
      delay (longDelayTime);      
      decreaseTempButton.update ();
      while (decreaseTempButton.read () == LOW && targetTemp > minimumTemp)
      {
         targetTemp -= 1;
         displayTemperaturesInformation ();
         delay (shortDelayTime);
         decreaseTempButton.update ();
      }
   }
}

void setTemperatureAndRelay ()
{
   relayCounter ++;

   if (relayCounter == relayTimer)
   {
      relayCounter = 0;

      currentTemperature = getThermistanceTemperature (thermistorPin);

      if (currentTemperature >= targetTemp)
      {
         digitalWrite (relayCommandPin, LOW);
      }
      else
      {
         digitalWrite (relayCommandPin, HIGH);
      }

      if (currentTemperature != previousTemperature)
      {
         previousTemperature = currentTemperature;
      }

      displayTemperaturesInformation ();

      //    if (oldTargetTemp != targetTemp)
      //    {
      //       EEPROM.write (tempAddressIntoMemory, targetTemp);
      //       oldTargetTemp = targetTemp;
      //    }

   }
}

void displayTemperaturesInformation ()
{
   firstLCDLine = "Bed ";
   firstLCDLine.append (int(currentTemperature));
   firstLCDLine.append (" > ");
   firstLCDLine.append (targetTemp);
   if (digitalRead (relayCommandPin) == HIGH)
   {
      firstLCDLine.append (" *  ");
   }
   else
   {
      firstLCDLine.append ("    ");
   }
   lcd.setCursor (0, 0);
   lcd.print (firstLCDLine);

   secondLCDLine = "Amb ";
   secondLCDLine.append (int(getTMP36Temperature (TMP36Pin)));   
   lcd.setCursor (0, 1);
   lcd.print (secondLCDLine);
}

float getTMP36Temperature (int pin)
{
   float temp = analogRead (pin) * .004882814;
   temp = (temp - .5) * 100;
   return temp;
}

int getThermistanceTemperature (int pin)
{
   // see http://www.reprap.org/wiki/Temperature_Sensor_2_0#Upload_firmware_to_Arduino
   int rawtemp = analogRead (pin);
   int current_celsius = 0;

   byte i;
   for (i=1; i<NUMTEMPS; i++)
   {
      if (temptable[i][0] > rawtemp)
      {
         int realtemp  = temptable[i-1][1] + (rawtemp - temptable[i-1][0]) * (temptable[i][1] - temptable[i-1][1]) / (temptable[i][0] - temptable[i-1][0]);
         if (realtemp > 255)
         {
            realtemp = 255; 
         }
         current_celsius = realtemp;
         break;
      }
   }

   // Overflow: We just clamp to 0 degrees celsius
   if (i == NUMTEMPS)
   {
      current_celsius = 0;
   }

   return current_celsius;
}

