#include <Adafruit_NeoPixel.h>

#define PIN 6 //pin number that you have connected your data pin to
#define PIXNUMBER 16 //number of neopixels you have connected

int velo;
int oldvelo;
int poten;
int sens;
float bright ;
int led;
int col1 ;
int col1b ;
int col2 ;
int col2b ;
int col3 ;
int col3b ;
float disp;




Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXNUMBER, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options

uint32_t vert = strip.Color(0, 50, 50);//in (0, 0, 0) type in intesities for each color

int rien(int val){
  for(val = 0; val<255 ; val++) {
    delay(20);
  }
  static int i = -i ;
  return val;
}

float fade(int add) {
static int val = 0;
static int dir = 1;
val = val + dir*add;
if (val >100) {
  val = 100; 
  dir *= -1;
  }
if (val <0) {
  val = 0; 
  dir *= -1;
  }
  return val ;
}

void setup() {
  
  strip.begin();
  strip.show();//sets all pixels to off state
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  Serial.begin(9600);
}


void loop() {
  
    int i = 0;                                        //dessine le fond 
    for(i; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 20, 80, 20);
     }


oldvelo = velo;
velo = analogRead(A1);
poten = analogRead(A2);
sens = analogRead(A3);

//velo = constrain(velo, 0, 255);
poten = map(poten, 95, 1020, 0, 100);


bright = fade(poten);
bright = constrain(bright, 0, 255);


if (bright < 1) {
  
  led = random(16);
  col1 = random(255);
  col2 = random(255);
  col3 = random(255);


}
Serial.print(velo);
Serial.print(" ");
Serial.println(sens);


disp = float(col1)*bright/100;
col1b = int(disp);

disp = float(col2)*bright/100;
col2b = int(disp);

disp = float(col3)*bright/100;
col3b = int(disp);

strip.setPixelColor(led, col1b, col2b, col3b);

  
strip.setBrightness(70);

strip.show();//show the pixels / colors of them after every cycle of loop -- like a refresh state
    delay(30);
}

/*
  for(static int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 20, 80, 20);
    Serial.println(i);
    if (i==strip.numPixels()) {i=0;}
    
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


    
