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




void contenuPacket(){
  Serial.print("receiveBox.TO = ");
  Serial.print(receiveBox.to);
  Serial.print(" receiveBox.FROM = ");
  Serial.print(receiveBox.from);
  Serial.print(" receiveBox.param = ");
  Serial.print(receiveBox.param);
  Serial.print(" receiveBox.value = ");
  Serial.print(receiveBox.value);
  Serial.println();
}

void setup()
{
  sendBox.from[8]=":111111";
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
  
  //radio.stopListening(); //déjà dans if reception.trigger
  //bool ok = radio.write( &duino2, sizeof(duino2) );
  
  radio.startListening();

  unsigned long started_waiting_at = millis();
  bool timeout = false;
  while ( ! radio.available() && ! timeout )
    if (millis() - started_waiting_at > 250 )
      timeout = true;

  if ( timeout )
  {
    //Serial.println("Failed, response timed out.");
    //digitalWrite(led, HIGH);
  }
  else
  {
    radio.read( &reception, sizeof(reception) );
    contenuPacket();
    //digitalWrite(led, LOW);
  }


if (reception.trigger) {    //envoi gâchette ok
  //delay(1000);
  envoi.trigger=1;
  radio.stopListening();
  bool ok = radio.write( &envoi, sizeof(envoi) );
  radio.startListening();
  reception.trigger=0;
  envoi.trigger=0;
  Serial.println("Triggered");
}

}

