#include <Adafruit_NeoPixel.h>
#include <Wire.h> // pour causer au magnétomètre
#include <VirtualWire.h> 


#define PIN 6 //pin number that you have connected your data pin to
#define PIXNUMBER 8 //number of neopixels you have connected

float bright = 10 ;
int coul;
int red;
int green;
int blue;
int vie = 10 ;
int mana = 0 ;
int ennVie = 0 ;
int ennMana = 0;
int sortCast= 0;

int oldvie = vie;
int oldmana = mana;
int oldennVie = ennVie;
int oldennMana = ennMana;

unsigned long tagTemps1 = 2000;
unsigned long offCast;

bool ledUpdate = LOW;


byte commande;
byte param;
byte mess3;
byte mess4;


Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXNUMBER, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options
uint32_t noir = strip.Color(0, 0, 0);
uint32_t orange1 = strip.Color(100, 20, 0);
uint32_t rouge = strip.Color(50, 0, 0);
uint32_t rose = strip.Color(50, 3, 3);
uint32_t bleu = strip.Color(10, 0, 50);
uint32_t vert = strip.Color(0, 100, 0);



void setup()
{
  delay(1000);
  Serial.begin(9600);
  Serial.println("hud-hub 0.7b, barre de vie renversee");

  pinMode(13, OUTPUT);
  
  strip.begin(); 
  strip.setBrightness(100);
  strip.show();//sets all pixels to off state
  
  vw_set_tx_pin(12);  //besoin ?
  vw_set_rx_pin(11);
  vw_set_ptt_pin(3);  //besoin ?
  vw_set_ptt_inverted(true); // Required for DR3100 //besoin ?
  vw_setup(2000); // initialisation de la librairie VirtualWire à 2000 bauds (note: je n'utilise pas la broche PTT)
  vw_rx_start();  // Activation de la partie réception de la librairie VirtualWire

  Wire.begin(); // pour causer au magnétomètre

  vie = 8 ; mana = 8 ; ennVie = 8 ; ennMana = 8;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////LOOP//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  
}

void loop(){

  uint8_t buf[VW_MAX_MESSAGE_LEN]; // Tableau qui va contenir le message reçu (de taille maximum VW_MAX_MESSAGE_LEN)
  uint8_t buflen = VW_MAX_MESSAGE_LEN; // Taille maximum de notre tableau


    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
    digitalWrite(13, HIGH); // Flash a light to show received good message
    int i;
    bool modeInt = LOW;

                int message = buf[i];  // traitement pour le Bluetooth
                byte messageConv = byte(message);
                Serial.write(messageConv);
            for (i = 0; i < buflen; i++)
            {
                
                int  recuInt  = buf[i];
                char recuChar = buf[i];
                /*
                if(buf == 84) {Serial.write("84");}
                if(buf == 85) {Serial.write("85");}
                if(buf == 83) {Serial.write("83");}*/

                if (modeInt == HIGH) {Serial.print(recuInt);}
            //    if (modeInt == LOW) {Serial.print(recuChar);}

                if (recuInt == 58) {modeInt = HIGH;}
                //Serial.print(buf[i], HEX);
                //Serial.print(' ');
            }
    Serial.println();
    digitalWrite(13, LOW);
    }



//byte commande;   //??

oldvie = vie;
oldmana = mana;
oldennVie = ennVie;
oldennMana = ennMana;


byte commande;   //??
byte param;   //??

/*
if (Serial.available() > 0 && commande != 0) {param = Serial.read(); }

    Serial.print(commande); Serial.print(" <cmd ");
    Serial.print(param); Serial.println(" <param");*/



/*if (Serial.available() > 0) {
commande = Serial.read(); 
param = Serial.read(); */

if (Serial.available() >= 2) //si 2 dans la file
{
    commande = Serial.read() ;
    param |= Serial.read();

  
  
  
  //for(int i=0 ; i<34 ; i++) {strip.setPixelColor (i, noir);}   //NOPE : pas tous en même temps, juste par barres
  


  
    Serial.print(commande); Serial.print(" <cmd ");   // à voir : le fait dans le bon ordre, mais param = 255 ???
    Serial.print(param); Serial.println(" <param");
  
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

  case 5:
  sortCast = param;
  break;
  
  }

  ledUpdate = HIGH;
 }


//Serial.print(commande); Serial.println(param);

vie = constrain(vie, 0, 8);
mana = constrain(mana, 0, 8);
ennVie = constrain(ennVie, 0, 8);
ennMana = constrain(ennMana, 0, 8);




if (ledUpdate == HIGH) { //sans ça, ça bugue
//if (Serial.available()) {

  if (mana != oldmana) {
  for(int i=0 ; i<8 ; i++) {strip.setPixelColor (i, noir);} // mise au noir localisée
  for(int i=0 ; i<mana ; i++) {                             //et couleurs
    int j = i;
    strip.setPixelColor(i, 0, 0, 50);
    strip.show();
    }
  }
  

  if (vie != oldvie) {
  for(int i=8 ; i<16 ; i++) {strip.setPixelColor (i, noir);}
  
  if (vie!=0) { for(int i=0 ; i<vie ; i++){
   int j = i+16-vie;
   strip.setPixelColor(j, rose);
   strip.show();
    }
   }
  }


  if (ennVie != oldennVie) {
  for(int i=16 ; i<24 ; i++) {strip.setPixelColor (i, noir);}
  for(int i=0 ; i<ennVie ; i++) {
    int j = i+16 ;
    strip.setPixelColor(j, rouge);
    strip.show();
    }
  }
  
  if (ennMana != oldennMana) {
  for(int i=24 ; i<32 ; i++) {strip.setPixelColor (i, noir);}
  for(int i=0 ; i<ennMana ; i++){
   int j = i+32-ennMana;
   strip.setPixelColor(j, bleu);
   strip.show();
   }
  }

  if (sortCast == 1) {    //feu
    strip.setPixelColor(32, orange1);
    strip.setPixelColor(33, orange1);
    strip.show(); 
    offCast = millis() + 1000;
    }
    
  if (sortCast == 2) {    //vie
    strip.setPixelColor(32, vert);
    strip.setPixelColor(33, vert);
    strip.show(); 
    offCast = millis() + 1000;
    }

  if (sortCast == 3) {    //bou
    strip.setPixelColor(32, 100, 100, 100);
    strip.setPixelColor(33, 100, 100, 100);
    strip.show(); 
    offCast = millis() + 1000;
    }

    if (millis() > offCast) {
    strip.setPixelColor(32, noir);
    strip.setPixelColor(33, noir);
    strip.show(); 
    }
    
ledUpdate = LOW;

}
    
 

/*
    if (tagTemps1 < millis()) {
    Serial.print(vie); Serial.print(" ");
    Serial.print(mana); Serial.print(" ");
    Serial.print(ennVie); Serial.print(" ");
    Serial.print(ennMana); Serial.println(" ");
    tagTemps1 = millis() + 2000 ;
    }*/

    
  }


