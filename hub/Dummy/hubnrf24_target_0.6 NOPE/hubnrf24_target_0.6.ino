// http://www.bajdi.com
// Sending a struct with the nRF24L01 module
// Data to be sent is the reading of 2 analog pins
// Data received is the analog reading of 2 pins on the other Arduino 
// code hub

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//Neopixel
#include <Adafruit_NeoPixel.h>
#define PIN 5 //pin number that you have connected your data pin to
#define Pix 10 //number of neopixels you have connected

float redNP ;
float greNP ;
float bluNP ;
float bright=0.4;
bool refreshLifeNP ;
int NPled ;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(Pix, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options


//Tag infrarouge
#include <IRremote.h>
IRsend irsend;
unsigned long tagGate = 0 ;
unsigned long tagNxtChrTime = 0 ;
int indexIRTag = 0 ;


RF24 radio(9,10);  // make sure this corresponds to the pins you are using : SCL SO
const uint64_t pipes[3] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL, 0xF0F0F0F066 };

//données
const int led = 0;
//char IDObject[8] = "!111111";
char IDObject[8] = "!184675";  //Dessloch
//char IDObject[8] = "!123456";  //Alarik
//char IDObject[8] = "!986543";  //Rhea
bool process ;
bool justReceive ;
 




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
int rec[1] = {2};

void setup()
{
  strcpy( sendBox.from, IDObject );
  Serial.begin(57600);
  pinMode(led, OUTPUT);

  strip.begin();
  strip.setBrightness(255);
  strip.show();//sets all pixels to off state
  
  radio.begin();
  //radio.setAutoAck(true);
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(10);
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[0]);
  radio.startListening();
  
  Serial.print("Hub cible 0.6. Tag : "); Serial.println(IDObject);
  pinMode(7, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  //dummyInit();
}




void loop(){
  
  if ( radio.available() )
  {
      radio.read( &uncertainBox, sizeof(uncertainBox) );
      //contenuUncertain();
      if (String(uncertainBox.to).equals(IDObject)) {
        receiveBox = uncertainBox ;
        //contenuReceive();
        justReceive = 1 ;
      }
  }

String RecToString = String(receiveBox.to) ;
String RecFromString = String(receiveBox.from) ;    //pour aussi remettre à 0 la receiveBox
String RecParamString=String(receiveBox.param);


hubReceive(RecToString, RecParamString, receiveBox.value);


  
if (process) {
  radio.stopListening();
  radio.write( &sendBox, sizeof(sendBox) );
  radio.startListening();
  process=0;
  }
  





hubLoop(); //ça sera calculé par le téléphone




if (refreshLifeNP) {
    strip.setPixelColor(NPled, redNP, greNP, bluNP); 
    strip.show();
  refreshLifeNP = 0;
}


  if (tagNxtChrTime < millis()){  
      irsend.sendRC5(thisHub.tag.charAt(indexIRTag), 12);
      tagNxtChrTime = millis() + 15 ;  //15 500
      indexIRTag++;
    }
  if(indexIRTag >= thisHub.tag.length()) {    indexIRTag=0; tagNxtChrTime = millis() + 100 ; } //100 2000

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









