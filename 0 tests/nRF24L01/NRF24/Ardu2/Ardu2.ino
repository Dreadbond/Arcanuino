// http://www.bajdi.com
// Sending a struct with the nRF24L01 module
// Data to be sent is the reading of 2 analog pins
// Data received is the analog reading of 2 pins on the other Arduino 
// code objet

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9,10);   // make sure this corresponds to the pins you are using
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

typedef struct{
  int to;
  int from;
  float value;
  float rssi;
  char A = 'e';
  char B[3] = "Ki";
  int C = 3566;
  int D = 7500;
}
ardu1;

typedef struct{
  int to;
  int from;
  float value;
  float rssi;
  char A = 'L';
  char B[4] = "Lal";
  int C = 3566;
  int D = 7500;
}
ardu2;

ardu1 duino1;  
ardu2 duino2;


void setup()
{
  Serial.begin(57600);
  radio.begin();
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);
  radio.startListening();
}

void loop(void)
{ 
  // we need data to send...
  duino1.to = analogRead(A0);
  duino1.from = analogRead(A1);
  duino1.value = analogRead(A0)/102.3;
  duino1.rssi = analogRead(A1)/102.3;
  // end of analog reading

  // radio stuff
  if ( radio.available() )
  {
    bool done = false;
    while (!done)
    {
      done = radio.read( &duino2, sizeof(duino2) );
    }
    radio.stopListening();
    radio.write( &duino1, sizeof(duino1) );
    radio.startListening();
  }
  // end of radio stuff

  // serial print received data 
  Serial.print("duino2.W = ");
  Serial.print(duino2.to);
  Serial.print(" duino2.X = ");
  Serial.print(duino2.from);
  Serial.print(" duino2.Y = ");
  Serial.print(duino2.value);
  Serial.print(" duino2.Z = ");
  Serial.print(duino2.rssi);
  Serial.print(" duino2.Y = ");
  Serial.print(duino2.A);
  Serial.print(" duino2.Z = ");
  Serial.print(duino2.B);
  Serial.print(" duino2.I = ");
  Serial.print(duino2.C);
  Serial.print(" duino2.J = ");
  Serial.println(duino2.D);
  // end of serial printing
}

