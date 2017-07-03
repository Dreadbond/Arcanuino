#include <IRremote.h>
#include <Wire.h> 

//Neopixel
#include <Adafruit_NeoPixel.h>
#define PIN 4 //pin number that you have connected your data pin to
#define PIXNUMBER 6 //number of neopixels you have connected
int departBright = 255;
int bright = 10 ;
int coul;
float red;
float green;
float blue;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXNUMBER, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options

//nrf24l01
#include <SPI.h>      // Pour la communication via le port SPI
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include "RF24.h"
RF24 radio(9,10);  // make sure this corresponds to the pins you are using : SCL SO
//0xF0F0F0F042
const uint64_t pipes[2] = { 0xF0F0F0F042, 0xF0F0F0F0D2LL };   //1er : selfObject, deuxième : hub
//const uint64_t pipes[5] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL, 0xF0F0F0F066, 0xF0F0F0F012, 0xF0F0F0F042 };
char IDObject[8] = ":gant";
char charCible[8];


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

//End Communications RF

//configuration
//#include "feedback.h"

//données
bool stopEffectToken ;
bool process ;
bool getValue = HIGH ;
unsigned long nextGetValue = 0 ;
int refrRate = 10 ;
int sendValue=1;
bool debug_mode = LOW ;

//données capteur
int p, i, m, an, au ;
int valeursGant[8] ;
bool pFlag ;
bool iFlag ;
bool mFlag ;
bool anFlag;
bool auFlag;

byte Version[3];
int8_t x_data;
int8_t y_data;
int8_t z_data;
byte range=0x00;
float divi=16;
float x,y,z;

//communication
int message_moniteur = 0 ; //49 pour données
int messRCVhF ;

bool cosplayMode = 1 ;

//Infrarouge
const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

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
//String cible = "vide" ; // ou char ou 
//bool cibleConfirmee = LOW ;

unsigned long faireMessageCible ;   //uniquement pour réception char
//unsigned long gateCible ;         //pour la cible en elle-même
unsigned long resetCible ;          //décision de perdre la cible

void raz() {
    posCharRcv = 0 ;  //retour chariot
    cible = "!vide" ;
    strMessActual = "arf" ;      //strMessActual.remove(0);
    for (int i=0 ; i<lgMess; i++) {messActual[i] = '\0' ;}
    write_message = LOW;
}




// Fireball spell
struct fireBall{
int nextPoll ;
unsigned long cancelTimeTag ;
unsigned long cooldown ;
int castStrengh ;
int xStrengh ;
int yStrengh ;
int zStrengh ;
bool launchToken = 1 ;
bool castToken = 1 ;
};


#include "feedback.h"

 
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////SETUP/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  strcpy( sendBox.from, IDObject );
  strcpy( sendBox.to, "!111111" );

  Serial.begin(9600); 
  Serial.println("Gant V0.93");

  
  strip.begin();
  strip.show();//sets all pixels to off state
  strip.setBrightness(departBright);  //jusqu'à 100
  
  radio.begin();
  radio.setChannel(1);
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[2]);
  radio.startListening(); 

  Wire.begin(); 
  Wire.beginTransmission(0x0A); // address of the accelerometer 
  // range settings
  Wire.write(0x22); //register address
  Wire.write(range); //can be set at"0x00""0x01""0x02""0x03", refer to Datashhet on wiki
  // low pass filter  
  Wire.write(0x20); //register address
  Wire.write(0x05); //can be set at"0x05""0x04"......"0x01""0x00", refer to Datashhet on wiki
  Wire.endTransmission();

  irrecv.enableIRIn(); // Start the receiver
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A6, INPUT);
  

  irrecv.enableIRIn(); // Start the receiver
  //irrecv.blink13(true);
  
}

void AccelerometerInit() 
{ 
  Wire.beginTransmission(0x0A); // address of the accelerometer 
  // reset the accelerometer 
  Wire.write(0x04); // Y data
  Wire.endTransmission(); 
  Wire.requestFrom(0x0A,1);    // request 6 bytes from slave device #2
  while(Wire.available())    // slave may send less than requested
  { 
    Version[0] = Wire.read(); // receive a byte as characte
  }  
  x_data=(int8_t)Version[0]>>2;
   
  Wire.beginTransmission(0x0A); // address of the accelerometer 
  // reset the accelerometer 
  Wire.write(0x06); // Y data
  Wire.endTransmission(); 
  Wire.requestFrom(0x0A,1);    // request 6 bytes from slave device #2
  while(Wire.available())    // slave may send less than requested
  { 
    Version[1] = Wire.read(); // receive a byte as characte
  }  
  y_data=(int8_t)Version[1]>>2;
    
  Wire.beginTransmission(0x0A); // address of the accelerometer 
  // reset the accelerometer 
  Wire.write(0x08); // Y data
  Wire.endTransmission(); 
  Wire.requestFrom(0x0A,1);    // request 6 bytes from slave device #2
   while(Wire.available())    // slave may send less than requested
  { 
    Version[2] = Wire.read(); // receive a byte as characte
  }
   z_data=(int8_t)Version[2]>>2; 
    
   x=(float)x_data/divi*100; 
   y=(float)y_data/divi*100;
   z=(float)z_data/divi*100;
}





///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////LOOP/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

void loop() {

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
        resetCible = millis() + 300;                    //délai avant perte de cible 300 à la base. 200 ensuite
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


fireBall fireBall ;


//////////////////////////////////Récolte des données des capteurs

if (nextGetValue < millis()) {getValue = HIGH; nextGetValue = millis() + refrRate ;} 
else {getValue = LOW; }

  switch(range)  //change the data dealing method based on the range u've set
  {
  case 0x00:divi=16;  break;
  case 0x01:divi=8;  break;
  case 0x02:divi=4;  break;
  case 0x03:divi=2;  break;
  default: Serial.println("range setting is Wrong,range:from 0to 3.Please check!");while(1); 
  }
  AccelerometerInit(); 

x = x;
y = y;
z = z;
p = analogRead(A0);
i = analogRead(A1);
m = analogRead(A2);
an = analogRead(A3);
au = analogRead(A6);



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

//////////////////////////////////Fin de récolte des données des capteurs
//    for(int i=0; i<PIXNUMBER; i++){
//////////////////////////////////Envoi vers hub   //sendBox  sendGantDoigts  sendGantAcc
if (getValue ){
  //Serial.println(sendValue);
  //radio.stopListening();
    //for(sendValue=1; sendValue<9; sendValue++){
      switch (sendValue) {
      case 1 :
      radio.stopListening();
      strcpy( sendBox.param, "x" ); sendBox.value = x;
      radio.write( &sendBox, sizeof(sendBox) ); 
      radio.startListening();
      break ;
  
      case 2 :
      radio.stopListening();
      strcpy( sendBox.param, "y" ); sendBox.value = y;
      radio.write( &sendBox, sizeof(sendBox) ); 
      radio.startListening();
      break ;
  
      case 3 :
      radio.stopListening();
      strcpy( sendBox.param, "z" ); sendBox.value = z;
      radio.write( &sendBox, sizeof(sendBox) ); 
      radio.startListening();
      break ;
  
  
      case 4 :
      radio.stopListening();
      strcpy( sendBox.param, "p" ); sendBox.value = p;
      radio.write( &sendBox, sizeof(sendBox) ); 
      radio.startListening();
      break ;
  
      case 5 :
      radio.stopListening();
      strcpy( sendBox.param, "i" ); sendBox.value = i;
      radio.write( &sendBox, sizeof(sendBox) ); 
      radio.startListening();
      break ;
  
      case 6 :
      radio.stopListening();
      strcpy( sendBox.param, "m" ); sendBox.value = m;
      radio.write( &sendBox, sizeof(sendBox) ); 
      radio.startListening();
      break ;
  
      case 7 :
      radio.stopListening();
      strcpy( sendBox.param, "an" ); sendBox.value = an;
      radio.write( &sendBox, sizeof(sendBox) ); 
      radio.startListening();
      break ;
  
      case 8 :
      radio.stopListening();
      strcpy( sendBox.param, "au" ); sendBox.value = au;
      radio.write( &sendBox, sizeof(sendBox) ); 
      radio.startListening();
      break ;
      }
    //}
    sendValue++;
    if(sendValue >= 9) {sendValue = 1;}
  //radio.startListening();
}
  

if (Serial.available() > 0) {message_moniteur = Serial.read() ; Serial.println(message_moniteur);}

if (message_moniteur == 49) {debug_mode = HIGH ;} else //if (message_moniteur == 50) 
{debug_mode = LOW;}

if (debug_mode) {
     Serial.print(x);   Serial.print(" ");
     Serial.print(y);   Serial.print(" ");
     Serial.print(z);   Serial.print(" ");
     
     Serial.print(p);   
     Serial.print(" ");
     Serial.print(i);   
     Serial.print(" ");
     Serial.print(m);   
     Serial.print(" ");
     Serial.print(an);   
     Serial.print(" ");
     Serial.println(au);  
    }


  if ( radio.available() )
  {
      radio.read( &uncertainBox, sizeof(uncertainBox) );
      //contenuUncertain();
      if (String(uncertainBox.to).equals(IDObject)) {
        receiveBox = uncertainBox ;
        contenuReceive();
        process = 1 ;
        }
  }

String recFromString = String(receiveBox.from) ;    //pour aussi remettre à 0 la receiveBox
String recToString=String(receiveBox.to);
String recParamString=String(receiveBox.param);

  if (String(receiveBox.to).equals(IDObject) && process) {
      //Serial.println(receiveBox.to); Serial.println(receiveBox.param);
    if (String(receiveBox.param).equals("fireCast")) {stopEffectToken=1 ; fireCastToken=1;}
    if (String(receiveBox.param).equals("fireball")) {stopEffectToken=1 ; fireBallFbToken=1;}   
    if (String(receiveBox.param).equals("protCast")) {stopEffectToken=1 ; protectionCastToken=1; }
    if (String(receiveBox.param).equals("protec"))   {stopEffectToken=1 ; protectionFbToken=1;}
    //if (String(receiveBox.param).equals("vampire")) {stopEffectToken=0 ; protectionFbToken=1;}

  process = 0;
  }

/////////////////////////////////////Feedbacks

  if(fireCastToken) fireCastFb();
  if(fireBallFbToken) fireBallFb();

  if(protectionCastToken) protectionCastFb();
  if(protectionFbToken) protectionFb();

}
