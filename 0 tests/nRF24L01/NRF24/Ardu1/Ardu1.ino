// http://www.bajdi.com
// Sending a struct with the nRF24L01 module
// Data to be sent is the reading of 2 analog pins
// Data received is the analog reading of 2 pins on the other Arduino 
// code hub

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9,10);  // make sure this corresponds to the pins you are using : SCL SO
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

const int led = 0;

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
  pinMode(led, OUTPUT);
  radio.begin();
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
}

void loop(void)
{
  // we need data to send...
//  duino2.W = analogRead(A0);
//  duino2.X = analogRead(A1);
//  duino2.Y = analogRead(A0)/102.3;
//  duino2.Z = analogRead(A1)/102.3;
  // end of analog reading

  duino2.to = 12;
  duino2.from ++;
  duino2.value = random(0, 255);
  duino2.rssi = analogRead(A1)/102.3;

  // radio stuff
  radio.stopListening();
  bool ok = radio.write( &duino2, sizeof(duino2) );
  radio.startListening();

  unsigned long started_waiting_at = millis();
  bool timeout = false;
  while ( ! radio.available() && ! timeout )
    if (millis() - started_waiting_at > 250 )
      timeout = true;

  if ( timeout )
  {
    Serial.println("Failed, response timed out.");
    digitalWrite(led, HIGH);
  }
  else
  {
    radio.read( &duino1, sizeof(duino1) );
    
    digitalWrite(led, LOW);
  }
  // end of radio stuff

  // serial print received data
  /*
  Serial.print("duino1.W = ");
  Serial.print(duino1.to);
  Serial.print(" duino1.X = ");
  Serial.print(duino1.from);
  Serial.print(" duino1.Y = ");
  Serial.print(duino1.value);
  Serial.print(" duino1.Z = ");
  Serial.print(duino1.rssi);
  Serial.print(" duino1.Y = ");
  Serial.print(duino1.A);
  Serial.print(" duino1.Z = ");
  Serial.print(duino1.B);
  Serial.print(" duino1.I = ");
  Serial.print(duino1.C);
  Serial.print(" duino1.J = ");
  Serial.println(duino1.D);
  */
  // end of serial printing
}

