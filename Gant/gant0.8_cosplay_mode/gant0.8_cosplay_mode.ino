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
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXNUMBER, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options

//nrf24l01
#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI


//configuration
//#include "feedback.h"

//données capteur
int p ;
int i ;
int m ;
int an;
int au;
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
bool hubMode = 0 ;

//Infrarouge
const int RECV_PIN = 6;
IRrecv irrecv(RECV_PIN);
decode_results results;

bool getValue = HIGH ;
unsigned long nextGetValue = 0 ;
int refrRate = 200 ;

String cible = "vide" ; // ou char ou 

String idJoueur = "111111" ; //osef
char *IDobjet = "nrf04";
char *toIDobjet = "nrf01" ;     //ID de l'objet qui est sensé recevoir

bool debug_mode = LOW ;

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


typedef struct {
  char objectStru = 'g' ;
  char commande;
  int valeur;
} MaStructure;

//ou pas :
typedef struct{
  char objectStru = 'g' ;
  char action = 'v' ;
    char commandeX = 'x' ;
  int valeurX;
    char commandeY = 'y' ;
  int valeurY;
    char commandeZ = 'z' ;
  int valeurZ;

    char commandePouce = 'p';
  int valeurPouce;
    char commandeIndex = 'i' ;
  int valeurIndex;
    char commandeMajeur = 'm' ;
  int valeurMajeur;
    char commandeAnnulaire = 'a' ;
  int valeurAnnulaire;
    char commandeAuriculaire = 'o' ;
  int valeurAuriculaire;
  
} infosGantStruct ;

bool prepaT2Ftoken = LOW ;
bool launchT2Ftoken = LOW ;
bool cancelT2Ftoken = LOW ;

unsigned long timeCancelT2F ;

void prepaT2F(){
  for(int i=0; i<PIXNUMBER; i++){
    red  = random(210, 255);

    green= red - 160 ;
    green= green + random(0,150);
  
    blue= random(0, 2);
    
    strip.setPixelColor(i, red*bright, green*bright, blue*bright);
    strip.show();
  }
}


void launchT2F(){
    for(int i=0; i<PIXNUMBER; i++){
    strip.setPixelColor(i, 200, 200, 200);
    strip.show();
  }
  
    delay(20);
    
    for(int i=0; i<PIXNUMBER; i++){
    strip.setPixelColor(i, 0, 0, 0);
    strip.show();
    }
}


void cancelT2F(){
  for(int i=0; i<PIXNUMBER; i++){
    strip.setPixelColor(i, 0, 0, 0);
    strip.show();
  }
}
 
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////SETUP/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  strip.begin();
  strip.show();//sets all pixels to off state
  strip.setBrightness(departBright);  //jusqu'à 100
  
  Mirf.cePin = 9; // Broche CE sur D9
  Mirf.csnPin = 10; // Broche CSN sur D10
  Mirf.spi = &MirfHardwareSpi; // On veut utiliser le port SPI hardware
  Mirf.init(); // Initialise la bibliothèque

  Mirf.channel = 1; // Choix du canal de communication (128 canaux disponibles, de 0 à 127)
  Mirf.payload = sizeof(MaStructure); //32; // Taille d'un message (maximum 32 octets)
  Mirf.config(); // Sauvegarde la configuration dans le module radio

  Mirf.setTADDR((byte *) toIDobjet);//toIDobjet); "nrf02"); // Adresse de transmission
  Mirf.setRADDR((byte *) IDobjet);//IDobjet); //"nrf01"); // Adresse de réception
  

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
  
  Serial.begin(9600); 
  irrecv.enableIRIn(); // Start the receiver
  //irrecv.blink13(true);
  
  Serial.println("Gant V0.8 + cosplayMode");
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
MaStructure messageStru ;
infosGantStruct infosGant ;
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

p = analogRead(A0);
i = analogRead(A1);
m = analogRead(A2);
an = analogRead(A3);
au = analogRead(A6);

valeursGant[0] = x ;
valeursGant[1] = y ;
valeursGant[2] = z ;
valeursGant[3] = p ;
valeursGant[4] = i ;
valeursGant[5] = m ;
valeursGant[6] = an ;
valeursGant[7] = au ;

/*
 * Code récolte IR ici
 * 
 */

//////////////////////////////////Fin de récolte des données des capteurs



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
//////////////////////////////////////////////////////////////////////Mode Hub

if (hubMode){
  if (getValue) {
    for (int i=0; i<8; i++) {
      if (debug_mode) {
        Serial.print("to_"); Serial.print(idJoueur); Serial.print("_from_:"); Serial.print(IDobjet); Serial.print("_valAdresse_:"); 
        Serial.print(i); Serial.print("_valeur_:"); Serial.println(valeursGant[i]);
        Serial.println();
      }
    delay(15);
      messageStru.commande = i + '0' ;//Serial.read(); //g : doigt
      messageStru.valeur = valeursGant[i] ;//Serial.parseInt(); //valeur : 1, ok. 2, non. ...
      Mirf.send((byte*) &messageStru); // On envoie le message (Strings) et strucutre
      while(Mirf.isSending()); // On attend la fin de l'envoi
    }


  if(Mirf.dataReady())  {
    Mirf.getData((byte*) &messRCVhF);
    switch (messRCVhF) {
      case 10 :
      prepaT2Ftoken = HIGH;

      break;
      
      case 11 :
      launchT2Ftoken = HIGH;
      break;
      
      case 12 :
      cancelT2Ftoken = HIGH;
      break;
      }
    }
  }
}

/////////////////////////////////////Feedbacks

  if(prepaT2Ftoken) {prepaT2F(); timeCancelT2F = millis() + 2000; }
  if(launchT2Ftoken) {launchT2F();}
  if(cancelT2Ftoken) {cancelT2F();!prepaT2Ftoken;}
  if (millis()>timeCancelT2F) {cancelT2F(); prepaT2Ftoken=LOW;}


  //envoi de cible
  //if (debug_mode) {Serial.print("cible_"); Serial.println(cible);}
  


}
