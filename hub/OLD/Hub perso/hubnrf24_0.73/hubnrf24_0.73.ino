// http://www.bajdi.com
// Sending a struct with the nRF24L01 module
// Data to be sent is the reading of 2 analog pins
// Data received is the analog reading of 2 pins on the other Arduino 
// code hub


#define sps Serial.print(" ");
#define spr Serial.println();

//Tag infrarouge
#include <IRremote.h>
IRsend irsend;
unsigned long tagGate = 0 ;
unsigned long tagNxtChrTime = 0 ;
int indexIRTag = 0 ;



//données
const int led = 0;
char IDObject[8] = "!111111";
//char IDObject[8] = "!184675";  //Dessloch
//char IDObject[8] = "!123456";  //Alarik
//char IDObject[8] = "!986543";  //Rhea
bool process ;
bool justReceive ;
bool canSend = 1;
unsigned long nextSend ;

//Communications RF
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
RF24 radio(9,10);  // make sure this corresponds to the pins you are using : SCL SO
const uint64_t pipes[4] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL, 0xF0F0F0F066, 0xF0F0F0F012 };


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

void contenuUncertain(){
  Serial.print(" FROM = ");
  Serial.print(uncertainBox.from);
  Serial.print(" TO = ");
  Serial.print(uncertainBox.to);
  Serial.print(" param = ");
  Serial.print(uncertainBox.param);
  Serial.print(" value = ");
  Serial.println(uncertainBox.value);
}

#include "hub.h"
#include "gant0.9.h"
#include "flingue0.4.h"
#include "wizarBlaster_0.3.h"
#include "piquemord.h"



void setup()
{
  strcpy( sendBox.from, IDObject );
  Serial.begin(57600);
  pinMode(led, OUTPUT);

  //Communications RF
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  //radio.openWritingPipe(pipes[0]);
  //radio.openReadingPipe(1,pipes[1]);
  radio.setChannel(1);
  radio.openWritingPipe(pipes[4]);
  radio.openReadingPipe(1,pipes[1]);
  radio.startListening();
  //End communications RF
  
  Serial.print("Hub NRF24. 0.73 Tag : "); Serial.println(IDObject);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

}




void loop(){
  
  if ( radio.available() )
  {
      radio.read( &uncertainBox, sizeof(uncertainBox) );
      if (String(uncertainBox.to).equals(IDObject)) {
        receiveBox = uncertainBox ;
        //contenuUncertain();
        //contenuReceive();
        justReceive = 1 ;
        }
  }

String RecToString = String(receiveBox.to) ;
String RecFromString = String(receiveBox.from) ;    //pour aussi remettre à 0 la receiveBox
String RecParamString=String(receiveBox.param);


hubReceive(RecToString, RecParamString, receiveBox.value);

flingueCode(RecFromString, RecParamString, receiveBox.value);
wizblaCode(RecFromString, RecParamString, receiveBox.value);
swordCode(RecFromString, RecParamString, receiveBox.value);

  
if (process) {
  radio.stopListening();
  //radio.openWritingPipe(pipes[3]);
  radio.write( &sendBox, sizeof(sendBox) );
  radio.startListening();
  process=0;
  }
  




pistolCode();
hubLoop(); //ça sera calculé par le téléphone



  if (tagNxtChrTime < millis()){  
      irsend.sendRC5(thisHub.tag.charAt(indexIRTag), 12);
      tagNxtChrTime = millis() + 15 ;  //15 500
      indexIRTag++;
    }
  if(indexIRTag >= thisHub.tag.length()) {    indexIRTag=0; tagNxtChrTime = millis() + 100 ; } //100 2000

  //taux de rafraichissement de l'envoi de données
  if (nextSend < millis() ) {canSend=1; nextSend = millis() + 10; }


//Remise à zéro
justReceive = 0;
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
  if (tagGate < millis()) {
    //for (int i = 0; i < thisHub.tag.length(); i++){
    if (tagNxtChrTime < millis()){  
      irsend.sendRC5(thisHub.tag.charAt(indexIRTag), 12); 
      tagNxtChrTime = millis() + 150 ;  //15
      //delay(15);
    }
    if(indexIRTag=thisHub.tag.length()) { tagGate = millis() + 2000 + (15*thisHub.tag.length() ); }  //100
  }
*/









