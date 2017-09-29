#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI
char *IDobjet = "nrf08";
char *toIDobjet = "nrf01" ;     //ID de l'objet qui est sensé recevoir

typedef struct {
  char objectStru = 'h' ;
  char commande;
  int valeur;
} actionStruct;

char commande ;
int valeur ;
bool sendToken ;

unsigned long nextSend = 0;

int bouton_1;
int bouton_2;
int bouton_3;

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Setup////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Mirf.cePin = 9; // Broche CE sur D9
  Mirf.csnPin = 10; // Broche CSN sur D10
  Mirf.spi = &MirfHardwareSpi; // On veut utiliser le port SPI hardware
  Mirf.init(); // Initialise la bibliothèque

  Mirf.channel = 1; // Choix du canal de communication (128 canaux disponibles, de 0 à 127)
  Mirf.payload = sizeof(actionStruct); //32; // Taille d'un message (maximum 32 octets)
  Mirf.config(); // Sauvegarde la configuration dans le module radio

  Mirf.setTADDR((byte *) toIDobjet);//toIDobjet); "nrf02"); // Adresse de transmission
  Mirf.setRADDR((byte *) IDobjet);//IDobjet); //"nrf01"); // Adresse de réception
  
  pinMode(7, OUTPUT);
pinMode(A1, INPUT);
pinMode(A5, INPUT);
pinMode(A7, INPUT);
Serial.begin(9600);
Serial.println("Grimoire par contact HF V0.1");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Loop/////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
actionStruct messageStru;

bouton_1 = analogRead(A1);
bouton_2 = analogRead(A5);
bouton_3 = analogRead(A7);

//Serial.print(bouton_1) ; Serial.print(bouton_2) ; Serial.println(bouton_3) ; 
if (bouton_1 < 700) {commande = 'f'; valeur = 1 ; sendToken = HIGH; }
if (bouton_2 < 700) {commande = 'b'; valeur = 1 ; sendToken = HIGH; }
if (bouton_3 < 700) {commande = 's'; valeur = 1 ; sendToken = HIGH; }


if (nextSend<millis()){
  digitalWrite(7, LOW);
  if (sendToken){
      digitalWrite(7, HIGH);
      messageStru.commande = commande ;//Serial.read(); //s :soins
      messageStru.valeur = valeur ;//Serial.parseInt(); //valeur : 1, ok. 2, non. ...
      
      Mirf.send((byte*) &messageStru); // On envoie le message (Strings) et strucutre
      while(Mirf.isSending()); // On attend la fin de l'envoi
      nextSend=millis()+40;
      sendToken = LOW ;
      }
   }
}

