#include <Wire.h> 
#include <math.h>
#include <VirtualWire.h>

//Neopixel
#include <Adafruit_NeoPixel.h>
#define PIN 6 //pin number that you have connected your data pin to
#define PIXNUMBER 30 //number of neopixels you have connected
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXNUMBER, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options
uint32_t noir = strip.Color(0, 50, 50);
uint32_t orange1 = strip.Color(226, 121, 35);
uint32_t nuance2 = strip.Color(255, 239, 180);
uint32_t nuance3 = strip.Color(250, 200, 53);
uint32_t nuance4 = strip.Color(191, 56, 0);
uint32_t blanc   = strip.Color(255, 255, 255);
uint32_t toucheOrange= strip.Color(255, 0, 0);
int departBright = 255;
int bright = 10 ;
int coul;
float red;
float green;
float blue;

//nrf24L01
#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI
char *IDobjet = "nrf06";
char *toIDobjet = "nrf01" ;     //ID de l'objet qui est sensé recevoir

//Accéléromètre
byte Version[3];
int8_t x_data;
int8_t y_data;
int8_t z_data;
byte range=0x00;
float divi=16;
float x,y,z;
int oldx, oldy, oldz ;
int diffx, diffy, diffz;
int mainx, mainy, mainz;
int diffxMax;


int modeTeinte = 51;
int nbreCoups = 2 ;

//Traitement de données
int chiffreVoulu ;
int iMoyenne ;
int tableau[10] ;
int mesures = 10 ;
int forceMax ;
unsigned long gateCoup ;

unsigned long nextRefresh = 0 ;

//Envoi messages
bool flagSend = HIGH ;
bool sendTicket = LOW ;

typedef struct {
  char objectStru = 'p' ;  //Piquemord
  char commande;
  int valeur;
} actionStruct;

///////////////////////////////////////////////////////////////Fonctions
void teinteNoire() {
  for(int i=0 ; i<PIXNUMBER ; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
}

void teinteFeu(int intens, int posI) {
    //strip.setBrightness(100);

    bright = intens * random(1, 5);
    bright = bright + 10;
    bright = constrain(bright, 20, 255);

    red  = random(160,200);
    //float red = float(red);
    red  = red + diffy*2;
    red  = red * bright;
    red  = red / 255;
    
    //green= red - 100 ;
    //float green = float(green);
    green = red * 0.9;
    green= green - random(0, 10);
    //green= green - diffy*2;
    green= green * bright;
    green = green/255;
    //green= green / 255;

    //float blue = float(blue);
    blue = random(0,10);
    blue = blue * bright;
    blue = blue / 255;

    red = constrain(red, 0, 255);
    green = constrain(green, 2, 245);
    blue = constrain(blue, 0, 255);

    strip.setPixelColor(posI, red, green, blue);
    nextRefresh = millis() + 10 ;
    strip.show();
}

void teintePoison(int intens, int posI) {
    //strip.setBrightness(100);
  
    bright = intens;
    bright += random(-1, 1);
    bright = bright + 10;
    bright = constrain(bright, 10, 255);
    
    red = random(1, 10);
    red = red + PIXNUMBER - posI*5;
    
    red  = red * bright;
    red  = red / 255;

    green= random(170, 200);
    green= green + diffy;
    
    green= green * bright;
    green= green / 255;
    
    blue = green - 100;
    blue = blue - random(10, 30);
    blue = blue + PIXNUMBER - posI*5;
    
    blue = blue * bright;
    blue = blue / 255;
    
    red = constrain(red, 0, 255);
    green = constrain(green, 0, 255);
    blue = constrain(blue, 0, 245);

    strip.setPixelColor(posI, red, green, blue);
    nextRefresh = millis() + 20 ;
    strip.show();
}

void teinteBerserk(int intens, int posI) {
    
    //red  = random(1,160);
    red = 10;
    red  = red + intens*2;
    red  += posI*3;
    
    green= 0;
    
    blue = 0;
    
    red = constrain(red, 0, 255);
    green = constrain(green, 0, 255);
    blue = constrain(blue, 0, 255);

    strip.setPixelColor(posI, red, green, blue);
    nextRefresh = millis() + 10 ;
    strip.show();
/*
    bright = diffy * random(1, 5);
    bright = bright + 10;
    bright = constrain(bright, 20, 255);*/
    //strip.setBrightness(bright);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() { 
  Mirf.cePin = 9; // Broche CE sur D9
  Mirf.csnPin = 10; // Broche CSN sur D10
  Mirf.spi = &MirfHardwareSpi; // On veut utiliser le port SPI hardware
  Mirf.init(); // Initialise la bibliothèque

  Mirf.channel = 1; // Choix du canal de communication (128 canaux disponibles, de 0 à 127)
  Mirf.payload = sizeof(actionStruct); //32; // Taille d'un message (maximum 32 octets)
  Mirf.config(); // Sauvegarde la configuration dans le module radio

  Mirf.setTADDR((byte *) toIDobjet);//toIDobjet); "nrf02"); // Adresse de transmission
  Mirf.setRADDR((byte *) IDobjet);//IDobjet); //"nrf01"); // Adresse de réception
  
  strip.begin();
  strip.show();//sets all pixels to off state
  strip.setBrightness(255);  //jusqu'à 255

  Serial.begin(9600); 
  Serial.println("Epee de feu HF V0.1");
  
  Wire.begin(); 
  Wire.beginTransmission(0x0A); // address of the accelerometer 
  // range settings
  Wire.write(0x22); //register address
  Wire.write(range); //can be set at"0x00""0x01""0x02""0x03", refer to Datashhet on wiki
  // low pass filter  
  Wire.write(0x20); //register address
  Wire.write(0x05); //can be set at"0x05""0x04"......"0x01""0x00", refer to Datashhet on wiki
  Wire.endTransmission();

  
  digitalWrite(3, OUTPUT);
  digitalWrite(5, OUTPUT);
  digitalWrite(9, OUTPUT);

  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);


  digitalWrite(2, LOW);
  digitalWrite(5, HIGH);
} 

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

   
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
    
   x=(float)x_data/divi; 
   y=(float)y_data/divi;
   z=(float)z_data/divi;
}


int moyenney(int entree){
  //int i ;
  //int tableau[10] ;
  int somme ;
  tableau[iMoyenne] = entree ;
  iMoyenne++;
  //Serial.print(tableau[iMoyenne]); Serial.print(" ");Serial.println(iMoyenne);


      for(int j=0 ; j<mesures ; j++){
      somme += tableau[j] ; 
      //Serial.print(j);
      }
  //somme = tableau[1] + tableau[2] + tableau[3] + tableau[4] + tableau[5] + tableau[6] + tableau[7] + tableau[8] + tableau[9] + tableau[10] ;
  /*
      Serial.print(tableau[0]); Serial.print(" ");
      Serial.print(tableau[1]); Serial.print(" ");
      Serial.print(tableau[2]); Serial.print(" ");
      Serial.print(tableau[3]); Serial.print(" ");
      Serial.print(tableau[4]); Serial.print(" ");
      Serial.print(tableau[5]); Serial.print(" ");
      Serial.print(tableau[6]); Serial.print(" ");
      Serial.print(tableau[7]); Serial.print(" ");
      Serial.print(tableau[8]); Serial.print(" ");
      Serial.print(tableau[9]); Serial.print(" ");
      Serial.print(tableau[10]); Serial.print(" ");*/
  //somme = somme/10;
  if (iMoyenne >= mesures) {iMoyenne=0;}
  return somme;
}


///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
   
void loop() {
actionStruct messageStru;

oldx = mainx;
oldy = mainy;
oldz = mainz;
 
  switch(range)  //change the data dealing method based on the range u've set
  {
  case 0x00:divi=16;  break;
  case 0x01:divi=8;  break;
  case 0x02:divi=4;  break;
  case 0x03:divi=2;  break;
  default: Serial.println("range setting is Wrong,range:from 0to 3.Please check!");while(1); 
  }
  AccelerometerInit(); 

if (mainx < 0) {mainx = -mainx;}
if (mainy < 0) {mainy = -mainy;}
if (mainz < 0) {mainz = -mainz;}

mainx = x*100;
mainy = y*100;
mainz = z*100;

diffx = oldx - mainx;
diffy = oldy - mainy;
diffz = oldz - mainz; 

if (diffx < 0) {diffx = -diffx;}
if (diffy < 0) {diffy = -diffy;}
if (diffz < 0) {diffz = -diffz;}

chiffreVoulu = moyenney(mainy) ;
//Serial.print(mainx); Serial.print(" "); Serial.print(mainy); Serial.print(" "); Serial.print(mainz); Serial.print(" "); Serial.println(chiffreVoulu);
//Serial.print(diffy); Serial.print(" "); Serial.println(mainy);


if (gateCoup<millis() ){
  static unsigned long chrono ;
  static unsigned long timeTag ;
    if (diffy > 50 || chrono>0 ) {
      
      if (millis()-100>chrono+timeTag) {timeTag=millis();}
      chrono=millis() - timeTag;

      //if (diffy>forceMax) {forceMax=diffy;}
      forceMax += diffy;
      
      if (chrono>200) {
        Serial.print("La !"); Serial.println(forceMax);
        messageStru.commande = 'h' ;//Serial.read(); //h : hit
        messageStru.valeur = forceMax/40 ;//Serial.parseInt(); //valeur : 1, ok. 2, non. ...
      
        Mirf.send((byte*) &messageStru); // On envoie le message (Strings) et strucutre
        while(Mirf.isSending()); // On attend la fin de l'envoi
        gateCoup = millis() + 500;
        forceMax=0;
      }
    }
  }

}
/*
if (Serial.available()) {modeTeinte = Serial.read();}

  if(Serial.read() > 0 && Serial.read() < 4) {modeTeinte = Serial.read();  }


  if (diffy > 50 && modeTeinte == 151) {   //200 normalement
    //for(int i=0 ; i<PIXNUMBER ; i++) {     //flash coup
    //strip.setPixelColor(i, red+70, green+70, blue+70); }
    //nextRefresh = millis() + 100 ; //ou 200ms
    sendCoup(diffy);
    nbreCoups--;
    nbreCoups = constrain(nbreCoups, 0, 5);
    Serial.println(nbreCoups);
  }

if (nbreCoups == 0 && modeTeinte > 0) {
  teinteNoire();
  modeTeinte = 0;
  }

if (nextRefresh < millis() && modeTeinte > 0 && nbreCoups > 0){
  for(int i=0 ; i<PIXNUMBER ; i++) {

      switch (modeTeinte){
        case 48:
        teinteNoire();
        modeTeinte = 0;
        break;
        
        case 49:
        teinteFeu(diffy, i);
        break;

        case 50:
        teintePoison(diffy, i);
        break;

        case 51:
        teinteBerserk(diffy, i);
        break;
      }
     }
     
}
//strip.show();
//delay(10);
*/
