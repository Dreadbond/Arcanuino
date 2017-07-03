/*
{
    "fromId": ":111111",
    "toId": ":123456",
    "rawPiercingDamage": 100
}
*/

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

//infrarouge
int RECV_PIN = 5;
IRrecv irrecv(RECV_PIN);
decode_results results;

//Radio nrf24L01
RF24 radio(9,10);  // make sure this corresponds to the pins you are using : SCL SO
const uint64_t pipes[4] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL, 0xF0F0F0F066, 0xF0F0F0F012 };

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


//données
int debug = 0 ;
char IDObject[8] = ":pistol";
char charCible[8];
bool process ;
int redNP ;
int greNP ;
int bluNP ;


//gâchette
bool mireCible ;
bool panFlag = HIGH ;
unsigned long debounceGachette ;

int messRCVhF ;




void raz() {
    posCharRcv = 0 ;  //retour chariot
    cible = "!vide" ;
    strMessActual = "arf" ;      //strMessActual.remove(0);
    for (int i=0 ; i<lgMess; i++) {messActual[i] = '\0' ;}
    write_message = LOW;
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

bool tokenSight;
bool tokenReload;
bool tokenShoot ;
void shootFb(){
  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static int red ;
  static int green ;
  static int blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 10 ;
  static int TC2 = 40 ;
  static int TC3 = 200 ;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;

  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);
  
  if (chrono>TC0 && chrono<TC1) {
      //bright = 0.25;
      stripCanon.setPixelColor(2, 0, 0, 0);  stripCanon.show();
      stripCanon.setPixelColor(2, 100, 0, 0); 
      stripCanon.show();
  }

  if (chrono>TC1 && chrono<TC2){
    stripCanon.setPixelColor(2, 0, 0, 0);  stripCanon.show();
    stripCanon.setPixelColor(2, 255, 245, 0); 
    stripCanon.show();
  }
  if (chrono>TC2 && chrono<TC3) {
    stripCanon.setPixelColor(2, 0, 0, 0);  stripCanon.show();
  bright = (TC3-chrono)/5;

  red=190*bright/100;
  green=40*bright/100;
  blue=5*bright/100;
  
  red=constrain(red, 0, 255);
  green=constrain(green, 0, 255);
  blue=constrain(blue, 0, 255);
  
  stripCanon.setPixelColor(2, red, green, blue); 
  stripCanon.show();
  //shootFbToken=LOW;
  //effetStopFlag=HIGH;
  }
  if (chrono>TC3) {
    tokenShoot=LOW;
    for(int i=0 ; i<PixCanon ; i++) {stripCanon.setPixelColor(i, 0, 0, 0);  stripCanon.show();}
    }

}


//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Setup////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  strcpy( sendBox.from, IDObject );
  strcpy( sendBox.to, "!111111" );

  Serial.begin(57600);

  //Communications RF
  radio.begin();
  //radio.setAutoAck(true);
  radio.setPALevel(RF24_PA_MIN);
  //radio.setDataRate(RF24_2MBPS);
  //radio.setChannel(10);
  //radio.openWritingPipe(pipes[0]);
  //radio.openReadingPipe(1,pipes[1]);
  radio.setChannel(1);
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[2]);
  radio.startListening();
  //Communications RF

  stripCanon.begin();
  stripCanon.setBrightness(255);
  stripCanon.show();

  //pinMode(A2, OUTPUT);  //anciennement feedback shight

  irrecv.enableIRIn(); // Start the receiver
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A7, OUTPUT);
  digitalWrite(A7, LOW);
  
  Serial.println("Flingue 0.5d");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Loop/////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
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
    if (cosplayMode) {stripCanon.setPixelColor(0, 0, 255, 0); stripCanon.show(); }
    }
  
  }


//timeout ou message trop long: grosse galère, je compte sur le || strMessActual.length() == lgMess pour éviter ça
if (resetCible < millis() || strMessActual.length() > lgMess ) {   
  raz();
  if (cosplayMode) {stripCanon.setPixelColor(0, 0, 0, 0); stripCanon.show(); }
  //cible = "vide"; 
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////ENVOIS//////////////////////////////
////////////////////////////////////////////////////////////////////////


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


////////////////////////////////////Envoi action a : tir
if (digitalRead(A1) == LOW && panFlag == HIGH && millis() > debounceGachette) {  //1==1){
  Serial.println("Pan !");

  radio.stopListening();
  strcpy( sendBox.param, "trigger"); sendBox.value = 1; radio.write( &sendBox, sizeof(sendBox) );
  radio.startListening();

  panFlag = LOW ;
  debounceGachette = millis() + 20;
  }
//on libère la gachette pour le prochain loop
if (digitalRead(A1) == HIGH && millis() > debounceGachette)
  {
      if (!panFlag){
      radio.stopListening();
      strcpy( sendBox.param, "trigger"); sendBox.value = 0; radio.write( &sendBox, sizeof(sendBox) );
      radio.startListening();
      }
  panFlag = HIGH ;
  debounceGachette = millis() + 50;
  }

////////////////////////////////////Envoi action b : rechargement
if (digitalRead(A2) == LOW && panFlag == HIGH && millis() > debounceGachette) {  //1==1){
  Serial.println("Rechargement");

  radio.stopListening();
  strcpy( sendBox.param, "reload"); sendBox.value = 1; radio.write( &sendBox, sizeof(sendBox) );
  radio.startListening();
  }


//////////////////////////////////////Feedback
  if (radio.available() )
  {
      radio.read( &uncertainBox, sizeof(uncertainBox) );
      if (String(uncertainBox.to).equals(IDObject)) {
        receiveBox = uncertainBox ;
        //contenuUncertain();
        process=1;
        }
    
  }

String recFromString = String(receiveBox.from) ;    //pour aussi remettre à 0 la receiveBox
String recToString=String(receiveBox.to);
String recParamString=String(receiveBox.param);


  if (recToString == IDObject && process) {
      //Serial.println(receiveBox.to); Serial.println(receiveBox.param);
    if (recParamString == "shootFB") {tokenShoot=1;}
    if (recParamString == "rldFB") {tokenReload=1;}
    if (recParamString =="sightFB") {tokenSight=1;}
    if (recParamString.startsWith("NP")){
      int NPled = recParamString.charAt(6) - 48;
        if (recParamString.startsWith("NPRed")) {redNP = receiveBox.value; stripCanon.setPixelColor(NPled, 0, 0, 0);}
        if (recParamString.startsWith("NPGre")) {greNP = receiveBox.value;}
        if (recParamString.startsWith("NPBlu")) {bluNP = receiveBox.value;
        
        stripCanon.setPixelColor(NPled, redNP, greNP, bluNP); 
        stripCanon.show();
        //Serial.print(redNP); Serial.print(" "); Serial.print(greNP); Serial.print(" "); Serial.println(bluNP); 
        }
    }

  process = 0;
  }
  
//Serial.println(reception.trigger);
if (tokenShoot) {shootFb();}  //obsolète





}












