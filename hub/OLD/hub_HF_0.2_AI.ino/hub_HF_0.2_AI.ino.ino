/**
 * Exemple de code pour la bibliothèque Mirf – Serveur d'envoi de structure
 */
#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI
#include <stdlib.h>
#include <IRremote.h>

IRsend irsend;

String AEnvoyer ;   //Alarik par défaut
unsigned long tagGate = 0 ;

String joueurID = ":111111" ;
//String objetID = "ohub1"; //tag unique de l'objet
String cibleID = ":vide" ;

typedef struct { //à dégager
  char commande ;
  int  valeur ;
} envoiNeopixel;

typedef struct { //à dégager
  char objet ;
  char action; //char action;
  int valeur;
} MaStructure;

char *IDobjet = "nrf01" ; //hub
char *toIDobjetSlot2 = "nrf02" ;  //flingue
char *toIDobjetSlot3 = "nrf03" ;  //brassard
char *toIDobjetSlot4 = "nrf04" ;
char *toIDobjetSlot5 = "nrf05" ;
char *toIDobjetSlot6 = "nrf06" ;


int vieSelf ;
int wizarSelf ;
int vieCible ;
int wizarCible ;

bool gachetteToken;

char objet ;
char action ;
int valeur ;

bool sendTicket = LOW ;


bool debug_mode = HIGH;

void brassardFBtest() {

}

void gachetteFB() {
      int messTest = 1;
      Mirf.setTADDR((byte *) toIDobjetSlot2);//IDobjet);  // "nrf01"); // Adresse de transmission
      Mirf.send((byte*) &messTest); // On envoie le message (Strings) et strucutre
      while(Mirf.isSending()); // On attend la fin de l'envoi
}

void cibleTrueFB() {
      int messTest = 2;
      Mirf.setTADDR((byte *) toIDobjetSlot2);//IDobjet);  // "nrf01"); // Adresse de transmission
      Mirf.send((byte*) &messTest); // On envoie le message (Strings) et strucutre
      while(Mirf.isSending()); // On attend la fin de l'envoi
}

void cibleFalseFB() {
      int messTest = 3;
      Mirf.setTADDR((byte *) toIDobjetSlot2);//IDobjet);  // "nrf01"); // Adresse de transmission
      Mirf.send((byte*) &messTest); // On envoie le message (Strings) et strucutre
      while(Mirf.isSending()); // On attend la fin de l'envoi
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////SETUP///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);

  Mirf.cePin = 9; // Broche CE sur D9
  Mirf.csnPin = 10; // Broche CSN sur D10
  Mirf.spi = &MirfHardwareSpi; // On veut utiliser le port SPI hardware
  Mirf.init(); // Initialise la bibliothèque

  Mirf.channel = 1; // Choix du canal de communication (128 canaux disponibles, de 0 à 127)
  Mirf.payload = sizeof(MaStructure); // Taille d'un message (maximum 32 octets)
  Mirf.config(); // Sauvegarde la configuration dans le module radio

  //Mirf.setTADDR((byte *) toIDobjet);//IDobjet);  // "nrf01"); // Adresse de transmission
  Mirf.setRADDR((byte *) IDobjet);//toIDobjet); // "nrf02");Adresse de réception

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  Serial.println("Hub HF 0.2 version App Inventor"); 
}






void loop() {
  /*Réception message :
   * 1 char (voire String) objet qui émet
   * 2 char (voire String) : kessiveutnousdire : c cible, g gachette
   * 3 int (voire String) : valeur de ce qu'il dit
   */
///////////////////////////////////Réception messages d'objets (nr24L01)//////////////////////////////
  MaStructure message;
  envoiNeopixel messNeo;
  
  if(Mirf.dataReady()){
    Mirf.getData((byte*) &message); // Réception du paquet

    Serial.print("objet=");
    Serial.print(message.objet);  
    Serial.print(" action="); // Affiche le message
    Serial.print(message.action);
    Serial.print(" valeur=");
    Serial.println(message.valeur);  
    
    sendTicket = HIGH ;
  }



///////////////////////////////////Envoi vers bluetooth///////////////////////////////////////////////
objet  =message.objet;
action =message.action;
valeur =message.valeur;

valeur = constrain(valeur, 0, 100);

//à dégager : cheatCible
     if (message.action == 'c' && message.valeur==1) {cibleID = ":123456";}
else if (message.action == 'c' && message.valeur==2) {cibleID = ":986543";}
else if (message.action == 'c' && message.valeur==3) {cibleID = ":184675";}
else if (message.action == 'c' && message.valeur==4) {cibleID = ":111111";}
else if (message.action == 'c' && message.valeur==0) {cibleID = ":vide";}


if (sendTicket) {
  //Serial.println("{");
  //Serial.print("\"fromId\": \""); Serial.print(joueurID); Serial.println("\",");
  Serial.print("\"toId\": \""); Serial.print(cibleID); Serial.println("\",");
  if (cibleID != ":vide") {cibleTrueFB();}
  else {cibleFalseFB();}
  
    switch (objet){
        case 'f' : //flingue
          switch (action) {
          case 'g' :        //gachette
          Serial.print("\"rawPiercingDamage\": "); Serial.print(100); Serial.println();
          
          //gachetteFB();
          gachetteToken = HIGH;
          break;

          case 'r' :        //recharge
          Serial.print("\"actionReload\": "); Serial.print(100); Serial.println();
          
          break;
          }
        break;

        case 'g' : //gant
          switch (action) {
          case 'f' : //feu
          Serial.print("\"rawFireDamage\": "); Serial.print(100); Serial.println();
          
          break;

          case 's' : //soins
          Serial.print("\"rawHeal\": "); Serial.print(100); Serial.println();
          
          break;

          case 'd' : //drain
          Serial.print("\"rawVampire\": "); Serial.print(100); Serial.println();
          
          break;
          }
        break;
        
        case 'h' : //grimoire
          switch (action) {
          case 'f' : //feu
          Serial.print("\"rawFireDamage\": "); Serial.print(100); Serial.println();
          
          break;

          case 's' : //soins
          Serial.print("\"rawHeal\": "); Serial.print(100); Serial.println();
          
          break;

          case 'b' : //drain
          Serial.print("\"rawVampire\": "); Serial.print(100); Serial.println();
          
          break;
          }
        break;

        case 'e' : //épée
          switch (action) {
          case 'h' : //touche
          Serial.print("\"swordDamage\": "); Serial.print(valeur); Serial.println();
          
          break;
            
          case 'f' : //feu
          Serial.print("\"fireMode\": "); Serial.print(100); Serial.println();
          
          break;

          case 'p' : //poison
          Serial.print("\"poisonMode\": "); Serial.print(100); Serial.println();
          
          break;

          case 'b' : //berserk
          Serial.print("\"berserkMode\": "); Serial.print(100); Serial.println();
          
          break;
          }
        break;
    
    }
  Serial.println("<");
  sendTicket = LOW ;
}
//AEnvoyer = joueurID;
AEnvoyer = ":123456";
/*
if (digitalRead(4) == LOW) {AEnvoyer = ":123456";}  //Alarik
if (digitalRead(5) == LOW) {AEnvoyer = ":986543";}  //Rhea
if (digitalRead(6) == LOW) {AEnvoyer = ":184675";}  //Dessloch*/
  if (tagGate < millis()) {
    for (int i = 0; i < AEnvoyer.length(); i++){
      irsend.sendRC5(AEnvoyer.charAt(i), 12); 
      delay(15);
    }
    tagGate = millis() + 100 ; //200 à la base
  }

if (gachetteToken) {gachetteFB();gachetteToken = LOW;}


///////////////////////////////////Tag infrarouge/////////////////////////////////////////////////////

}
/*
{
    "fromId": ":111111",
    "toId": ":123456",
    "rawPiercingDamage": 100
}
*/

/*
if (fromPlayer != "0" || toPlayer != "0" || objet != "0" || action != "0") {
  Serial.println("{");
  Serial.print("\"action\": \"");
  Serial.print(action);
  Serial.println("\",");
  Serial.print("\"objet\": [");
  Serial.print(objet);
  Serial.println("],");
  Serial.print("\"from\": \"");
  Serial.print(fromPlayer);
  Serial.println("\",");
  Serial.print("\"toIds\": [");
  Serial.print(toPlayer);
  Serial.println("],");
  Serial.print("\"data\": {\"damage\" : ");
  Serial.print(action);
    if (heure != "0") {
        Serial.print("\"hitbox\": ");
        Serial.println(heure);
        }
  Serial.println("}");
  Serial.println("}");
  zero();
  }*/








  

