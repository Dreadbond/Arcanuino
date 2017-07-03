#include <Adafruit_NeoPixel.h>
#include <Wire.h> // pour causer au magnétomètre
#include <VirtualWire.h> 


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



int oldvie = vie;
int oldmana = mana;
int oldennVie = ennVie;
int oldennMana = ennMana;

unsigned long nextRefresh = 0;
unsigned long tagTemps1 = 2000;
//unsigned long offCast;

bool ledUpdate = LOW;
bool sortUpdate= LOW;

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
  strip.setBrightness(20);
  strip.show();//sets all pixels to off state
  
  vw_set_tx_pin(12);  //besoin ?
  vw_set_rx_pin(11);
  vw_set_ptt_pin(3);  //besoin ?
  vw_set_ptt_inverted(true); // Required for DR3100 //besoin ?
  vw_setup(2000); // initialisation de la librairie VirtualWire à 2000 bauds (note: je n'utilise pas la broche PTT)
  vw_rx_start();  // Activation de la partie réception de la librairie VirtualWire

  //Wire.begin(); // pour causer au magnétomètre

  vie = 8 ; mana = 8 ; ennVie = 8 ; ennMana = 8;
}
void offCast() {
    strip.setPixelColor(32, noir);
    strip.setPixelColor(33, noir);
    //strip.show(); 
    sortCast = 0;
    }

void feu_pattern() {
    int r = random(80, 120);
    int v = r - random(0, 60);
    strip.setPixelColor(32, r, v, 0);
    
    r = random(140, 220);
    v = r - random(0, 100);
    strip.setPixelColor(33, r, v, 0);
    
    //strip.show(); 
    }

void poison_pattern() {

    if(vS > 250) {vS = -250;}
    vS += random(2, 10);
    int j;
    if(vS <0) {j= vS * -1;} else {j= vS * 1;}
    j += random(0, 5);
    
    strip.setPixelColor(32, 0, j, 0);

    int k;
    k = j - 100;
    k +=  random(1, 5);
    if(k <0) {k= k * -1;} else {k= k * 1;}
    
    strip.setPixelColor(33, 0, k, 0);
    //strip.show(); 
    }

void bouclier_pattern() {

    if(vS > 150) {vS = -150;}
    vS += 5;
    int j;
    if(vS <0) {j= vS * -1;} else {j= vS * 1;}   //étage inversion de <0
    j += 100 ;
 
    strip.setPixelColor(32, j, j, j);
    strip.setPixelColor(33, j, j, j);
    //strip.show(); 
    }

void soins_pattern() {
    if(vS > 200) {vS = -200;}
    vS += 4;
    int j;
    if(vS <0) {j= vS * -1;} else {j= vS * 1;}
    j += 50;
    
    strip.setPixelColor(32, j, j, 0);

    int k;
    k = j - 100;
    if(k <0) {k= k * -1;} else {k= k * 1;}
    
    strip.setPixelColor(33, j, j, 0);
    //strip.show(); 
    //offCast = millis() + 1000;
    }
    
void drain_de_vie_pattern() {

    if(vS > 100) {vS = -100;}
    vS += 1;
    int j;
    if(vS <0) {j= vS * -1;} else {j= vS * 1;}   //étage inversion de <0
    j += 100 ;
    j += random(0, 100);
    bS = j - 70;
    
    strip.setPixelColor(32, 0, j, bS);
    strip.setPixelColor(33, 0, j, bS);
    //strip.show(); 
    //offCast = millis() + 1000;
    }
    
void super_punch_pattern() {
    //int ener;
    ener += 2;
    //ener += 1 ;
    if (ener > 400) {ener = 0; rS=0; vS=0; bS=0;}
    if (ener > 0)   {rS = ener;}
    if (ener > 75)  {vS = ener - 75;}
    if (ener > 120) {bS = ener - 120;}

        
    rS = constrain(rS, 0, 150);
    vS = constrain(vS, 0, 255);
    bS = constrain(bS, 0, 255);
    strip.setPixelColor(32, rS, vS, bS);
    strip.setPixelColor(33, rS, vS, bS);
    //strip.show(); 
    Serial.print(rS);Serial.print(" ");
    Serial.print(vS);Serial.print(" ");
    Serial.print(bS);Serial.println(" ");
}
    



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////LOOP//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop(){
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

            for (int i=0; i < qsdqsdLengh; i++) {
            if (qsdqsd.startsWith("to:br", i)) {Serial.print("To : brassard ");}
            
            if (qsdqsd.startsWith("ss:none", i)) {Serial.print("sort : rien"); sortCast = 48; }
            if (qsdqsd.startsWith("ss:feu", i)) {Serial.print("sort : feu"); sortCast = 49; }
            if (qsdqsd.startsWith("ss:poison", i)) {Serial.print("sort : poison"); sortCast = 50; }
            if (qsdqsd.startsWith("ss:bouclier", i)) {Serial.print("sort : bouclier"); sortCast = 51; }
            if (qsdqsd.startsWith("ss:soins", i)) {Serial.print("sort : soins"); sortCast = 52; }
            if (qsdqsd.startsWith("ss:drain", i)) {Serial.print("sort : drain"); sortCast = 53; }
            if (qsdqsd.startsWith("ss:punch", i)) {Serial.print("sort : punch"); sortCast = 54; }

            if (qsdqsd.startsWith("val_", i)) {Serial.print("inserer valeur");}
            
            }
        digitalWrite(13, false);
        Serial.println("");
        //ledUpdate = HIGH;
        nextRefresh = millis();
    } // fin boucle réception HF


/*
if (Serial.available() > 0 && commande != 0) {param = Serial.read(); }

    Serial.print(commande); Serial.print(" <cmd ");
    Serial.print(param); Serial.println(" <param");*/



/*if (Serial.available() > 0) {
commande = Serial.read(); 
param = Serial.read(); */


/* çui-là
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
 }*/


oldvie = vie;
oldmana = mana;
oldennVie = ennVie;
oldennMana = ennMana;

if (Serial.available() > 0) {  modeCom = Serial.read();}
  
    if (tagTemps1 < millis() && modeCom == 48) {
    tagTemps1 = millis() + 4000 ;
    vie = random(0, 8);
    mana = random(0, 8);
    ennVie = random(0, 8);
    ennMana = random(0, 8);
    ledUpdate = HIGH;
/*
    Serial.print(vie); Serial.print(" ");
    Serial.print(mana); Serial.print(" ");
    Serial.print(ennVie); Serial.print(" ");
    Serial.print(ennMana); Serial.println(" ");*/
    }



vie = constrain(vie, 0, 8);
mana = constrain(mana, 0, 8);
ennVie = constrain(ennVie, 0, 8);
ennMana = constrain(ennMana, 0, 8);


if (ledUpdate == HIGH) { //sans ça, ça bugue

  if (ennVie != oldennVie) {
      for(int i=0 ; i<8 ; i++) {strip.setPixelColor (i, noir);}   // mise au noir localisée
      for(int i=0 ; i<ennVie ; i++) {                              //et couleurs
        int j = i;
        strip.setPixelColor(i, 40, 10, 0);
        //strip.show();
        }
  }
  
  if (ennMana != oldennMana) {
      for(int i=8 ; i<16 ; i++) {strip.setPixelColor (i, noir);}
      for(int i=0 ; i<ennMana ; i++){
         int j = i+16-ennMana;
         strip.setPixelColor(j, bleu);
         //strip.show();
        }
  }

  if (mana != oldmana) {
      for(int i=16 ; i<24 ; i++) {strip.setPixelColor (i, noir);}
      for(int i=0 ; i<mana ; i++) {
          int j = i+16 ;
          strip.setPixelColor(j, 0, 0, 50);
          //strip.show();
        }
  }
  
  if (vie != oldvie) {
      for(int i=24 ; i<32 ; i++) {strip.setPixelColor (i, noir);}
      for(int i=0 ; i<vie ; i++){
          int j = i+32-vie;
          strip.setPixelColor(j, rouge);
          //strip.show();
          }
  }

ledUpdate = LOW;
}


//Serial.println(sortCast);

    if (nextRefresh < millis() ) {sortUpdate = HIGH; nextRefresh = millis() + 500; }
    //if (millis() > 2*nextRefresh) {offCast();}

    //if (sortUpdate == HIGH) {Serial.print("891871871");}
      if (sortCast == 49) {feu_pattern();}    //feu  
      if (sortCast == 50) {poison_pattern();}    //vie
      if (sortCast == 51) {bouclier_pattern();}    //bou
      if (sortCast == 52) {soins_pattern();}    //bou
      if (sortCast == 53) {drain_de_vie_pattern();}    //bou
      if (sortCast == 54) {super_punch_pattern();}    //bou
    
      if (sortCast == 48) {offCast();}//sortUpdate = LOW
      //sortUpdate = LOW;  }
      

      if (sortUpdate) {strip.show();Serial.print("kidiwe ");} //strip.show() bloque toute les réceptions. Il faut l'éteindre pour écouter. Conflit de lecture i2c ? même adresse ? même temps ?
      sortUpdate = LOW;
}




