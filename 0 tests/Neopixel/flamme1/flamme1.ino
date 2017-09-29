#include <Adafruit_NeoPixel.h>

#define PIN 5 //pin number that you have connected your data pin to
#define PIXNUMBER 16 //number of neopixels you have connected

float bright ;
int coul;
int red;
int green;
int blue;



Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXNUMBER, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options



void setup()
{
  strip.begin();
  strip.setBrightness(255);
  strip.show();//sets all pixels to off state
  
  Serial.begin(9600);

  Serial.println("Test Neopixel : flammes");
}

void loop(){

  for(int i=0 ; i<PIXNUMBER ; i++) {
red  = random(180, 255);

green= red - 160 ;

blue= 0;

strip.setPixelColor(i, red, green, blue); 

}


strip.show();
delay(100);

}












