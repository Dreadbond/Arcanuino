#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <LIS3MDL.h>

LIS3MDL mag;

#define PIN 6 //pin number that you have connected your data pin to
#define PIXNUMBER 34 //number of neopixels you have connected

float bright = 10 ;
int coul;
int red;
int green;
int blue;



Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXNUMBER, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options
uint32_t noir = strip.Color(0, 0, 0);
uint32_t orange1 = strip.Color(226, 140, 0);
uint32_t rouge = strip.Color(255, 20, 20);
uint32_t bleu = strip.Color(20, 20, 255);
uint32_t vert = strip.Color(0, 255, 0);


void setup()
{
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  
  strip.begin();
  strip.show();//sets all pixels to off state
  
  Serial.begin(9600);
  Wire.begin();

  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
}

void loop(){

  for(int i=0 ; i<34 ; i++) {
if (i>=0 && i<=7) {strip.setPixelColor(i, bleu);}
if (i>=8 && i<=15) {strip.setPixelColor(i, rouge);}
if (i>=16 && i<=23) {strip.setPixelColor(i, rouge);}
if (i>=24 && i<=31) {strip.setPixelColor(i, bleu);}
if (i==32) {strip.setPixelColor(i, vert);}
if (i==33) {strip.setPixelColor(i, vert);}

//Serial.println(arf);
}
/*
Serial.print(red);
Serial.print(" ");
Serial.print(green);
Serial.print(" ");
Serial.print(blue);
Serial.println(" ");*/

strip.setBrightness(5);
strip.show();
delay(100);

}












