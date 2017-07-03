#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <LIS3MDL.h>

LIS3MDL mag;

#define PIN 6 //pin number that you have connected your data pin to
#define PIXNUMBER 34 //number of neopixels you have connected

float bright ;
int coul;
int red;
int green;
int blue;



Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXNUMBER, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options
uint32_t noir = strip.Color(0, 50, 50);
uint32_t orange1 = strip.Color(226, 121, 35);
uint32_t nuance2 = strip.Color(158, 8, 148);
uint32_t nuance3 = strip.Color(74, 150, 12);
uint32_t nuance4 = strip.Color(226, 15, 30);



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

  for(int i=0 ; i<PIXNUMBER ; i++) {
//coul = randCoul(random(1, 5));
red  = random(210, 255);

//green= red - 170 ;
//green= green + random(0,60);

green= random(30,200);

/*
//blue = green - 90; 
blue = red - 210 ;
blue = blue + random(0,25);*/

blue= random(0, 30);

strip.setPixelColor(i, red, green, 0); 
//Serial.println(arf);
}
/*s
Serial.print(red);
Serial.print(" ");
Serial.print(green);
Serial.print(" ");
Serial.print(blue);
Serial.println(" ");*/

strip.setBrightness(10);
strip.show();
delay(100);

}












