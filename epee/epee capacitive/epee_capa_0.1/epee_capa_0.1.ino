#include <CapacitiveSensor.h>

/*
   CapitiveSense Library Demo Sketch
   Paul Badger qq2008
   Uses a high value resistor e.g. 10 megohm between send pin and receive pin
   Resistor effects sensitivity, experiment with values, 50 kilohm - 50 megohm. Larger resistor values yield larger sensor values.
   Receive pin is the sensor pin - try different amounts of foil/metal on this pin
   Best results are obtained if sensor foil and wire is covered with an insulator such as paper or plastic sheet
*/
int led = 11 ;
int sensi = 20 ;
int maxLed = 100 ;
int intenLed ;
CapacitiveSensor   cs_7_2 = CapacitiveSensor(7, 2);       // 10 megohm resistor between pins 7 & 2, pin 2 is sensor pin, add wire, foil

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  //cs_7_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(9600);
}

void loop()
{
  long start = millis();
  long total1 =  cs_7_2.capacitiveSensor(30);

Serial.print(millis() - start); Serial.print(" ");        // check on performance in milliseconds
Serial.println(total1);

/*
if (maxLed < total1) {maxLed = total1;}
intenLed = map(total1, 0, maxLed, 0, 255) ;
intenLed = constrain(intenLed, 0, 255) ;
*/
//Serial.println(intenLed);   
//analogWrite(led, intenLed);


}
