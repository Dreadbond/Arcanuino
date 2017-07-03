#include <Adafruit_NeoPixel.h>

#define PIN 7 //pin number that you have connected your data pin to
#define PIXNUMBER 11 //number of neopixels you have connected

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXNUMBER, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options

float bright ;
int coul;
int red;
int green;
int blue;

unsigned long timeTag ;
int intens = 70;
int message ;

void setup() {
Serial.begin(9600);

  strip.begin();
  strip.setBrightness(100);
  strip.show();//sets all pixels to off state
Serial.println("Test vibreur + Neopixel gant");
pinMode(6, OUTPUT);
}

void loop() {

if (Serial.available() >0) {message = Serial.read(); Serial.println(message);}
//if (intens > 255) {intens = 70;}
analogWrite(6, message);

for(int i=0 ; i<PIXNUMBER ; i++) {
    red  = random(210, 255);
    
    green= red - 160 ;
    green= green + random(0,150);
    
    blue = green + random(0, green);
    
    blue= random(0, 2);
    
    strip.setPixelColor(i, red, green, blue); 

    }
strip.show();

//intens++;
//delay(100);
}
