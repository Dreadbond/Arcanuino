#include <Adafruit_NeoPixel.h>
#include <Wire.h> 
#include <math.h>
#include <VirtualWire.h>

#define PIN 6 //pin number that you have connected your data pin to
#define PIXNUMBER 30 //number of neopixels you have connected

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

int departBright = 255;
int bright = 10 ;
int coul;
float red;
float green;
float blue;

unsigned long nextRefresh = 0 ;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXNUMBER, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options
uint32_t noir = strip.Color(0, 50, 50);
uint32_t orange1 = strip.Color(226, 121, 35);
uint32_t nuance2 = strip.Color(255, 239, 180);
uint32_t nuance3 = strip.Color(250, 200, 53);
uint32_t nuance4 = strip.Color(191, 56, 0);
uint32_t blanc   = strip.Color(255, 255, 255);
uint32_t toucheOrange= strip.Color(255, 0, 0);

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
/*
    bright = diffy * random(1, 5);
    bright = bright + 10;
    bright = constrain(bright, 20, 255);*/
    //strip.setBrightness(bright);
}


void setup() 
{ 
  strip.begin();
  strip.show();//sets all pixels to off state
  //strip.setBrightness(5);  //jusqu'à 

  Serial.begin(9600); 
  Serial.println("Epee de feu V0.63");
  
  Wire.begin(); 
  Wire.beginTransmission(0x0A); // address of the accelerometer 
  // range settings
  Wire.write(0x22); //register address
  Wire.write(range); //can be set at"0x00""0x01""0x02""0x03", refer to Datashhet on wiki
  // low pass filter  
  Wire.write(0x20); //register address
  Wire.write(0x05); //can be set at"0x05""0x04"......"0x01""0x00", refer to Datashhet on wiki
  Wire.endTransmission();

  vw_set_tx_pin(10);
  //vw_set_rx_pin(receive_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);       // Bits per sec
  
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
}

void sendCoup(int puissance) {
  digitalWrite(13, HIGH); 

  char msg1[13]= "sw_stk_";
      switch (modeTeinte){
        case 49: //feu
        msg1[7]= 'f'; msg1[8]= 'e';
        break;

        case 50: //poison
        msg1[7]= 'p'; msg1[8]= 'o';
        break;

        case 51: //berserk
        msg1[7]= 'b'; msg1[8]= 'e';
        break;
      }
    msg1[9] = char(puissance);
    vw_send((uint8_t *)msg1, 12); //strlen(msg) + x
  vw_wait_tx(); // Wait until the whole message is gone

  digitalWrite(13, LOW);
/*
  byte messageConv = byte(modeTeinte); //pour Bluetooth
  Serial.write(messageConv);           //pour Bluetooth
  */
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

mainx = mainx;
mainy = mainy;
mainz = mainz;

if (Serial.available()) {modeTeinte = Serial.read();}
/*
  if(Serial.read() > 0 && Serial.read() < 4) {modeTeinte = Serial.read();  }
}*/
  

if (nextRefresh < millis() ){
  for(int i=0 ; i<PIXNUMBER ; i++) {

      switch (modeTeinte){
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
/*
        Serial.print(red);   Serial.print(" ");
        Serial.print(green);   Serial.print(" ");
        Serial.print(blue);   Serial.println(" ");*/

  if (diffy > 50) {   //200 normalement
    //for(int i=0 ; i<PIXNUMBER ; i++) {     //flash coup
    //strip.setPixelColor(i, red+70, green+70, blue+70); }
    //nextRefresh = millis() + 100 ; //ou 200ms
    sendCoup(diffy);
  }
  /*
  float j = float(bright)/100;
  j = exp(j) * 20   ;
  j = j - 20;
  float squrt = sq(bright);*/
  
strip.show();
delay(10);
}

