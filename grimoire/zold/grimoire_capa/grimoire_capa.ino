#include <CapacitiveSensor.h>

/*
   CapitiveSense Library Demo Sketch
   Paul Badger qq2008
   Uses a high value resistor e.g. 10 megohm between send pin and receive pin
   Resistor effects sensitivity, experiment with values, 50 kilohm - 50 megohm. Larger resistor values yield larger sensor values.
   Receive pin is the sensor pin - try different amounts of foil/metal on this pin
   Best results are obtained if sensor foil and wire is covered with an insulator such as paper or plastic sheet
*/

int sensi = 20 ;
CapacitiveSensor   cs_9_2 = CapacitiveSensor(9, 2);       // 10 megohm resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil
CapacitiveSensor   cs_9_5 = CapacitiveSensor(9, 5);       // 10 megohm resistor between pins 4 & 6, pin 6 is sensor pin, add wire, foil
CapacitiveSensor   cs_9_11 = CapacitiveSensor(9, 11);       // 10 megohm resistor between pins 4 & 8, pin 8 is sensor pin, add wire, foil

void setup()
{
  pinMode(13, OUTPUT);
  //cs_9_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(9600);

}

void loop()
{
  long start = millis();
  long total1 =  cs_9_2.capacitiveSensor(30);
  long total2 =  cs_9_5.capacitiveSensor(30);
  long total3 =  cs_9_11.capacitiveSensor(30);

  //Serial.print(millis() - start);        // check on performance in milliseconds
  Serial.print("\t");                    // tab character for debug window spacing

  Serial.print(total1);                  // print sensor output 1
  Serial.print("\t");
  Serial.print(total2);                  // print sensor output 2
  Serial.print("\t");
  Serial.println(total3);                // print sensor output 3

  if (total1 > sensi || total2 > sensi || total3 > sensi) {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }


  delay(100);                             // arbitrary delay to limit data to serial port
}
