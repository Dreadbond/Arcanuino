#include <Adafruit_NeoPixel.h>
#include <Wire.h> // pour causer au magnétomètre
#include <LIS3MDL.h>
#include <VirtualWire.h> 

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

unsigned long tagTemps1 ;


byte commande;
byte param;
byte mess3;
byte mess4;


Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXNUMBER, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options
uint32_t noir = strip.Color(0, 0, 0);
uint32_t orange1 = strip.Color(50, 1, 1);
uint32_t rouge = strip.Color(50, 0, 0);
uint32_t rose = strip.Color(50, 3, 3);
uint32_t bleu = strip.Color(10, 0, 50);
uint32_t vert = strip.Color(0, 50, 0);


void setup()
{
  Serial.begin(9600);
  Serial.println("hud-hub 0.3");

  pinMode(13, OUTPUT);
  
  strip.begin();
  strip.show();//sets all pixels to off state

  vw_set_rx_pin(11);
  vw_setup(2000); // initialisation de la librairie VirtualWire à 2000 bauds (note: je n'utilise pas la broche PTT)
  vw_rx_start();  // Activation de la partie réception de la librairie VirtualWire

  Wire.begin(); // pour causer au magnétomètre


  
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

byte commande;

if (Serial.available()) {

  for(int i=0 ; i<34 ; i++) {strip.setPixelColor (i, noir);}
  
  commande = Serial.read(); 
  param = Serial.read(); 
  
  switch (commande){
  case 1:
  vie = param;
  break;

  case 2:
  mana = param;
  break;

  case 3:
  ennVie = param;
  break;

  case 4:
  ennMana = param;
  break;
  }
 }

//Serial.print(commande); Serial.println(param);

vie = constrain(vie, 0, 8);
mana = constrain(mana, 0, 8);
ennVie = constrain(ennVie, 0, 8);
ennMana = constrain(ennMana, 0, 8);



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
    strip.setPixelColor(j, orange1);
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
delay(2000);//test
Serial.write(1); //test

  uint8_t buf[VW_MAX_MESSAGE_LEN]; // Tableau qui va contenir le message reçu (de taille maximum VW_MAX_MESSAGE_LEN)
  uint8_t buflen = VW_MAX_MESSAGE_LEN; // Taille maximum de notre tableau





    if (vw_get_message(buf, &buflen)) {// Non-blocking

    int i;
    digitalWrite(13, true); // 84 85 86
    
      for (i = 0; i < buflen; i++) {
      int message = buf[i];
      byte messageConv = byte(message);
      //Serial.println(messageConv);
      Serial.write(messageConv);
     
      }
    digitalWrite(13, false);

    }
}












