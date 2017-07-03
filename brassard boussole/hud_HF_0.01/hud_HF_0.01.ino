#include <Adafruit_NeoPixel.h>
#include <Wire.h> // pour causer au magnétomètre

#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI

#include <stdlib.h>

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
int sortCast;
int modeCom ;
char modeComChar ;
int ener=1;
int val ; //valeur générale, free to use

int rS ;
int vS ;
int bS ;

typedef struct { //à dégager
  char commande ;
  int  valeur ;
} MaStructure;

char *IDobjet = "nrf02" ; //brassard
char *toIDobjet = "nrf01" ;  //hub


int oldvie = vie;
int oldmana = mana;
int oldennVie = ennVie;
int oldennMana = ennMana;

unsigned long nextRefresh = 0;
unsigned long tagTemps1 = 2000;
unsigned long offCast;

bool ledVieUpdate = LOW;
bool sortUpdate= LOW;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXNUMBER, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options
uint32_t noir = strip.Color(0, 0, 0);
uint32_t orange1 = strip.Color(100, 20, 0);
uint32_t rouge = strip.Color(50, 0, 0);
uint32_t rose = strip.Color(50, 3, 3);
uint32_t bleu = strip.Color(10, 0, 50);
uint32_t vert = strip.Color(0, 100, 0);
uint32_t blanc = strip.Color(80, 80, 80);


void setup()
{
  delay(1000);
  Serial.begin(9600);
  Serial.println("hud-hub HF 0.01");

  
  strip.begin(); 
  strip.setBrightness(50);
  strip.show();//sets all pixels to off state
  
  //Wire.begin(); // pour causer au magnétomètre
  Mirf.cePin = 9; // Broche CE sur D9
  Mirf.csnPin = 10; // Broche CSN sur D10
  Mirf.spi = &MirfHardwareSpi; // On veut utiliser le port SPI hardware
  Mirf.init(); // Initialise la bibliothèque

  Mirf.channel = 1; // Choix du canal de communication (128 canaux disponibles, de 0 à 127)
  Mirf.payload = sizeof(MaStructure); // Taille d'un message (maximum 32 octets)
  Mirf.config(); // Sauvegarde la configuration dans le module radio

  Mirf.setTADDR((byte *) toIDobjet);//toIDobjet); "nrf02"); // Adresse de transmission
  Mirf.setRADDR((byte *) IDobjet);//IDobjet); //"nrf01"); // Adresse de réception : IDobjet

  vie = 8 ; mana = 8 ; ennVie = 8 ; ennMana = 8;
}
void none_pattern() {
    strip.setPixelColor(32, noir);
    strip.setPixelColor(33, noir);
    sortCast = 0;
    }

void feu_pattern() {
    strip.setPixelColor(32, 120, 80, 0);
    strip.setPixelColor(33, 110, 100, 0);
    }

void poison_pattern() {
    strip.setPixelColor(32, 0, 100, 0);
    strip.setPixelColor(33, 0, 70, 0);
    }

void bouclier_pattern() {
    //int j = 80;
    strip.setPixelColor(32, blanc);
    strip.setPixelColor(33, blanc);
    }

void soins_pattern() {
    int j= 100;
    strip.setPixelColor(32, j, j, 0);
    strip.setPixelColor(33, j, j, 0);
    }
    
void drain_de_vie_pattern() {
    strip.setPixelColor(32, 0, 70, 80);
    strip.setPixelColor(33, 0, 70, 80);
    }
    
void super_punch_pattern() {
    strip.setPixelColor(32, 30, 70, 100);
    strip.setPixelColor(33, 30, 70, 100);
}

void rouge_pattern() {
    strip.setPixelColor(32, 80, 0, 0);
    strip.setPixelColor(33, 80, 0, 0);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////LOOP//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop(){
  //envoiNeopixel messNeo;
    MaStructure message;
  
oldvie = vie;
oldmana = mana;
oldennVie = ennVie;
oldennMana = ennMana;



  if(Mirf.dataReady()){
    Serial.print("J'ai ! : ");

    Mirf.getData((byte*) &message); // Réception du paquet
    
    Serial.print("objet=");
    Serial.print(message.commande);  
    Serial.print(" valeur=");
    Serial.println(message.valeur);  
    
    //sendTicket = HIGH ;
  }

}

/*

if (Serial.available() > 0) {  modeCom = Serial.read();}
  
    if (tagTemps1 < millis() && modeCom == 48) {
    tagTemps1 = millis() + 4000 ;
    vie = random(0, 8);
    mana = random(0, 8);
    ennVie = random(0, 8);
    ennMana = random(0, 8);
    ledVieUpdate = HIGH;
    }

/*

vie = constrain(vie, 0, 8);
mana = constrain(mana, 0, 8);
ennVie = constrain(ennVie, 0, 8);
ennMana = constrain(ennMana, 0, 8);


if (ledVieUpdate == HIGH) { //sans ça, ça bugue

  //if (ennVie != oldennVie) {
      for(int i=0 ; i<8 ; i++) {strip.setPixelColor (i, noir);}   // mise au noir localisée
      for(int i=0 ; i<ennVie ; i++) {                              //et couleurs
        int j = i;
        strip.setPixelColor(i, 40, 10, 0);
        //strip.show();
        }
  //}
  
  //if (ennMana != oldennMana) {
      for(int i=8 ; i<16 ; i++) {strip.setPixelColor (i, noir);}
      for(int i=0 ; i<ennMana ; i++){
         int j = i+16-ennMana;
         strip.setPixelColor(j, bleu);
         //strip.show();
        }
  //}

  //if (mana != oldmana) {
      for(int i=16 ; i<24 ; i++) {strip.setPixelColor (i, noir);}
      for(int i=0 ; i<mana ; i++) {
          int j = i+16 ;
          strip.setPixelColor(j, 0, 0, 50);
          //strip.show();
        }
  //}
  
  //if (vie != oldvie) {
      for(int i=24 ; i<32 ; i++) {strip.setPixelColor (i, noir);}
      for(int i=0 ; i<vie ; i++){
          int j = i+32-vie;
          strip.setPixelColor(j, rouge);
          //strip.show();
          }
  //}

ledVieUpdate = LOW;
}



      if (sortCast == 49) {feu_pattern();}
      if (sortCast == 50) {poison_pattern();}
      if (sortCast == 51) {bouclier_pattern();}
      if (sortCast == 52) {soins_pattern();}
      if (sortCast == 53) {drain_de_vie_pattern();}
      if (sortCast == 54) {super_punch_pattern();}
      if (sortCast == 55) {rouge_pattern();}
    
      if (sortCast == 48) {none_pattern();}

      
      
      if (sortUpdate) {strip.show(); sortUpdate = LOW; offCast = millis() + 2500;} //strip.show() bloque toute les réceptions. Il faut l'éteindre pour écouter. Conflit de lecture i2c ? même adresse ? même temps ? Trop de consommation électrique
      if (millis() > offCast) {
        sortCast = 48; 
        //strip.show();
        }



        
}
*/

  /* RIP
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {

    //int i; à dégager ?
    char messActual[buflen] = " ";
    digitalWrite(13, true);
              for (int i = 0; i < buflen; i++) //faisage du message à partir des lettres
                {
                char lettre = char(buf[i]);
                messActual[i] = lettre ;
                }
            String qsdqsd = String(messActual);
            int qsdqsdLengh = qsdqsd.length();
            Serial.println(qsdqsd);
            bool lireMessage = LOW ;

            for (int i=0; i < qsdqsdLengh; i++) {
            if (qsdqsd.startsWith("to:br", i)) {lireMessage = HIGH; Serial.print("To : brassard ");} 
            }

            if (lireMessage) {
                for (int i=0; i < qsdqsdLengh; i++) {
                if (qsdqsd.startsWith("ss:none", i)) {Serial.print("sort : rien"); sortCast = 48; }
                if (qsdqsd.startsWith("ss:feu", i)) {Serial.print("sort : feu"); sortCast = 49; }
                if (qsdqsd.startsWith("ss:poison", i)) {Serial.print("sort : poison"); sortCast = 50; }
                if (qsdqsd.startsWith("ss:bouclier", i)) {Serial.print("sort : bouclier"); sortCast = 51; }
                if (qsdqsd.startsWith("ss:soins", i)) {Serial.print("sort : soins"); sortCast = 52; }
                if (qsdqsd.startsWith("ss:drain", i)) {Serial.print("sort : drain"); sortCast = 53; }
                if (qsdqsd.startsWith("ss:punch", i)) {Serial.print("sort : punch"); sortCast = 54; }
                if (qsdqsd.startsWith("ss:rouge", i)) {Serial.print("sort : rouge"); sortCast = 55; }
    
                if (qsdqsd.startsWith("val_", i)) {Serial.print("inserer valeur");}
                
                if (qsdqsd.startsWith("vie_", i)) {vie = int(messActual[10]) - 48;}
                if (qsdqsd.startsWith("mana_", i)) {mana = char(messActual[11]) - 48;}
                if (qsdqsd.startsWith("ennVie", i)) {ennVie = byte(messActual[13]) - 48;}
                if (qsdqsd.startsWith("ennMana", i)) {ennMana = messActual[14] - 48;}
                }
            }
        digitalWrite(13, false);
        Serial.println("");
        sortUpdate = HIGH;
        ledVieUpdate = HIGH;
        } // fin boucle réception HF
        */

