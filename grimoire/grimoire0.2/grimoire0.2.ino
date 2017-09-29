#include <SPI.h>      // Pour la communication via le port SPI
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include "RF24.h"

bool cosplayMode = 0 ;

//Neopixel
#include <Adafruit_NeoPixel.h>
#define PIN 5 //number of neopixels you have connected
#define PIX 16
Adafruit_NeoPixel page = Adafruit_NeoPixel(PIX, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options

//Vibreur 
int motorPin = 4 ;

//Radio nrf24L01
RF24 radio(9,10);  // make sure this corresponds to the pins you are using : SCL SO
byte addresses[][8] = {"hub","grimoire"};
int chan = 1 ;

//capteurs
int fireCap  = A1;
int healCap  = A7;
int shieldCap= A5;

bool fire, heal, shield ;
unsigned long debounceFire, debounceShield, debounceHeal ;

//données
String inMessage ;
char IDObject[8] = ":grimoire";
char IDHub[8]    = "!11";  //111111
bool process ;
int redNP ;
int greNP ;
int bluNP ;


typedef struct{
  char from[8];
  //char to[8];
  char par[8];
  float val;
}
packet;

packet sendBox ;
packet receiveBox ;
packet uncertainBox;

void contenuSend(){
  Serial.print("J'envoie : FROM = ");
  Serial.print(sendBox.from);
//  Serial.print(" TO = ");
//  Serial.print(sendBox.to);
  Serial.print(" par = ");
  Serial.print(sendBox.par);
  Serial.print(" val = ");
  Serial.println(sendBox.val);
}

void contenuReceive(){
  Serial.print("Je recois : FROM = ");
  Serial.print(receiveBox.from);
//  Serial.print(" TO = ");
//  Serial.print(receiveBox.to);
  Serial.print(" par = ");
  Serial.print(receiveBox.par);
  Serial.print(" val = ");
  Serial.println(receiveBox.val);
}

void contenuUncertain(){
  Serial.print(" FROM = ");
  Serial.print(uncertainBox.from);
//  Serial.print(" TO = ");
//  Serial.print(uncertainBox.to);
  Serial.print(" par = ");
  Serial.print(uncertainBox.par);
  Serial.print(" val = ");
  Serial.println(uncertainBox.val);
}

#include "feedbackEvent.h"
//#include "feedback.h"
//#include "feedbackVib.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Setup////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  strcpy( sendBox.from, IDObject );
  //strcpy( sendBox.to, IDHub );

  Serial.begin(9600);

  //Communications RF
  radio.begin();
  //radio.setAutoAck(true);
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(chan);

  radio.openWritingPipe(addresses[0]);        // Both radios listen on the same pipes by default, but opposite addresses
  radio.openReadingPipe(1,addresses[1]);  

  radio.startListening();
  //Communications RF

  page.begin();
  page.setBrightness(255);
  page.show();

  pinMode(shield, INPUT);
  pinMode(heal, INPUT);
  pinMode(fire, INPUT);

  pinMode(5, OUTPUT);
  
  Serial.println("Grimoire0.1.1");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Loop/////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
  if (Serial.available()) {
    inMessage = Serial.readStringUntil('}');
    Serial.println(inMessage);
  }


Serial.print(analogRead(fireCap));
Serial.print(" ");
Serial.print(analogRead(shieldCap));
Serial.print(" ");
Serial.print(analogRead(healCap));
Serial.print(" ");
Serial.println();


if (analogRead(fireCap) < 750 && !fire && debounceFire < millis()) {
  fire = 1 ;
  debounceFire = millis() + 100 ;

}
if (analogRead(fireCap) > 750 && fire && debounceFire < millis()) {
  fire = 0 ;
  debounceFire = millis() + 100 ;

}



if (analogRead(shieldCap) < 750 && !shield && debounceShield < millis()) {

  shield = 1 ;
  debounceShield = millis() + 100 ;
}
if (analogRead(shieldCap) > 750 && shield && debounceShield < millis()) {

  shield = 0 ;
  debounceShield = millis() + 100 ;
}




if (analogRead(healCap) < 750 && !heal && debounceHeal < millis()) {
  heal = 1 ;
  
  debounceHeal = millis() + 100 ;

}
if (analogRead(healCap) > 750 && heal && debounceHeal < millis()) {
  heal = 0 ;
  debounceHeal = millis() + 100 ;

}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////ENVOIS//////////////////////////////
////////////////////////////////////////////////////////////////////////
/*
if (analogRead(fireCap) < 750) {
tokenFireCast=1 ;
}
*/


//////////////////////////////////////Feedback
  if (radio.available() )
  {
      radio.read( &receiveBox, sizeof(receiveBox) );
      //if (String(uncertainBox.to).equals(IDObject) && String(uncertainBox.from).equals(IDHub) ) {
        //receiveBox = uncertainBox ;
        //contenuUncertain();
        //contenuReceive();
        process=1;
        //}
  }

String recFromString = String(receiveBox.from) ;    //pour aussi remettre à 0 la receiveBox
String recparString=String(receiveBox.par);


  if (process) {  //recToString == IDObject && 
      Serial.println("Reçu un truc radio");
  process = 0;
  }

//if (tokenFireCast) fireCast("more") ;
eventFeedback();

}












