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
int vie = 10 ;
int mana = 0 ;
int ennVie = 0 ;
int ennMana = 0;



Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXNUMBER, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options
uint32_t noir = strip.Color(0, 0, 0);
uint32_t orange1 = strip.Color(49, 23, 0);
uint32_t rouge = strip.Color(50, 0, 0);
uint32_t rose = strip.Color(50, 3, 3);
uint32_t bleu = strip.Color(10, 2, 50);
uint32_t vert = strip.Color(0, 40, 10);


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
/*
  for(int i=0 ; i<34 ; i++) {
if (i>=0 && i<=7) {strip.setPixelColor(i, bleu);}
if (i>=8 && i<=15) {strip.setPixelColor(i, rouge);}
if (i>=16 && i<=23) {strip.setPixelColor(i, rouge);}
if (i>=24 && i<=31) {strip.setPixelColor(i, bleu);}
if (i==32) {strip.setPixelColor(i, vert);}
if (i==33) {strip.setPixelColor(i, vert);}

//Serial.println(arf);
}*/

vie = constrain(vie, 0, 8);
mana = constrain(mana, 0, 8);
ennVie = constrain(ennVie, 0, 8);
ennMana = constrain(ennMana, 0, 8);

  for(int i=0 ; i<34 ; i++) {strip.setPixelColor (i, noir);}

if (mana >= 0) {
  for(int i=0 ; i<mana ; i++) {
    int j = i;
    strip.setPixelColor(i, vert);
    strip.show();
    }
  }
  

if (vie >= 0) {
  for(int i=0 ; i<vie ; i++){
   int j = i+16-vie;
   strip.setPixelColor(j, rose);
   strip.show();
   }
  }


if (ennVie >= 0) {
  for(int i=0 ; i<ennVie ; i++) {
    int j = i+16 ;
    strip.setPixelColor(j, rouge);
    strip.show();
    }
  }
  
if (ennMana >= 0) {
  for(int i=0 ; i<ennMana ; i++){
   int j = i+32-ennMana;
   strip.setPixelColor(j, bleu);
   strip.show();
   }
  }

/*
Serial.print(red);
Serial.print(" ");
Serial.print(green);
Serial.print(" ");
Serial.print(blue);
Serial.println(" ");*/

strip.setBrightness(80);
strip.show();
delay(100);

if (Serial.available()) {int aze = Serial.read(); Serial.println(aze);}

delay(5000);
vie = random (0, 9);
mana = random (0, 9);
ennVie = random (0, 9);
ennMana = random (0, 9);

Serial.print(vie);
Serial.print(" ");
Serial.print(mana);
Serial.print(" ");
Serial.print(ennVie);
Serial.print(" ");
Serial.print(ennMana);
Serial.println(" ");

}












