#include <IRremote.h>

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

void raz() {
    posCharRcv = 0 ;  //retour chariot
    cible = "vide" ;
    strMessActual = "arf" ;      //strMessActual.remove(0);
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
  //cible = "vide";
  /*
  Serial.print("Message invalide : "); 
  Serial.print(posCharRcv);
  Serial.print(" "); 
  Serial.println(strMessActual.length());*/
  raz();
  write_message = LOW;
}

//message valide
if (faireMessageCible < millis() || strMessActual.length() == lgMess ) {
    if (strMessActual.length() == lgMess && strMessActual.charAt(0) == ':' ) {
    posCharRcv = 0 ;  //retour chariot
    cible = String(messActual) ;
    strMessActual.remove(0);
    for (int i=0 ; i<lgMess; i++) {messActual[i] = '\0' ;}
    write_message = LOW;
    //Serial.println("Ok");
    }
  }



if (resetCible < millis() || strMessActual.length() > lgMess ) {   //grosse galère, je compte sur le || strMessActual.length() == lgMess pour éviter ça
  raz();
  //cible = "vide"; 
}











/////////////////////////////////////////Lecture/interprétation du message (aucune modification !!)////////////////////////////////////////


if (cible != oldCible) {//Serial.println(cible);
   digitalWrite(13, HIGH);
   if (cible == "vide") {Serial.println("Pas de cible"); digitalWrite(13, LOW);}
   else if (cible == ":123456") {Serial.println("Vous pointez Alarik");}                    //rouge
   else if (cible == ":986543") {Serial.println("Vous pointez Rhea");}
   else if (cible == ":184675") {Serial.println("Vous pointez Dessloch");}
   else {Serial.print(cible); Serial.println(" : Cible inconnue"); digitalWrite(13, LOW);}  //orange
}



















    
}














