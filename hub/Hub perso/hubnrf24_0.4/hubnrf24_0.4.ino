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

//données
const int led = 0;
char IDObject[8] = ":111111";
bool process ;
bool justReceive ;
 

//String RecFromString ;
//String RecParamString;

unsigned long D6rfrsh ;
unsigned long D7rfrsh ;

typedef struct{
  char from[8];
  char to[8];
  char param[8];
  float value;
}
packet;

packet sendBox ;
packet receiveBox ;
packet uncertainBox ;
/*
void Send(){
    radio.stopListening();
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
}*/

void contenuSend(){
  Serial.print(" FROM = ");
  Serial.print(sendBox.from);
  Serial.print(" TO = ");
  Serial.print(sendBox.to);
  Serial.print(" param = ");
  Serial.print(sendBox.param);
  Serial.print(" value = ");
  Serial.println(sendBox.value);
}

void contenuReceive(){
  Serial.print(" FROM = ");
  Serial.print(receiveBox.from);
  Serial.print(" TO = ");
  Serial.print(receiveBox.to);
  Serial.print(" param = ");
  Serial.print(receiveBox.param);
  Serial.print(" value = ");
  Serial.println(receiveBox.value);
}

#include "dummy.h"
#include "gant0.9.h"
#include "flingue0.4.h"
#include "wizarBlaster_0.3.h"


void setup()
{
  strcpy( sendBox.from, IDObject );
  Serial.begin(57600);
  pinMode(led, OUTPUT);
  
  radio.begin();
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  radio.startListening();
  
  Serial.println("Hub NRF24");
  pinMode(7, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);

  dummyInit();
}




void loop(){
  
  if ( radio.available() )
  {
    justReceive = 1 ;
    bool done = false;
    //while (!done) {
      done = radio.read( &uncertainBox, sizeof(uncertainBox) );
      //}
      if (String(uncertainBox.to).equals(IDObject)) {receiveBox = uncertainBox ;}
      contenuReceive();
  }



  //if (String(receiveBox.to).equals(IDObject) && process) {
    
    
String RecFromString = String(receiveBox.from) ;    //pour aussi remettre à 0 la receiveBox
String RecParamString=String(receiveBox.param);

//if (RecFromString == ":wizbla") {wizarBlasterCode(RecParamString, receiveBox.value);}
//if (RecFromString == ":pistol") {flingueCode(RecParamString, receiveBox.value);}
//if (RecFromString == ":gant")   {gantCode(RecParamString, receiveBox.value);}
flingueCode(RecFromString, RecParamString, receiveBox.value);
wizblaCode(RecFromString, RecParamString, receiveBox.value);

  //}

  
if (process) {
  radio.stopListening();
  radio.write( &sendBox, sizeof(sendBox) );
  radio.startListening();
  process=0;
  }
  
justReceive = 0;





dummyLoop();




}
/*
void Send(String to, String param, float value) {
 //   strcpy( sendBox.to, to );
 //   strcpy( sendBox.param, param );
    sendBox.value=1;
    
    radio.stopListening();
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
}
*/
/*
  if (!digitalRead(6)&& D6rfrsh<millis()){
    strcpy( sendBox.to, ":satOne" );
    strcpy( sendBox.param, "fireFB" );
    sendBox.value=1;
    
    radio.stopListening();
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
    Serial.println("Ca envoie");
    //contenuSend();
    D6rfrsh=millis() + 200;
  }

  if (!digitalRead(7)&& D7rfrsh<millis()){
    strcpy( sendBox.to, ":wizbla" );
    strcpy( sendBox.param, "iceFB" );
    sendBox.value=1;
    
    radio.stopListening();
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
    Serial.println("Ca envoie");
    //contenuSend();
    D7rfrsh=millis() + 15;
  }
  */
  

















