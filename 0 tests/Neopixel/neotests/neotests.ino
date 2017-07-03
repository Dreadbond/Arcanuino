#include <Adafruit_NeoPixel.h>

#define PIN 6 //pin number that you have connected your data pin to
#define PIXNUMBER 16 //number of neopixels you have connected

int velo;
int oldvelo;
int poten;
int i;
int o;
int val = 0;
int bright ;
int dir=1;


Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXNUMBER, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options

uint32_t vert = strip.Color(0, 50, 50);//in (0, 0, 0) type in intesities for each color

int rien(int val){
  for(val = 0; val<255 ; val++) {
    delay(20);
  }
  i = -i ;
  return val;
}




void setup() {
  
  strip.begin();
  strip.show();//sets all pixels to off state
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  Serial.begin(9600);
}


void loop() {

oldvelo = velo;
velo = analogRead(A1);
poten = analogRead(A2);
velo = constrain(velo, 0, 255);
poten = map(poten, 95, 1020, 0, 100);


fade(poten)

bright = bright + dir*poten;
if (bright >255) {
  bright = 255; 
  dir *= -1;
  }
if (bright <0) {
  bright = 0; 
  dir *= -1;
  }



Serial.print(bright);
Serial.print(" ");
Serial.println(poten);



bright = constrain(bright, 0, 255);
//strip.setPixelColor(1, vert);
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 20, 20, 20);
    //strip.show();
    //delay(100);
  }
strip.setBrightness(bright);
strip.show();//show the pixels / colors of them after every cycle of loop -- like a refresh state
    delay(30);

}

/*
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(100);
  }

if (i>= 16 ) {
    i=0;
    for(o=0; o<strip.numPixels(); o++) {
    strip.setPixelColor(o, color);
    strip.show();
    delay(100);
  }


   

/*
  strip.setPixelColor(poten, 0, 0, 0);
   strip.setPixelColor(1, 100, 100, 255); //set pixel collor: 1. is the pixel number, 2., 3., 4. are values from 0-255 for brightness of each color of the pixel

 strip.setPixelColor(6, color); //you can use a variable such as color that is defined in another section of the code.//

 uint32_t color = strip.getPixelColor(pixel);//get a color of a pixel for previous cycle

 uint16_t n = strip.numPixels(); //get a number of pixels previously-declared strip
strip.setBrightness(poten);//Set brightness of the whole strip from 0 - 255
*/


    
