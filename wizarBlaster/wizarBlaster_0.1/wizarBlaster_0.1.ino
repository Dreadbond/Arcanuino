#include <IRremote.h>

#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI

//Neopixel
#include <Adafruit_NeoPixel.h>
#define PIN 6 //pin number that you have connected your data pin to
#define PIXNUMBER 10 //number of neopixels you have connected


//String idJoueur = "111111" ; //osef
char *IDobjet = "nrf05";
char *toIDobjet = "nrf01" ;     //ID de l'objet qui est sensé recevoir
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXNUMBER, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options
uint32_t orange1 = strip.Color(226, 121, 35);
typedef struct {
  char objectStru = 'w' ;
  char commande;
  int valeur;
} actionStruct;


//traitement message entré
bool write_message = LOW ;      //si détecté un ":", il concatène la suite
char messActual[10] = " ";
String strMessActual ;          // pour conversion 
int tempsBuffer ;
int posCharRcv ;
int lgMess = 7 ;                //taille du message (trouver un standard)

//entité ciblée (tag)
String cible ;                     //cible actuelle
String oldCible ;                  //cible avant



//bool cibleConfirmee = LOW ;

unsigned long faireMessageCible ;   //uniquement pour réception char
//unsigned long gateCible ;         //pour la cible en elle-même
unsigned long resetCible ;          //décision de perdre la cible

int debug = 0 ;

//infrarouge
int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

char modeFeu = 'p' ;

//gâchette
bool mireCible ;
bool panFlag = HIGH ;
unsigned long debounceGachette ;

int messRCVhF ;




void raz() {
    posCharRcv = 0 ;  //retour chariot
    cible = "vide" ;
    strMessActual = "arf" ;      //strMessActual.remove(0);
    for (int i=0 ; i<lgMess; i++) {messActual[i] = '\0' ;}
    write_message = LOW;
}




typedef struct {      //pas utilisé
  char objectStru = 'w' ;
  char commande;
  byte cible[6];
} actionCibleStruct;


//////////////////////////////////Blaster
bool tokenFire ;
void fireLedFB(){
  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static int red ;
  static int green ;
  static int blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 2500 ;
  static int TC2 = 2550 ;
  static int TC3 = 2570 ;
  static int TC4 ;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;
  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);
  
  if (chrono>TC0 && chrono<TC1) {
    for(int i=0; i<3 ; i++) {
      red  = random(210, 255);
      green= red - 160 ;
      green= green + random(0,100);

      bright = float(chrono)/TC1;
      strip.setPixelColor(i, red*bright, green*bright, 0); 
      strip.show();
    }
  }
  if (chrono>TC1 && chrono<TC2){
    for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
      for(int i=3; i<PIXNUMBER ; i++) {
      red  = 70 + (i*9) ;
      green= i*3 ;
      blue = 0;
  
      red=constrain(red, 0, 255);
      strip.setPixelColor(i, red, green, blue); 
      strip.show();
      }
  }
  if (chrono>TC2 && chrono<TC3){
    //for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
    strip.setPixelColor(9, 200, 200, 200); 
    strip.show();
  }
  if (chrono>TC3 ) {
    for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
  tokenFire=LOW;
  effetStopFlag=HIGH;
  }
}

//////////////////////////////////Plasma
bool tokenPlasma ;
void plasmaLedFB(){
  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static int red ;
  static int green ;
  static int blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 40 ;
  static int TC2 = 50 ;
  static int TC3 = 70 ;
  static int TC4 = 80 ;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;

  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);
  
  if (chrono>TC0 && chrono<TC1) {
    for(int i=0; i<4 ; i++) {
      green= random(100, 180);
      red  = 0;
      blue = 10;
      
      bright = 0.25;
      strip.setPixelColor(i, red*bright, green*bright, blue*bright); 
      strip.show();
    }
  }
  if (chrono>TC1 && chrono<TC2){
      for(int i=4; i<7 ; i++) {
      green= random(150, 210);
      red  = 0;
      blue = random(50, 100);;
      
      bright = 0.5;
      strip.setPixelColor(i, red*bright, green*bright, blue*bright); 
      strip.show();
      }
  }
  if (chrono>TC1 && chrono<TC2){
      for(int i=7; i<PIXNUMBER ; i++) {
      green= random(210, 255);
      red  = 100;
      blue = 100;
      
      bright = 1;
      strip.setPixelColor(i, red*bright, green*bright, blue*bright); 
      strip.show();
      }
  }
  if (chrono>TC2 && chrono<TC3){
    for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
    strip.setPixelColor(9, 200, 200, 200); 
    strip.show();
  }
  if (chrono>TC3 ) {
    for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
  tokenFire=LOW;
  effetStopFlag=HIGH;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Setup////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  strip.begin();
  strip.setBrightness(255);
  strip.show();//sets all pixels to off state
  
  Mirf.cePin = 9; // Broche CE sur D9
  Mirf.csnPin = 10; // Broche CSN sur D10
  Mirf.spi = &MirfHardwareSpi; // On veut utiliser le port SPI hardware
  Mirf.init(); // Initialise la bibliothèque

  Mirf.channel = 1; // Choix du canal de communication (128 canaux disponibles, de 0 à 127)
  Mirf.payload = sizeof(actionStruct); //32; // Taille d'un message (maximum 32 octets)
  Mirf.config(); // Sauvegarde la configuration dans le module radio

  Mirf.setTADDR((byte *) toIDobjet);//toIDobjet); "nrf02"); // Adresse de transmission
  Mirf.setRADDR((byte *) IDobjet);//IDobjet); //"nrf01"); // Adresse de réception
  
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(2, INPUT_PULLUP);
  Serial.println("WizarBlaster 0.1");
}




//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Loop/////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
  //tokenFire = HIGH;
actionStruct messageStru;
actionCibleStruct cibleStruct;


if (Serial.available() > 0) {debug = Serial.read();}
//if (debug == 1) {Serial.println("debug");}





oldCible = cible ;
//////////////////////////////////////////Traitement du message///////////////////////////////////////

//irrecv.resume();
//détection Ir : faisage de message
  if (irrecv.decode(&results)) {
     //Serial.println(char(results.value));
     irrecv.resume(); //à garder ici (???)
     if (char(results.value) == ':') {write_message = HIGH;}
        if (write_message) {
        messActual[posCharRcv] = char(results.value) ;  //concaténation
        strMessActual = String(messActual) ;            //conversion en String
        irrecv.resume();
        //Serial.print(messActual[posCharRcv]);
        posCharRcv++ ;
        resetCible = millis() + 150;                    //délai avant perte de cible 300 à la base. 200 ensuite
        faireMessageCible = millis() + 50 ;             //délai avant de confirmer message
        //Serial.print(posCharRcv); Serial.print(" ");
        //Serial.print(strMessActual); Serial.print(" ");
        //Serial.println(strMessActual.length());
        }
    }


//message trop long : erreur et vide
if (strMessActual.length() > lgMess) {   
  raz();
  write_message = LOW;
}


//message valide
if (faireMessageCible < millis() || strMessActual.length() == lgMess ) {
    if (strMessActual.length() == lgMess && strMessActual.charAt(0) == ':' ) {
    posCharRcv = 0 ;  //retour chariot
    cible = String(messActual) ;

      for (int i=1 ; i<lgMess; i++) {
        if (isDigit(messActual[i])) {}
        else {cible = "vide";} //
      }
    
    strMessActual.remove(0);
    for (int i=0 ; i<lgMess; i++) {messActual[i] = '\0' ;}
    write_message = LOW;
    //Serial.println("Ok");
    }
  }


//timeout ou message trop long: grosse galère, je compte sur le || strMessActual.length() == lgMess pour éviter ça
if (resetCible < millis() || strMessActual.length() > lgMess ) {   
  raz();
  //cible = "vide"; 
}




////////////////////////////////////Envoi action a : tir
if (digitalRead(2) == LOW && panFlag == HIGH && millis() > debounceGachette) {
      tokenFire=HIGH;
      
      
      messageStru.commande = 'g' ;//Serial.read(); //g : gachette
      messageStru.valeur = 1 ;//Serial.parseInt(); //valeur : 1, ok. 2, non. ...
      
      Mirf.send((byte*) &messageStru); // On envoie le message (Strings) et strucutre
      while(Mirf.isSending()); // On attend la fin de l'envoi
 
  panFlag = LOW ;
  debounceGachette = millis() + 20;
  }

if (tokenFire) {
  switch (modeFeu) {
    case 'b' :
    fireLedFB();
    break ;

    case 'p' :
    plasmaLedFB();
    break ;
  }
}


////////////////////////////////////Envoi action c : cible (vise)
if (cible != oldCible) {
    for (int i=0; i<6; i++) {
        cibleStruct.cible[i] = cible[i] ;
        cibleStruct.cible[i+1] = '\0';
        //Serial.println(cibleStruct.cible[i]);
        //Serial.println(cibleStruct.cible[i+1]);
        }
      
      int cheatCible ;
           if (cible== ":123456")  {  cheatCible = 1 ;}
      else if (cible== ":986543")  {  cheatCible = 2 ;}
      else if (cible== ":184675")  {  cheatCible = 3 ;}
      else if (cible== ":111111")  {  cheatCible = 4 ;}
      else if (cible== ":vide")    {  cheatCible = 0 ;}
      
      messageStru.commande = 'c' ;//Serial.read(); //c : cible
      messageStru.valeur = cheatCible ;//Serial.parseInt(); //valeur : 1, ok. 2, non. ...
      
      Mirf.send((byte*) &messageStru); // On envoie le message (Strings) et strucutre
      while(Mirf.isSending()); // On attend la fin de l'envoi
}





/////////////////////////////////////Réception HF
  if(Mirf.dataReady()){
    Serial.print("J'ai ! : ");
    
    Mirf.getData((byte*) &messRCVhF); // Réception du paquet
    Serial.println(messRCVhF);
  }

     if (messRCVhF == 2) { mireCible = HIGH;       }
     if (messRCVhF == 3) { mireCible = LOW;       }


if (mireCible) {  digitalWrite(A2, HIGH);}
else{digitalWrite(A2, LOW);}


//on libère la gachette pour le prochain loop
if (digitalRead(A1) == LOW && millis() > debounceGachette)
  {
  panFlag = HIGH ;
  debounceGachette = millis() + 50;
  }

    
}

/*
{
    "fromId": ":111111",
    "toId": ":123456",
    "rawPiercingDamage": 100
}

*/
