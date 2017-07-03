#include <IRremote.h>

char messActual[10] = " ";
String strMessActual ;  // pour conversion 
String cible ;
String oldCible ;
int tempsBuffer ;
int posCharRcv ;

bool cibleConfirmee = LOW ;

unsigned long faireMessageCible ;   //uniquement pour réception char
unsigned long gateCible ;         //pour la cible en elle-même
unsigned long resetCible ; 

int debug = 0 ;

int RECV_PIN = 6;
IRrecv irrecv(RECV_PIN);
decode_results results;



void raz() {
cible = " " ;
strMessActual = " " ;
}

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {

if (Serial.available() > 0) {debug = Serial.read();}
//if (debug == 1) {Serial.println("debug");}







oldCible = cible ;

//////////////////////////////////////////Traitement du message///////////////////////////////////////
  if (irrecv.decode(&results)) {                    //détection Ir : faisage de message
    messActual[posCharRcv] = char(results.value) ;
    strMessActual = String(messActual) ;
    irrecv.resume(); // Receive the next value
    //cleanMessage = millis() + 3000;
    posCharRcv++ ;
    //Serial.println(strMessActual);
    resetCible = millis() + 300;
    faireMessageCible = millis() + 50 ;
    }


//if (strMessActual.length() == 6) {posCharRcv = 0 ; strMessActual.remove(0);}
if (strMessActual.length() > 6) {posCharRcv = 0 ; }   //si messae trop long = invalide


if (faireMessageCible < millis() || posCharRcv > 6) {    //si message (et cible) confirmé
  posCharRcv = 0 ;  //retour chariot
  cible = String(messActual) ;
  strMessActual.remove(0);
  //resetCible = millis() + 1000;
}

if (resetCible < millis() ) {
  cible = "vide"; 
}











/////////////////////////////////////////Vérification du message////////////////////////////////////////


if (cible != oldCible) {Serial.println(cible);
   if (cible == "Alarik") {Serial.println("Alarik");}
   else if (cible == "vide") {Serial.println("Pas de cible");}
   else {Serial.print(cible); Serial.println(" : Cible inconnue");}
}



















    
}














