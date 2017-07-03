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

//char IDObject[8] = ":satOne";
//char IDObject[8] = ":satTwo";
//char IDObject[8] = ":pistol";
bool process ;
bool bouton ;
bool oldBouton ;


typedef struct{
  char from[8];
  char to[8];
  char param[8];
  float value;
}
packet;

packet sendBox ;
packet receiveBox ;

void contenuSend(){
  Serial.print("J'envoie : FROM = ");
  Serial.print(sendBox.from);
  Serial.print(" TO = ");
  Serial.print(sendBox.to);
  Serial.print(" param = ");
  Serial.print(sendBox.param);
  Serial.print(" value = ");
  Serial.println(sendBox.value);
}

void contenuReceive(){
  Serial.print("Je recois : FROM = ");
  Serial.print(receiveBox.from);
  Serial.print(" TO = ");
  Serial.print(receiveBox.to);
  Serial.print(" param = ");
  Serial.print(receiveBox.param);
  Serial.print(" value = ");
  Serial.println(receiveBox.value);
}


void setup()
{

  strcpy( sendBox.from, IDObject );
  strcpy( sendBox.to, ":111111" );

  Serial.begin(57600);
  radio.begin();
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);
  radio.startListening();
  pinMode(7, INPUT_PULLUP);
  //pinMode(A1, INPUT_PULLUP);

  Serial.println(String(IDObject[8]));
}

void loop(void)
{ 
oldBouton = bouton ;
bouton = digitalRead(7);

  if ( radio.available() )
  {
    bool done = false;
    while (!done) {done = radio.read( &receiveBox, sizeof(receiveBox) );}
    process=1;
  }

  if (oldBouton != bouton){
    strcpy( sendBox.param, "bouton" );
    sendBox.value=!bouton;
    contenuSend();
    
    radio.stopListening();
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
  }

if (String(receiveBox.to).equals(IDObject) && process) {
  contenuReceive();
  process=0;
  }


}

