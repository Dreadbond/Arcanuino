#include <IRremote.h>
#include <Wire.h> 

//Neopixel
#include <Adafruit_NeoPixel.h>
#define PIN 4 //pin number that you have connected your data pin to
#define PIXNUMBER 3 //number of neopixels you have connected
int departBright = 255;
int bright = 10 ;
int coul;
float red;
float green;
float blue;
int vibreur = 5 ;
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



String cible = "vide" ; // ou char ou 



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





bool fireCastToken = LOW ;
void fireCastFb(){

  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static int red ;
  static int green ;
  static int blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 6000 ;
  static int TC2 = TC1 + 2000 ;
  static int TC3 = TC2 + 1000 ;
  
  static int TC4 ;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;
  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);
  
  if (chrono>TC0 && chrono<TC1) {
    for(int i=0; i<3 ; i++) {
      red  = random(210, 255);
      green= red - 160 ;
      green= green + random(0,100);

      bright = map(chrono, TC0, TC1, 0, 50) ;
      bright /= 100 ;
      
      strip.setPixelColor(i, red*bright, green*bright, 0); 
      strip.show();
    }
    
    
  }
  if (chrono>TC1 && chrono<TC2) {
    for(int i=0; i<3 ; i++) {
      red  = random(210, 255);
      green= red - 160 ;
      green= green + random(0,100);

      bright = 0.5 ;
      strip.setPixelColor(i, red*bright, green*bright, 0); 
      strip.show();
    }
    //analogWrite(vibreur, bright*100);
  }
  if (chrono>TC2 && chrono<TC3) {
    for(int i=0; i<3 ; i++) {
      red  = random(210, 255);
      green= red - 160 ;
      green= green + random(0,100);

      blue = map(chrono, TC2, TC3, 0, 80);

      bright = map(chrono, TC2, TC3, 50, 0) ;
      bright /= 100 ;

      strip.setPixelColor(i, red*bright, green*bright, blue*bright); 
      strip.show();
    }
    //analogWrite(vibreur, bright*100);
  }
  if (chrono>TC3 ) {
    for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
    analogWrite(vibreur, 0);
  fireCastToken=LOW;
  }
  
  Serial.println(bright*200 + 100);
  analogWrite(vibreur, bright*200 + 100);

}


unsigned long timeCancelT2F ;

bool fireBallFbToken = LOW ;
void fireBallFb(){

  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static int red ;
  static int green ;
  static int blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 100 ;
  static int TC2 = TC1 + 200 ;
  static int TC3 = TC2 + 1000 ;
  
  static int TC4 ;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;
  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);
  
  if (chrono>TC0 && chrono<TC1) {
    for(int i=0; i<3 ; i++) {
      red  = random(210, 255);
      green= red - 160 ;
      green= green + random(0,100);

      bright = map(chrono, TC0, TC1, 0, 100);
      bright /= 100 ;
      
      strip.setPixelColor(i, red*bright, green*bright, blue*bright); 
      strip.show();
    }
  }
  if (chrono>TC1 && chrono<TC2) {
    for(int i=0; i<3 ; i++) {
      red  = random(230, 255);
      green= red - 160 ;
      green= green + random(70,100);
      blue = 80 ;

      bright = 1 ;
      strip.setPixelColor(i, red*bright, green*bright, blue*bright); 
      strip.show();
    }
  }
  if (chrono>TC2 && chrono<TC3) {
    for(int i=0; i<3 ; i++) {
      red  = random(150, 255);
      green= red - 160 ;
      green= green + random(0,100);
      blue = 0 ;
      //blue = map(chrono, TC2, TC3, 0, 80);

      bright = map(chrono, TC2, TC3, 70, 0) ;
      bright /= 100 ;

      strip.setPixelColor(i, red*bright, green*bright, blue*bright); 
      strip.show();
    }
  }
  if (chrono>TC3 ) {
    for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
  fireBallFbToken=LOW;
  }
}

bool protectionCastToken = LOW ;
void protectionCastFb(){
  //PIXNUMBER
  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static float red ;
  static float green ;
  static float blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 5000 ;
  static float index ;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;
  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);

  red = 200;
  green = 200;
  blue = 200;
  
  if (chrono>TC0 && chrono<TC1) {
    //for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); }
      //for(int i=0; i<PIXNUMBER ; i++) {

      int i = random(0 , 3);
      bright = random(0 , 10);
      bright /= 100 ;
      
      strip.setPixelColor(i, red*bright, green*bright, blue*bright); 
      strip.show();
      //}
  }
  if (chrono>TC1 ) {
    for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); strip.show();}
  protectionCastToken=LOW;
  }
}

bool protectionFbToken = LOW ;
void protectionFb(){
  //PIXNUMBER
  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static float red ;
  static float green ;
  static float blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 200 ;
  static int TC2 = TC1 + 2000 ;
  static int TC3 = TC2 + 500 ;
  static float index ;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;
  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);

  red = 200;
  green = 200;
  blue = 200;
  
  if (chrono>TC0 && chrono<TC1) {
    //for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); }
      for(int i=0; i<PIXNUMBER ; i++) {
        
      bright = map(chrono, TC0, TC1, 0, 100);
      bright /= 100 ;
      
      strip.setPixelColor(i, red*bright, green*bright, blue*bright); 
      strip.show();
      }
  }
  if (chrono>TC1 && chrono<TC2){
    //for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); }
      for(int i=0; i<PIXNUMBER ; i++) {

      //bright = random(85, 100);
      //Serial.println(bright);
      //bright /= 100 ;
      //bright = constrain(bright, 0, 100);
      bright = 100 ;

      strip.setPixelColor(i, red*bright/100, green*bright/100, blue*bright/100); 
      strip.show();
      }
  }
  if (chrono>TC2 && chrono<TC3){
    //for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); }
      for(int i=0; i<PIXNUMBER ; i++) {
        
      bright = map(chrono, TC2, TC3, 100, 0);
      bright /= 100 ;
      
      strip.setPixelColor(i, red*bright, green*bright, blue*bright); 
      strip.show();
      }
  }
  if (chrono>TC3 ) {
    for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); strip.show();}
  protectionFbToken=LOW;
  }
}


 
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////SETUP/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  strcpy( sendBox.from, IDObject );
  strcpy( sendBox.to, "!111111" );

  Serial.begin(57600); 
  Serial.println("Gant V0.91");

  
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
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A6, INPUT);
  
  pinMode(vibreur, OUTPUT);

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



/*
 * Code récolte IR ici
 * 
 */

//////////////////////////////////Fin de récolte des données des capteurs
//    for(int i=0; i<PIXNUMBER; i++){
//////////////////////////////////Envoi vers hub   //sendBox  sendGantDoigts  sendGantAcc
if (getValue){
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




//////////////////////////////////////////////////////////////////////Mode cosplay
/*
if (cosplayMode){
if (p < 1000) {pFlag = HIGH;} else {pFlag = LOW;}
if (i < 1000) {iFlag = HIGH;} else {iFlag = LOW;}
if (m < 1000) {mFlag = HIGH;} else {mFlag = LOW;}
if (an < 1000) {anFlag = HIGH;} else {anFlag = LOW;}
if (au < 1000) {auFlag = HIGH;} else {auFlag = LOW;}

//fireball casting and growing
if (mFlag && anFlag && fireBall.nextPoll<millis() && fireBall.castToken && fireBall.castStrengh<100) {
  fireBall.castStrengh += 5 ;
  fireBall.cancelTimeTag = millis() + 2000 ;
  fireBall.nextPoll = millis()+200;
  Serial.println(fireBall.castStrengh);
  }

if (fireBall.castStrengh>20) {fireBall.launchToken=1;Serial.println("Prete !");}
  /*
//lancement boule de feu
if (x<10 && x>-10 && y<100 && z> 85 && fireBall.launchToken){
fireBall.xStrengh += fireBall.xStrengh ;
Serial.print(x);Serial.print(" ");  Serial.print(y); Serial.print(" "); Serial.println(z); 
  if (fireBall.xStrengh>=200) {
    Serial.println("Lancement boule de feu");
  }
}

//lancement en AoE
if (y<10 && y>-10 && x<100 && z<85 && fireBall.launchToken){
fireBall.xStrengh += fireBall.xStrengh ;
  if (fireBall.xStrengh>=200) {
    Serial.println("Lancement AoE de feu");
  }
}*/
/*
//fireBall timeout
if (fireBall.cancelTimeTag<millis() && fireBall.castToken){
fireBall.castStrengh = 0;
fireBall.castToken = 0;
fireBall.launchToken = 0;
fireBall.xStrengh = 0 ;
fireBall.yStrengh = 0 ;
fireBall.zStrengh = 0 ;
fireBall.cooldown = millis() + 1000 ;
}

//fireball ok to cast
if (fireBall.cooldown<millis()) {
fireBall.castStrengh = 0;
fireBall.castToken = 1;
fireBall.launchToken = 1;
fireBall.xStrengh = 0 ;
fireBall.yStrengh = 0 ;
fireBall.zStrengh = 0 ;
}
*/
//}



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
    if (String(receiveBox.param).equals("fireCast")) {fireCastToken=1;}
    if (String(receiveBox.param).equals("fireball")) {fireCastToken=0 ; fireBallFbToken=1;}   
    if (String(receiveBox.param).equals("protCast")) {protectionCastToken=1; }
    if (String(receiveBox.param).equals("protec")) {protectionCastToken=0 ; protectionFbToken=1;}

  process = 0;
  }

/////////////////////////////////////Feedbacks

  if(fireCastToken) fireCastFb();
  if(fireBallFbToken) fireBallFb();

  if(protectionCastToken) protectionCastFb();
  if(protectionFbToken) protectionFb();



  //envoi de cible
  //if (debug_mode) {Serial.print("cible_"); Serial.println(cible);}
  


}
