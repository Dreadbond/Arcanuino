#include <ArduinoJson.h>

#define spr Serial.println();
#define sps ; Serial.print(" ");


//Tag infrarouge
#include <IRremote.h>
IRsend irsend;
unsigned long tagGate = 0 ;
unsigned long tagNxtChrTime = 0 ;
int indexIRTag = 0 ;

//Neopixel
#include <Adafruit_NeoPixel.h>
#define PIN 5 //pin number that you have connected your data pin to
#define Pix 16 //number of neopixels you have connected
float redNP ;
float greNP ;
float bluNP ;
float bright=0.4;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(Pix, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options

//données
const int led = 0;
//char IDObject[8] = "!222222"; 
char IDObject[8] = "!111111";
//char IDObject[8] = "!184675";  //Dessloch
//char IDObject[8] = "!123456";  //Alarik
//char IDObject[8] = "!986543";  //Rhea
int chan = 1 ;
bool justReceive ;
bool canSend = 1;
unsigned long nextSend ;
String valueStr ;
  String inMessage ;

//Communications RF
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
RF24 radio(9,10);  // make sure this corresponds to the pins you are using : SCL SO
const uint64_t pipes[5] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL, 0xF0F0F0F066, 0xF0F0F0F012, 0xF0F0F0F042 };


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
  Serial.begin(9600); //9600
  pinMode(led, OUTPUT);

  //Communications RF
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);

  radio.setChannel(chan);
  radio.openWritingPipe(pipes[4]);
  radio.openReadingPipe(1,pipes[1]);
  radio.startListening();
  //End communications RF

  strip.begin();
  strip.setBrightness(255);
  strip.show();//sets all pixels to off state
  
  //Serial.print("Hub NRF24. 0.77 Ajout Json"); Serial.println(IDObject);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  thisHub.lifeDisplay=1;
}

void loop(){
if ( radio.available() ){
    //contenuUncertain();
      radio.read( &uncertainBox, sizeof(uncertainBox) );
      if (String(uncertainBox.to).equals(IDObject)) {
        receiveBox = uncertainBox ;
        //contenuReceive();
        justReceive = 1 ;
        }
  }

String RecToString = String(receiveBox.to) ;
String RecFromString = String(receiveBox.from) ;    //pour aussi remettre à 0 la receiveBox
String RecParamString=String(receiveBox.param);



flingueCode(RecFromString, RecParamString, receiveBox.value);
wizblaCode(RecFromString, RecParamString, receiveBox.value);
//swordCode(RecFromString, RecParamString, receiveBox.value);
gantCode(RecFromString, RecParamString, receiveBox.value);

hubReceive(RecToString, RecParamString, receiveBox.value);    //à la fin.

//{"to":":pistol","from":"!111111","param" :":shootFb","value":1}
//{"to":":hub","from":"!111111","param":"beenShot","value":1}
//Smartphone entries

  if (Serial.available()) {
  inMessage = Serial.readStringUntil('}');
  //Serial.println(pistol.inMessage);
  }

pistolReceive();
wizblaReceive();
gantReceive();
pistolCode();   //à laisser dans flingueCode
hubLoop(); //ça sera calculé par le téléphone
hubReceiveSP() ;


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