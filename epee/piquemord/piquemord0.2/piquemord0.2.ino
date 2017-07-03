#include <Adafruit_NeoPixel.h>
#include <Wire.h> 
#include <math.h>

#define PIN 6 //pin number that you have connected your data pin to
#define PIXNUMBER 30 //number of neopixels you have connected

#define sps Serial.print(" ");
#define spr Serial.println();

//capteur capacitif
#include <CapacitiveSensor.h>
int sensi = 20 ;
long capacitif ;
CapacitiveSensor   cs_7_2 = CapacitiveSensor(7, 2);       // 10 megohm resistor between pins 7 & 2, pin 2 is sensor pin, add wire, foil


//traitement données
bool process ;

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

int departBright = 255;
int bright = 10 ;
int coul;
float red;
float green;
float blue;

int chiffreVoulu ;
int iMoyenne ;
int tableau[10] ;
int mesures = 10 ;

unsigned long nextRefresh = 0 ;

//Communications RF

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
RF24 radio(9,10);  // make sure this corresponds to the pins you are using : SCL SO
const uint64_t pipes[4] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL, 0xF0F0F0F066, 0xF0F0F0F012 };
char IDObject[8] = ":sword";
unsigned long nextSend ;

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


int redNP ;
int greNP ;
int bluNP ;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXNUMBER, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options
uint32_t noir = strip.Color(0, 50, 50);
uint32_t orange1 = strip.Color(226, 121, 35);
uint32_t nuance2 = strip.Color(255, 239, 180);
uint32_t nuance3 = strip.Color(250, 200, 53);
uint32_t nuance4 = strip.Color(191, 56, 0);
uint32_t blanc   = strip.Color(255, 255, 255);
uint32_t toucheOrange= strip.Color(255, 0, 0);

void teinteNoire() {
  for(int i=0 ; i<PIXNUMBER ; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
}

//#include "feedback_sword.h"




bool tokenEnAvant;
void enAvantFb(){
  //PIXNUMBER
  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static int red ;
  static int green ;
  static int blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 500 ;
  static int TC2 = 700 ;
  static int TC3 = 3000 ;
  static float index ;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;
  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);


  
  if (chrono>TC0 && chrono<TC1) {
    for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0);}  //  strip.show();  <--- show() utile ?

    index = map(chrono, TC0, TC1, 0, 30);
    
    strip.setPixelColor(index, 255*index/30, 255*index/30, 50*index/30*5); 
    strip.show();
    strip.setPixelColor(index-1, 255*index/30, 255*index/30, 50*index/30*2); 
    strip.show();
    strip.setPixelColor(index-2, 150*index/30, 150*index/30, 0); 
    strip.show();
    strip.setPixelColor(index-3, 100*index/30, 100*index/30, 0); 
    strip.show();
    strip.setPixelColor(index-4, 50*index/30, 50*index/30, 0); 
    strip.show();
  }
  if (chrono>TC1 && chrono<TC2){
    //for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); }
      for(int i=0; i<PIXNUMBER ; i++) {
        
      bright = map(chrono, TC1, TC2, 80, 255);

      strip.setPixelColor(i, bright, bright, bright); 
      strip.show();
      }
  }
  if (chrono>TC2 && chrono<TC3){
    //for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); }
      for(int i=0; i<PIXNUMBER ; i++) {
        
      bright = map(chrono, TC2, TC3, 255, 0);
      
      strip.setPixelColor(i, bright, bright, bright); 
      strip.show();
      }
  }
  if (chrono>TC3 ) {
    for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); strip.show();}
  tokenEnAvant=LOW;
  effetStopFlag=HIGH;
  }
}

bool tokenProtec;
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
  static int TC1 = 500 ;
  static int TC2 = 3000 ;
  static int TC3 = 5000 ;
  static float index ;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;
  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);

  red = 255;
  green = 255;
  blue = 0;
  
  if (chrono>TC0 && chrono<TC1) {
    //for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); }
      for(int i=0; i<PIXNUMBER ; i++) {
        
      bright = map(chrono, TC0, TC1, 0, 100);
      
      strip.setPixelColor(i, red*bright/100, green*bright/100, blue*bright/100); 
      strip.show();
      }
  }
  if (chrono>TC1 && chrono<TC2){
    //for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); }
      for(int i=0; i<PIXNUMBER ; i++) {
        
      bright = random(80, 100);

      strip.setPixelColor(i, red*bright/100, green*bright/100, blue*bright/100); 
      strip.show();
      }
  }
  if (chrono>TC2 && chrono<TC3){
    //for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); }
      for(int i=0; i<PIXNUMBER ; i++) {
        
      bright = map(chrono, TC2, TC3, 100, 0);
      
      strip.setPixelColor(i, red*bright/100, green*bright/100, blue*bright/100); 
      strip.show();
      }
  }
  if (chrono>TC3 ) {
    for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); strip.show();}
  tokenProtec=LOW;
  effetStopFlag=HIGH;
  }
}

/*
bool tokenClock;
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

bool tokenAntiClock;
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
*/
bool tokenMoulinet;
void teinteBerserk() {
  //PIXNUMBER
  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static float red ;
  static float green ;
  static float blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 700 ;
  static int TC2 = 3500 ;
  static int TC3 = 3500 ;
  static float index ;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;
  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);

  red = 255;
  green = 0;
  blue = 0;
  
  if (chrono>TC0 && chrono<TC1) {
    //for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); }
      for(int i=0; i<PIXNUMBER ; i++) {
      
      bright = map(chrono, TC0, TC1, 0, 100);
      bright *= float(random(50, 100)/2);
      
      strip.setPixelColor(i, red*bright/100, green*bright/100, blue*bright/100); 
      strip.show();
      }
  }
  if (chrono>TC1 && chrono<TC2){
    //for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); }
      for(int i=0; i<PIXNUMBER ; i++) {
        
      bright = random(80, 100);

      strip.setPixelColor(i, red*bright/100, green*bright/100, blue*bright/100); 
      strip.show();
      }
  }
  if (chrono>TC2 && chrono<TC3){
    //for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); }
      for(int i=0; i<PIXNUMBER ; i++) {
        
      bright = map(chrono, TC2, TC3, 100, 0);
      
      strip.setPixelColor(i, red*bright/100, green*bright/100, blue*bright/100); 
      strip.show();
      }
  }

  
  if (chrono>TC3 ) {
    for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); strip.show();}
  tokenMoulinet=LOW;
  effetStopFlag=HIGH;
  }
}

    


////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// SETUP /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() 
{
  strip.begin();
  strip.show();//sets all pixels to off state
  //strip.setBrightness(5);  //jusqu'à 100

  Serial.begin(57600); 
  Serial.println("Piquemord V0.2");
  
  Wire.begin(); 
  Wire.beginTransmission(0x0A); // address of the accelerometer 
  // range settings
  Wire.write(0x22); //register address
  Wire.write(range); //can be set at"0x00""0x01""0x02""0x03", refer to Datashhet on wiki
  // low pass filter  
  Wire.write(0x20); //register address
  Wire.write(0x05); //can be set at"0x05""0x04"......"0x01""0x00", refer to Datashhet on wiki
  Wire.endTransmission();

  //Communications RF
  strcpy( sendBox.from, IDObject );
  strcpy( sendBox.to, "!111111" );
  
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  //radio.openWritingPipe(pipes[0]);
  //radio.openReadingPipe(1,pipes[1]);
  radio.setChannel(1);
  radio.openWritingPipe(pipes[1]);   //0xF0F0F0F0D2LL    
  radio.openReadingPipe(1,pipes[4]);
  radio.startListening();
  //End communications RF
  
  digitalWrite(3, OUTPUT);
  digitalWrite(5, OUTPUT);
  digitalWrite(9, OUTPUT);

  pinMode(2, OUTPUT);
  pinMode(3, INPUT);    //entrée RF
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

void sendCoup(int puissance) {

}



///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
   
void loop() {

  
//sendCoup(5); delay(2000);
  
oldx = mainx;
oldy = mainy;
oldz = mainz;
 
  switch(range)  //change the data dealing method based on the range u've set
  {
  case 0x00:divi=16; break;
  case 0x01:divi=8;  break;
  case 0x02:divi=4;  break;
  case 0x03:divi=2;  break;
  default: Serial.println("range setting is Wrong,range:from 0to 3.Please check!");while(1); 
  }
  AccelerometerInit(); 

if (mainx < 0) {mainx = -1 * mainx;}
if (mainy < 0) {mainy = -1 * mainy;}
if (mainz < 0) {mainz = -1 * mainz;}

mainx = x*100;
mainy = y*100;
mainz = z*100;

/*
diffx = oldx - mainx;
diffy = oldy - mainy;
diffz = oldz - mainz; 

if (diffx < 0) {diffx = -1 * diffx;}
if (diffy < 0) {diffy = -1 * diffy;}
if (diffz < 0) {diffz = -1 * diffz;}
*/
if (nextSend < millis() ){
  radio.stopListening();
    strcpy( sendBox.param, "x"); sendBox.value = mainx; radio.write( &sendBox, sizeof(sendBox) );
    //radio.startListening();
  
    //radio.stopListening();
    strcpy( sendBox.param, "y"); sendBox.value = mainy; radio.write( &sendBox, sizeof(sendBox) );
    //radio.startListening();
  
    //radio.stopListening();
    strcpy( sendBox.param, "z"); sendBox.value = mainz; radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
  nextSend = millis() + 80 ;
}


capacitif =  cs_7_2.capacitiveSensor(30);
if (capacitif > 300) {
  Serial.println(capacitif);
    radio.stopListening();
    strcpy( sendBox.param, "capa"); sendBox.value = capacitif; radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
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
    if (String(receiveBox.param).equals("enavant")) {tokenEnAvant=1;}
    if (String(receiveBox.param).equals("protec")) {tokenProtec=1;}
    if (String(receiveBox.param).equals("moulin")) {tokenMoulinet=1;}
    /*
    
    if (String(receiveBox.param).equals("clock")) {tokenClock=1;}
    if (String(receiveBox.param).equals("antclck")) {tokenAntiClock=1;}
    
    */
    //Serial.print(receiveBox.param); sps ; Serial.println(receiveBox.value);
    if (String(receiveBox.param).startsWith("NP")){
      int NPled = recParamString.charAt(6) - 48;
      int bande = recParamString.charAt(5) ;
      Serial.println(String(NPled));
       if (recParamString.charAt(5) == 65) {
        for (int i=NPled; i<5 ; i++) {strip.setPixelColor(i+1, 0, 0, 0); strip.show();}
        
        if (recParamString.startsWith("NPRed")) {redNP = receiveBox.value;}
        if (recParamString.startsWith("NPGre")) {greNP = receiveBox.value;}
        if (recParamString.startsWith("NPBlu")) {bluNP = receiveBox.value;

        strip.setPixelColor(NPled, redNP, greNP, bluNP); 
        strip.show();
        Serial.print(NPled); sps; Serial.print(redNP); sps; Serial.print(greNP); sps; Serial.println(bluNP); 
        }
      }
    }
  process = 0;
  }
//enAvantFb();

  if (tokenEnAvant)   {enAvantFb();}
  if (tokenProtec)    {protectionFb();}
  if (tokenMoulinet)  {teinteBerserk();}
  /*
  if (tokenClock)     {clockwise();}
  if (tokenAntiClock) {antiClockwise();}

*/

  
//strip.show();
//delay(5);
}

