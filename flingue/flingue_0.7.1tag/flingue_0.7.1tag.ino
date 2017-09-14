#include <IRremote.h>
#include <SPI.h>      // Pour la communication via le port SPI
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include "RF24.h"

bool cosplayMode = 0 ;

//Neopixel
#include <Adafruit_NeoPixel.h>
//#define PIN 6 //pin number that you have connected your data pin to
#define PixCanon 3 //number of neopixels you have connected
Adafruit_NeoPixel stripCanon = Adafruit_NeoPixel(PixCanon, 6, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options

//Vibreur 
int motorPin = 3 ;


//infrarouge
int RECV_PIN = 5;
IRrecv irrecv(RECV_PIN);
decode_results results;

//Radio nrf24L01
RF24 radio(9,10);  // make sure this corresponds to the pins you are using : SCL SO
byte addresses[][8] = {"hub","flingue"};
int chan = 1 ;

//traitement message entré IR

//entité ciblée (tag)
unsigned long targetTimeOut ;
int cible = 0 ;                     //cible actuelle
int oldCible ;                  //cible avant

//unsigned long gateCible ;         //pour la cible en elle-même

//données
String inMessage ;
char IDObject[8] = ":pistol";
char IDHub[8]    = "!11";  //111111
bool process ;
int redNP ;
int greNP ;
int bluNP ;


//gâchette
bool mireCible ;
bool panFlag = HIGH ;
bool reloadFlag = HIGH ;
unsigned long debounceGachette ;
unsigned long debounceReload ;

int messRCVhF ;


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


#include "feedback.h"
#include "feedbackVib.h"

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

  stripCanon.begin();
  stripCanon.setBrightness(255);
  stripCanon.show();

  irrecv.enableIRIn(); // Start the receiver
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  
  Serial.println("Flingue 0.6.1vib");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Loop/////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
  if (Serial.available()) inMessage = Serial.readStringUntil('}');

//if (inMessage == "debug") {Serial.println("debug");}

oldCible = cible ;
//////////////////////////////////////////Traitement du message infrarouge///////////////////////////////////////

//irrecv.resume();
//détection Ir : faisage de message
  if (irrecv.decode(&results) ) {
     if( results.value <= 127 && results.value >= 0){
    cible = results.value ;
    targetTimeOut = millis() + 45 ;
    }
    irrecv.resume();
  }

  if (targetTimeOut < millis() ) {
    cible = 0 ;
  }
  
////////////////////////////////////////////////////////////////////////
////////////////////////////////////ENVOIS//////////////////////////////
////////////////////////////////////////////////////////////////////////


////////////////////////////////////Envoi action c : cible (vise)
if (cible != oldCible) {   //problème avec cible != oldCible  // && cible != "vide"
    Serial.println(cible);
    
    strcpy( sendBox.par, "target");
    sendBox.val = cible;
    
    radio.stopListening();
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
}


////////////////////////////////////Envoi action a : tir
if (digitalRead(A1) == LOW && panFlag == HIGH && millis() > debounceGachette) { 
  Serial.println("Pan !");

  radio.stopListening();
  strcpy( sendBox.par, "trigger"); sendBox.val = 1; radio.write( &sendBox, sizeof(sendBox) );
  radio.startListening();

  panFlag = LOW ;
  debounceGachette = millis() + 20;
  }
//on libère la gachette pour le prochain loop
if (digitalRead(A1) == HIGH && millis() > debounceGachette)
  {
      if (!panFlag){
      radio.stopListening();
      strcpy( sendBox.par, "trigger"); sendBox.val = 0; radio.write( &sendBox, sizeof(sendBox) );
      radio.startListening();
      }
  panFlag = HIGH ;
  debounceGachette = millis() + 50;
  }

////////////////////////////////////Envoi action b : rechargement
if (digitalRead(A2) == LOW && millis() > debounceReload) { 

  if(panFlag == HIGH){
    Serial.println("Rechargement");

    radio.stopListening();
    strcpy( sendBox.par, "reload"); sendBox.val = 1; radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
    }
  debounceReload = millis() + 500 ;
  }

if (millis() > debounceReload) {
  reloadFlag = HIGH ;
}

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
      //Serial.println(receiveBox.to); Serial.println(receiveBox.par);
    if (recparString == "shootFB") {shootFb(0); tokenShoot=1; shootVibToken=1; }
    if (recparString == "rldFB") {tokenReload=1;}
    if (recparString == "sightFB") {
        stripCanon.setPixelColor(1, 0, 0, 100 * receiveBox.val); 
        stripCanon.show();
      }
    if (recparString.startsWith("NP")){
      int NPled = recparString.charAt(6) - 48;
        if (recparString.startsWith("NPRed")) {redNP = receiveBox.val; stripCanon.setPixelColor(NPled, 0, 0, 0);}
        if (recparString.startsWith("NPGre")) {greNP = receiveBox.val;}
        if (recparString.startsWith("NPBlu")) {bluNP = receiveBox.val;
        
        stripCanon.setPixelColor(NPled, redNP, greNP, bluNP); 
        stripCanon.show();
        //Serial.print(redNP); Serial.print(" "); Serial.print(greNP); Serial.print(" "); Serial.println(bluNP); 
        }
    }

  process = 0;
  }
  
//Serial.println(reception.trigger);
if (tokenShoot) {shootFb();}
if (shootVibToken) {shootVibFb();}



}












