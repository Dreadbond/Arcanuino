#include <IRremote.h>

#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI

//String idJoueur = "111111" ; //osef
char *IDobjet = "nrf02";
char *toIDobjet = "nrf01" ;     //ID de l'objet qui est sensé recevoir

/*
{
    "fromId": ":111111",
    "toId": ":123456",
    "rawPiercingDamage": 100
}
*/
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
int RECV_PIN = 6;
IRrecv irrecv(RECV_PIN);
decode_results results;

//Neopixel


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


typedef struct {
  char objectStru = 'f' ;
  char commande;
  int valeur;
} actionStruct;

typedef struct {
  char objectStru = 'f' ;
  char commande;
  byte cible[6];
} actionCibleStruct;

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Setup////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  Mirf.cePin = 9; // Broche CE sur D9
  Mirf.csnPin = 10; // Broche CSN sur D10
  Mirf.spi = &MirfHardwareSpi; // On veut utiliser le port SPI hardware
  Mirf.init(); // Initialise la bibliothèque

  Mirf.channel = 1; // Choix du canal de communication (128 canaux disponibles, de 0 à 127)
  Mirf.payload = sizeof(actionStruct); //32; // Taille d'un message (maximum 32 octets)
  Mirf.config(); // Sauvegarde la configuration dans le module radio

  Mirf.setTADDR((byte *) toIDobjet);//toIDobjet); "nrf02"); // Adresse de transmission
  Mirf.setRADDR((byte *) IDobjet);//IDobjet); //"nrf01"); // Adresse de réception
  
  pinMode(A2, OUTPUT);
  
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(A1, INPUT_PULLUP);
  Serial.println("Flingue 0.2");
}




//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Loop/////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
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
if (digitalRead(A1) == HIGH && panFlag == HIGH && millis() > debounceGachette) {
      
      messageStru.commande = 'g' ;//Serial.read(); //g : gachette
      messageStru.valeur = 1 ;//Serial.parseInt(); //valeur : 1, ok. 2, non. ...
      
      Mirf.send((byte*) &messageStru); // On envoie le message (Strings) et strucutre
      while(Mirf.isSending()); // On attend la fin de l'envoi
 
  panFlag = LOW ;
  debounceGachette = millis() + 20;
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


if (mireCible) {
  digitalWrite(A2, HIGH);
}
else
{
  digitalWrite(A2, LOW);
}


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
