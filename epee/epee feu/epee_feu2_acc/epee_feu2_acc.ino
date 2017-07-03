#include <Adafruit_NeoPixel.h>
#include <Wire.h> 
#include <math.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6 //pin number that you have connected your data pin to
#define PIXNUMBER 8 //number of neopixels you have connected

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

struct RGB {
  byte r;
  byte g;
  byte b;
};

//  The flame color array (the first is the default):
RGB flameColors[] = {
  { 226, 121, 35},  // Orange flame
  { 158, 8, 148},   // Purple flame 
  { 74, 150, 12},   // Green flame
  { 226, 15, 30}    // Red flame
  };

int NUMBER_OF_COLORS = sizeof(flameColors) / sizeof(RGB);

//  Tracks the current color
int currentColorIndex = 0;





int bright = 10 ;
int coul;
int red;
int green;
int blue;

unsigned long nextRefresh = 0 ;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXNUMBER, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options
uint32_t noir = strip.Color(0, 50, 50);
uint32_t orange1 = strip.Color(226, 121, 35);
uint32_t nuance2 = strip.Color(255, 239, 180);
uint32_t nuance3 = strip.Color(250, 200, 53);
uint32_t nuance4 = strip.Color(191, 56, 0);
uint32_t blanc   = strip.Color(255, 255, 255);

int randCoul(int index){
switch(index){
  case 1 : 
  return orange1;
  break ;

  case 2 : 
  return nuance2;
  break ;

  case 3 :
  return nuance3;
  break ;

  case 4 :
  return nuance4;
  break ;
  }
}

void setup() 
{ 
  strip.begin();
  strip.show();//sets all pixels to off state
  strip.setBrightness(5);

  Serial.begin(9600); 
  
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
    
   x=(float)x_data/divi; 
   y=(float)y_data/divi;
   z=(float)z_data/divi;
  /* Serial.print("X=");   
   Serial.print(x);         // print the character
   Serial.print("  "); 
   Serial.print("Y=");   
   Serial.print(y);         // print the character
   Serial.print("  "); 
   Serial.print("Z=");           // print the character
   Serial.println(z);   */
}
   
void loop() {
oldx = mainx;
oldy = mainy;
oldz = mainz;

  RGB currentColor = flameColors[currentColorIndex];
 
  switch(range)  //change the data dealing method based on the range u've set
  {
  case 0x00:divi=16;  break;
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

mainx = mainx;
mainy = mainy;
mainz = mainz;

diffx = oldx - mainx;
diffy = oldy - mainy;
diffz = oldz - mainz; 

if (diffx < 0) {diffx = -1 * diffx;}
if (diffy < 0) {diffy = -1 * diffy;}
if (diffz < 0) {diffz = -1 * diffz;}
/*
     Serial.print(diffx);   
     Serial.print(" ");
     Serial.print(diffy);   
     Serial.print(" ");
     Serial.println(diffz);   */

mainx = mainx;
mainy = mainy;
mainz = mainz;
/*
  constrain(mainx, 0, 255);
  constrain(mainy, 0, 255);
  constrain(mainz, 0, 255);
     
  analogWrite(3, mainx);
  analogWrite(5, mainy);
  analogWrite(9, mainz);*/

if (nextRefresh < millis() ){
      for(int i=0; i<strip.numPixels(); i++) {
    int flicker = random(0,55);
    int r1 = currentColor.r-flicker;
    int g1 = currentColor.g-flicker;
    int b1 = currentColor.b-flicker;
    if(g1<0) g1=0;
    if(r1<0) r1=0;
    if(b1<0) b1=0;
    strip.setPixelColor(i,r1,g1, b1);
  }
  nextRefresh = millis() + 60 ;

//  if (diffx > 200) {strip.setPixelColor(i, blanc); nextRefresh = millis() + 250 ;}
  }


Serial.print(red);
Serial.print(" ");
Serial.print(green);
Serial.print(" ");
Serial.print(blue);
Serial.println(" ");

  bright = diffx;
  float j = float(bright)/100;
  j = exp(j) * 20   ;
  j = j - 20;
   // Serial.print(j);   Serial.println(" ");
  
  bright = constrain(j, 1, 255);
  strip.setBrightness(bright);
strip.show();
delay(10);
  
}
