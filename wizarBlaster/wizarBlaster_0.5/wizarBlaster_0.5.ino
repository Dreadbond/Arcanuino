#include <IRremote.h>
#include <SPI.h>      // Pour la communication via le port SPI
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include "RF24.h"

//Neopixel
#include <Adafruit_NeoPixel.h>
//#define PIN 6 //pin number that you have connected your data pin to
#define PixCanon 10 //number of neopixels you have connected
#define PixAmmo 5
int redNP ;
int greNP ;
int bluNP ;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PixCanon, 6, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options
Adafruit_NeoPixel stripAmmo = Adafruit_NeoPixel(PixAmmo, 5, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options
uint32_t orange1 = strip.Color(226, 121, 35);

//Radio nrf24L01
RF24 radio(9,10);  // make sure this corresponds to the pins you are using : SCL SO
const uint64_t pipes[4] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL, 0xF0F0F0F066, 0xF0F0F0F012 };

//données
#define sps Serial.print(" ")
char charCible[8];

char IDObject[8] = ":wizbla";
bool process ;
bool triggerBut ;
bool modeBut ;
bool reloadBut ;
bool cosplayMode = 0;


//traitement message entré IR
bool write_message = LOW ;      //si détecté un ":", il concatène la suite
char messActual[10] = " ";
String strMessActual ;          // pour conversion 
int tempsBuffer ;
int posCharRcv ;
int lgMess = 7 ;                //taille du message (trouver un standard)

//entité ciblée (tag)
String cible ;                     //cible actuelle
String oldCible ;                  //cible avant

//bool cibleConfirmee = LOW ;
unsigned long faireMessageCible ;   //uniquement pour réception char
//unsigned long gateCible ;         //pour la cible en elle-même
unsigned long resetCible ;          //décision de perdre la cible

int debug = 0 ;

//infrarouge
int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

int modeFeu = 1 ;

//gâchette
bool mireCible ;
bool panFlag = HIGH ;
bool modeFlag = HIGH ;
bool reloadFlag = HIGH ;
unsigned long debounceGachette ;

int messRCVhF ;
int munitions = 100 ;



void raz() {
    posCharRcv = 0 ;  //retour chariot
    cible = "!vide" ;
    strMessActual = "arf" ;      //strMessActual.remove(0);
    for (int i=0 ; i<lgMess; i++) {messActual[i] = '\0' ;}
    write_message = LOW;
}

///////////////////////////////////////////////////////////////////Recharge
bool tokenReload ;
void reloadLedFB(){
  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static int red ;
  static int green ;
  static int blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 1000 ;
  static int TC2 = 2000 ;
  static int TC3 = 3000 ;
  static int TC4 = 4000 ;

  //panFlag=LOW;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;

  if (chrono==TC0) {for(int i=0 ; i<PixAmmo ; i++) {stripAmmo.setPixelColor(i, 0, 0, 0);  stripAmmo.show();}}
  
  if (chrono>TC0 && chrono<TC1) {
    //for(int i=0; i<PixAmmo ; i++) {
      red  = random(150, 255);
      blue= random(150, 255);

      bright = float(chrono)/TC1;
      stripAmmo.setPixelColor(1, red*bright, green*bright, blue*bright); 
      stripAmmo.show();
    //}
  }
  
  if (chrono>TC1 && chrono<TC2) {
    //for(int i=0; i<PixAmmo ; i++) {
      red  = random(150, 255);
      blue= random(150, 255);

      bright = float(chrono-TC1)/TC2;
      stripAmmo.setPixelColor(2, red*bright, green*bright, blue*bright); 
      stripAmmo.show();
    //}
  }

  if (chrono>TC2 && chrono<TC3) {
    //for(int i=0; i<PixAmmo ; i++) {
      red  = random(150, 255);
      blue= random(150, 255);

      bright = float(chrono-TC2)/TC3;
      stripAmmo.setPixelColor(3, red*bright, green*bright, blue*bright); 
      stripAmmo.show();
    //}
  }

  if (chrono>TC3 && chrono<TC4) {
    //for(int i=0; i<PixAmmo ; i++) {
      red  = random(150, 255);
      blue= random(150, 255);

      bright = float(chrono-TC3)/TC4;
      stripAmmo.setPixelColor(4, red*bright, green*bright, blue*bright); 
      stripAmmo.show();
      
    //}
  }

  
  if (chrono>TC4 ) {
    //for(int i=0 ; i<PixAmmo ; i++) {stripAmmo.setPixelColor(i, 0, 0, 0);  stripAmmo.show();}
  tokenReload=LOW;
  effetStopFlag=HIGH;
  reloadFlag = HIGH ;
  }
}

///////////////////////////////////////////////////////////////////Recharge Bis
bool tokenReloadBis ;
void reloadBisLedFB(){
  static int red ;
  static int green ;
  static int blue ;
  static float bright ;
  static float indiceAmmo ;

  panFlag=LOW;


  indiceAmmo = munitions/100;
  

    if (indiceAmmo<25) {
        red  = random(150, 255);
        blue= random(150, 255);
  
        bright = indiceAmmo;
        stripAmmo.setPixelColor(1, red*bright, green*bright, blue*bright); 
        stripAmmo.show();
    }

    if (indiceAmmo<50&&indiceAmmo>=25) {
        red  = random(150, 255);
        blue= random(150, 255);
  
        bright = indiceAmmo;
        stripAmmo.setPixelColor(2, red*bright, green*bright, blue*bright); 
        stripAmmo.show();
    }

    if (indiceAmmo<50&&indiceAmmo>=75) {
        red  = random(150, 255);
        blue= random(150, 255);
  
        bright = indiceAmmo;
        stripAmmo.setPixelColor(3, red*bright, green*bright, blue*bright); 
        stripAmmo.show();
    }

    if (indiceAmmo<75&&indiceAmmo>=100) {
        red  = random(150, 255);
        blue= random(150, 255);
  
        bright = indiceAmmo;
        stripAmmo.setPixelColor(4, red*bright, green*bright, blue*bright); 
        stripAmmo.show();
        
    }
  }


///////////////////////////////////////////////////////////////////Tir chargé
bool tokenFire ;
void chargedFireFB(){
  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static int red ;
  static int green ;
  static int blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 2500 ;
  static int TC2 = 2550 ;
  static int TC3 = 2570 ;
  static int TC4 ;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;
  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);
  
  if (chrono>TC0 && chrono<TC1) {
    for(int i=0; i<3 ; i++) {
      red  = random(210, 255);
      green= red - 160 ;
      green= green + random(0,100);

      bright = float(chrono)/TC1;
      strip.setPixelColor(i, red*bright, green*bright, 0); 
      strip.show();
    }
  }
  if (chrono>TC1 && chrono<TC2){
    for(int i=0 ; i<PixCanon ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
      for(int i=3; i<PixCanon ; i++) {
      red  = 70 + (i*9) ;
      green= i*3 ;
      blue = 0;
  
      red=constrain(red, 0, 255);
      strip.setPixelColor(i, red, green, blue); 
      strip.show();
      }
  }
  if (chrono>TC2 && chrono<TC3){
    strip.setPixelColor(9, 200, 200, 200); 
    strip.show();
  }
  if (chrono>TC3 ) {
    for(int i=0 ; i<PixCanon ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
  tokenFire=LOW;
  effetStopFlag=HIGH;
  }
}

///////////////////////////////////////////////////////////////////Plasma
bool tokenPlasma ;
void plasmaLedFB(){
  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static int red ;
  static int green ;
  static int blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 40 ;
  static int TC2 = 50 ;
  static int TC3 = 70 ;
  static int TC4 = 80 ;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;

  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);
  
  if (chrono>TC0 && chrono<TC1) {
    for(int i=0; i<4 ; i++) {
      green= random(100, 180);
      red  = 0;
      blue = 10;
      
      bright = 0.25;
      strip.setPixelColor(i, red*bright, green*bright, blue*bright); 
      strip.show();
    }
  }
  if (chrono>TC1 && chrono<TC2){
      for(int i=4; i<7 ; i++) {
      green= random(150, 210);
      red  = 0;
      blue = random(50, 100);;
      
      bright = 0.5;
      strip.setPixelColor(i, red*bright, green*bright, blue*bright); 
      strip.show();
      }
  }
  if (chrono>TC1 && chrono<TC2){
      for(int i=7; i<PixCanon ; i++) {
      green= random(210, 255);
      red  = 100;
      blue = 100;
      
      bright = 1;
      strip.setPixelColor(i, red*bright, green*bright, blue*bright); 
      strip.show();
      }
  }
  if (chrono>TC2 && chrono<TC3){
    for(int i=0 ; i<PixCanon ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
    strip.setPixelColor(9, 200, 200, 200); 
    strip.show();
  }
  if (chrono>TC3 ) {
    for(int i=0 ; i<PixCanon ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
  tokenPlasma=LOW;
  effetStopFlag=HIGH;
  }
}

//////////////////////////////////////////////////////////////////////CHangement de mode
bool tokenMode ;
void modeFB(){
  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static int red ;
  static int green ;
  static int blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 1000 ;
  static int TC2 = 2000 ;
  

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;
  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);

  switch (modeFeu){
  case 1 :
      if (chrono>TC0 && chrono<TC1) {
        for(int i=0; i<PixCanon ; i++) {
          red = 155;
          green = 100;    
          
          bright = float(chrono)/TC1; 

          strip.setPixelColor(i, red*bright, green*bright, 0); 
          strip.show();
        }
      }
      if (chrono>TC1 && chrono<TC2) {
          for(int i=0; i<PixCanon ; i++) {
            red = 155;
            green = 100;    
            bright = -1*(float(chrono)-TC2)/TC1;

            strip.setPixelColor(i, red*bright, green*bright, 0); 
            strip.show();
          }
        }

      if (chrono>TC2 ) {
        for(int i=0 ; i<PixCanon ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
      tokenMode=LOW;
      effetStopFlag=HIGH;
      }
   break;

   case 2 :
      if (chrono>TC0 && chrono<TC1) {
        for(int i=0; i<PixCanon ; i++) {
          blue = 155;
          green = 100;    
          
          bright = float(chrono)/TC1; 

          strip.setPixelColor(i, red*bright, green*bright, 0); 
          strip.show();
        }
      }
      if (chrono>TC1 && chrono<TC2) {
          for(int i=0; i<PixCanon ; i++) {
            blue = 155;
            green = 100;    
            bright = -1*(float(chrono)-TC2)/TC1;

            strip.setPixelColor(i, red*bright, green*bright, 0); 
            strip.show();
          }
        }

      if (chrono>TC2 ) {
        for(int i=0 ; i<PixCanon ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
      tokenMode=LOW;
      effetStopFlag=HIGH;
      }
   break;

    }
}





typedef struct{
  char from[8];
  char to[8];
  char param[8];
  float value;
}
packet;

packet sendBox ;
packet receiveBox ;
packet uncertainBox;

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Setup////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  strcpy( sendBox.from, IDObject );
  strcpy( sendBox.to, "!111111" );
  
  strip.begin();
  stripAmmo.begin();
  strip.setBrightness(255);
  stripAmmo.setBrightness(70);
  strip.show();//sets all pixels to off state
  stripAmmo.show();
  
  Serial.begin(57600);
  radio.begin();
  //radio.openWritingPipe(pipes[0]);
  //radio.openReadingPipe(1,pipes[1]);
  radio.setChannel(1);
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[3]);
  radio.startListening();

  irrecv.enableIRIn(); // Start the receiver
  
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  
  Serial.println("WizarBlaster 0.5");
}

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


//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Loop/////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
  //tokenFire = HIGH;

if (Serial.available() > 0) {debug = Serial.read();}
//if (debug == 1) {Serial.println("debug");}

oldCible = cible ;
//////////////////////////////////////////Traitement du message infrarouge///////////////////////////////////////

//irrecv.resume();
//détection Ir : faisage de message
  if (irrecv.decode(&results)) {
     //Serial.println(char(results.value));
     irrecv.resume(); //à garder ici (???)
     if (char(results.value) == '!') {write_message = HIGH;}
        if (write_message) {
        messActual[posCharRcv] = char(results.value) ;  //concaténation
        strMessActual = String(messActual) ;            //conversion en String
        irrecv.resume();
        //Serial.print(messActual[posCharRcv]);
        posCharRcv++ ;
        resetCible = millis() + 150;                    //délai avant perte de cible 300 à la base. 200 ensuite
        faireMessageCible = millis() + 50 ;             //délai avant de confirmer message
        //Serial.print(posCharRcv); Serial.print(" ");
        //Serial.print(strMessActual); Serial.print(" ");
        //Serial.println(strMessActual.length());
        }
    }


//message trop long : erreur et vide
if (strMessActual.length() > lgMess) {   
  raz();
  write_message = LOW;
  //if (cosplayMode) {stripCanon.setPixelColor(0, 237, 127, 16); stripCanon.show(); }
  }


//message valide
if (faireMessageCible < millis() || strMessActual.length() == lgMess ) {
    if (strMessActual.length() == lgMess && strMessActual.charAt(0) == '!' ) {   //si bonne taille et commence par bon marqueur cible
    posCharRcv = 0 ;  //retour chariot
    //strMessActual[9]='\0';
    cible = String(messActual) ;
    


      for (int i=1 ; i<lgMess; i++) {
        if (isDigit(messActual[i])) {}
        else {cible = "!vide";} //
      }
    
    strMessActual.remove(0);
    for (int i=0 ; i<lgMess; i++) {messActual[i] = '\0' ;}
    write_message = LOW;
    //Serial.println("Ok");
    }
  
  }


//timeout ou message trop long: grosse galère, je compte sur le || strMessActual.length() == lgMess pour éviter ça
if (resetCible < millis() || strMessActual.length() > lgMess ) {   
  raz();
  //cible = "vide"; 
}

////////////////////////////////////Envoi action c : cible (vise)
if (cible != oldCible) {   //problème avec cible != oldCible  // && cible != "vide"
    Serial.println(cible);
    for (int i=0; i<7; i++) {  //pour l'envoi et la conversion en char
      charCible[i] = cible.charAt(i);//strMessActual[i] ;
      charCible[i+1] = '\0';
      }
      

    strcpy(sendBox.param, charCible);
    //sendBox.param = charCible ;
    sendBox.value = 1;
    
    radio.stopListening();
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
}


////////////////////////////////////////////////////////////////////////
//////////////////////////////////BOUTONS///////////////////////////////
////////////////////////////////////////////////////////////////////////


////////////////////////////////////Gâchette
if (digitalRead(2)== LOW && millis() > debounceGachette) {  //&& panFlag == HIGH 
      if (cosplayMode) {tokenFire=HIGH;}

      strcpy( sendBox.param, "trigger");
      sendBox.value = !digitalRead(2);
    
      radio.stopListening();
      radio.write( &sendBox, sizeof(sendBox) );
      radio.startListening();
 
  panFlag = LOW ;
  debounceGachette = millis() + 20;
  triggerBut = 1;
  //Serial.print("Gachette "); Serial.println(!digitalRead(2));
  }
//triggerBut = digitalRead(2);
//pour libérer la gachette, mais 'faut trouver un hardware mieux
if (millis() > debounceGachette)  //digitalRead(2) == HIGH && 
  {  
  panFlag = HIGH ;
  debounceGachette = millis() + 90;  
  
  }


////////////////////////////////////recharge
if (digitalRead(3) != reloadBut && !digitalRead(3)) {
      if (cosplayMode) {tokenReload=HIGH;}

      strcpy( sendBox.param, "reload");
      sendBox.value = 1;
    
      radio.stopListening();
      radio.write( &sendBox, sizeof(sendBox) );
      radio.startListening();

  //Serial.println("Reloading...");
  }
reloadBut = digitalRead(3);

  
////////////////////////////////////changement de mode
if (digitalRead(4) != modeBut && !digitalRead(4)) {
      if (cosplayMode) {tokenMode=HIGH;}

      strcpy( sendBox.param, "nxtMode");
      sendBox.value = 1;
    
      radio.stopListening();
      radio.write( &sendBox, sizeof(sendBox) );
      radio.startListening();
 
  //Serial.println("Changing mode...");
  }
modeBut = digitalRead(4);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////Réception HF//////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if (radio.available() )
  {
      radio.read( &uncertainBox, sizeof(uncertainBox) );
      if (String(uncertainBox.to).equals(IDObject)) {
        receiveBox = uncertainBox ;
        //contenuReceive();
        //contenuUncertain();
        process=1;
        }
  }

String recFromString = String(receiveBox.from) ;    //pour aussi remettre à 0 la receiveBox
String recToString=String(receiveBox.to);
String recParamString=String(receiveBox.param);

  if (String(receiveBox.to).equals(IDObject) && process) {
      //Serial.println(receiveBox.to); Serial.println(receiveBox.param);
    if (String(receiveBox.param).equals("plasmFB")) {tokenPlasma=1;}
    if (String(receiveBox.param).equals("fireFB")) {tokenFire=1;}
    if (String(receiveBox.param).equals("rldFB")) {tokenReload=1;}
    if (String(receiveBox.param).equals("modeFB")) {tokenMode=1; modeFeu++; if(modeFeu>2) {modeFeu=1;} Serial.println(modeFeu);}
    //Serial.print(receiveBox.param); sps ; Serial.println(receiveBox.value);
    
    if (String(receiveBox.param).startsWith("NP")){
      int NPled = recParamString.charAt(6) - 48;
      int bande = recParamString.charAt(5) ;
      //Serial.println(String(NPled));
       if (recParamString.charAt(5) == 65) {
        for (int i=NPled; i<5 ; i++) {stripAmmo.setPixelColor(i+1, 0, 0, 0); stripAmmo.show();}
        
        if (recParamString.startsWith("NPRed")) {redNP = receiveBox.value;}
        if (recParamString.startsWith("NPGre")) {greNP = receiveBox.value;}
        if (recParamString.startsWith("NPBlu")) {bluNP = receiveBox.value;

        stripAmmo.setPixelColor(NPled, redNP, greNP, bluNP); 
        stripAmmo.show();
        Serial.print(NPled); sps; Serial.print(redNP); sps; Serial.print(greNP); sps; Serial.println(bluNP); 
        }
      }
    }
  process = 0;
  }


if (mireCible) {  digitalWrite(A2, HIGH);}
else{digitalWrite(A2, LOW);}



////////////////////////////////Feedbacks
//if (tokenFire) {chargedFireFB();}

//if (tokenPlasma){plasmaLedFB();}

if (tokenReload) {reloadLedFB(); }

if (tokenMode) { modeFB(); }






////////////////////////////////RAZ
/*
//pour libérer la gachette
if (digitalRead(A1) == LOW && millis() > debounceGachette)
  {  panFlag = HIGH ;
  debounceGachette = millis() + 50;  }*/

    
}

