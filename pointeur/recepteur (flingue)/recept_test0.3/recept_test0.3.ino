#include <IRremote.h>

//traitement message entré
bool write_message = LOW ;      //si détecté un ":", il concatène la suite
char messActual[10] = '\0';
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

void raz() {
    posCharRcv = 0 ;  //retour chariot
    cible = "vide" ;
    strMessActual.remove(0);
    for (int i=0 ; i<lgMess; i++) {messActual[i] = '\0' ;}
    write_message = LOW;
}

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {

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
        messActual[posCharRcv] = char(results.value) ;
        strMessActual = String(messActual) ;
        irrecv.resume(); // Receive the next value
        posCharRcv++ ;
        resetCible = millis() + 300;
        faireMessageCible = millis() + 50 ;
        //Serial.print(strMessActual); Serial.print(" ");
        //Serial.print(messActual[posCharRcv]);
        }
       /* }
        else {//Serial.println("Message pourri");
        }*/
    /*}
    else 
    { */
    //Serial.println("Rien a ecouter");
    }


//if (strMessActual.length() == 6) {posCharRcv = 0 ; strMessActual.remove(0);}

//stop message
/*
if (strMessActual.length() > lgMess || strMessActual.charAt(0) != ':') {
Serial.println("Message pourri");
raz();
}*/

/*
//message valide
if (faireMessageCible < millis() || strMessActual.length() == lgMess && strMessActual.charAt(0) == ':') {
    posCharRcv = 0 ;  //retour chariot
    cible = String(messActual) ;
    strMessActual.remove(0);
    messActual[lgMess] ;
    write_message = LOW;
    Serial.println("Ok");
  }*/

if (strMessActual.length() > lgMess) {
  Serial.println("Message invalide"); 
  raz();
  //cible = "vide";
}

//message valide
if (faireMessageCible < millis() ) {
    if (strMessActual.length() == lgMess && strMessActual.charAt(0) == ':' ) {
    posCharRcv = 0 ;  //retour chariot
    cible = String(messActual) ;
    strMessActual.remove(0);
    for (int i=0 ; i<lgMess; i++) {messActual[i] = '\0' ;}
    write_message = LOW;
    //Serial.println("Ok");
    }
  }


if (resetCible < millis() ) {
  raz();
  //cible = "vide"; 
}











/////////////////////////////////////////Vérification du message////////////////////////////////////////


if (cible != oldCible) {//Serial.println(cible);
   digitalWrite(13, HIGH);
   if (cible == "vide") {Serial.println("Pas de cible"); digitalWrite(13, LOW);}
   else if (cible == ":123456") {Serial.println("Vous pointez Alarik");}
   else if (cible == ":986543") {Serial.println("Vous pointez Rhea");}
   else if (cible == ":184675") {Serial.println("Vous pointez Dessloch");}
   else {Serial.print(cible); Serial.println(" : Cible inconnue"); digitalWrite(13, LOW);}
}



















    
}














