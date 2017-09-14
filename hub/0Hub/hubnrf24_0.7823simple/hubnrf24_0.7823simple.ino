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
//#define Pix 16
float redNP ;
float greNP ;
float bluNP ;
float bright=0.4;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(Pix, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options
Adafruit_NeoPixel stripFB = Adafruit_NeoPixel(Pix, 6, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options


//données
const int led = 0;
//char IDObject[8] = "!222222"; 
char IDObject[8] = "!11";
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
byte addresses[][8] = {"hub","flingue","wb","gant","grimoire"};
int hub = 0 ;
int flingue = 1 ;
int wizblaAddress = 2 ;
int gantAddress = 3 ;
int grimoireAddress = 4 ;
int epeeAddress = 5 ;


typedef struct{
  char from[8];
  char param[8];
  float value;
    
}
packet;

packet sendBox ;
packet receiveBox ;
packet uncertainBox ;

void contenuSend(){
  Serial.print(" FROM= ");
  Serial.print(sendBox.from);
  Serial.print(" param= ");
  Serial.print(sendBox.param);
  Serial.print(" value= ");
  Serial.println(sendBox.value);
}

void contenuReceive(){
  Serial.print(" FROM= ");
  Serial.print(receiveBox.from);
  Serial.print(" param= ");
  Serial.print(receiveBox.param);
  Serial.print(" value= ");
  Serial.println(receiveBox.value);
}

void contenuUncertain(){
  Serial.print(" FROM= ");
  Serial.print(uncertainBox.from);
  Serial.print(" param= ");
  Serial.print(uncertainBox.param);
  Serial.print(" value= ");
  Serial.println(uncertainBox.value);
}

#include "hub.h"
#include "flingue0.4.h"
#include "wizarBlaster_0.3.h"

/*
#include "gant0.9.h"
#include "piquemord.h"
*/


void setup()
{
  strcpy( sendBox.from, IDObject );
  Serial.begin(9600); //9600
  pinMode(led, OUTPUT);

  //Communications RF
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);

  radio.setChannel(chan);

  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[hub]);
  
  radio.startListening();
  //End communications RF

  strip.begin();
  strip.setBrightness(255);
  strip.show();//sets all pixels to off state

  stripFB.begin();
  stripFB.setBrightness(255);
  stripFB.show();//sets all pixels to off state
  
  thisHub.healthDisplay = 1;
  
  //Serial.print("Hub NRF24. 0.77 Ajout Json"); Serial.println(IDObject);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);


}

void loop(){
if ( radio.available() ){
      radio.read( &receiveBox, sizeof(receiveBox) );
      //contenuUncertain();
      
     // if (String(uncertainBox.to).equals(IDObject)) {
        //receiveBox = uncertainBox ;
        //contenuReceive();
        justReceive = 1 ;
        //}
  }

String RecFromString = String(receiveBox.from) ;    //pour aussi remettre à 0 la receiveBox
String RecparamString  = String(receiveBox.param);

  if (Serial.available()) inMessage = Serial.readStringUntil('}');


pistolReceive(RecFromString, RecparamString, receiveBox.value);
wizblaReceive(RecFromString, RecparamString, receiveBox.value);

/*
//swordCode(RecFromString, RecparamString, receiveBox.value);
//gantCode(RecFromString, RecparamString, receiveBox.value);

hubReceive(RecToString, RecparamString, receiveBox.value);    //sert pour combat avec routeurs

//{"to":":pistol","from":"!111111","param" :":shootFb","value":1}
//{"to":":hub","from":"!111111","param":"beenShot","value":1}
//Smartphone entries
*/

pistolSend();
wizblaSend();


hubCode();
pistolCode();
hubFeedback() ;
wizblaCode() ;




  if (tagNxtChrTime < millis()){  
      irsend.sendRC5(thisHub.tag.charAt(indexIRTag), 12);
      tagNxtChrTime = millis() + 15 ;  //15 500
      indexIRTag++;
    }
  if(indexIRTag >= thisHub.tag.length()) {    
    indexIRTag=0; 
    tagNxtChrTime = millis() + 20 ; //100 2000
    } 

  //taux de rafraichissement de l'envoi de données
  if (nextSend < millis() ) {canSend=1; nextSend = millis() + 10; }


justReceive = 0;
}
