#include <IRremote.h>

String idJoueur = "111111" ;


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
bool panFlag = HIGH ;
unsigned long debounceGachette ;






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
  pinMode(A1, INPUT_PULLUP);
  Serial.println("Flingue 0.1blue");
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

      for (int i=1 ; i<lgMess; i++) {
        if (isDigit(messActual[i])) {}
        else {cible = "vide";}
      }
    
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





if (digitalRead(A1) == HIGH && panFlag == HIGH && millis() > debounceGachette) {
  Serial.println("{");
  Serial.print("\"fromId\": \":"); Serial.print(idJoueur); Serial.println("\",");
  Serial.print("\"toId\": \""); Serial.print(cible); Serial.println("\",");
  Serial.print("\"rawPiercingDamage\": \":"); Serial.print(100); Serial.println("\",");
  Serial.println("{");
 
  panFlag = LOW ;
  debounceGachette = millis() + 20;
  }





/*
{
    "fromId": ":111111",
    "toId": ":123456",
    "rawPiercingDamage": 100
}

*/


//if (cible != "vide" || cible != ":123456" || cible != ":986543" || cible != ":184675") {cible = "vide";}
/////////////////////////////////////////Lecture/interprétation du message (aucune modification !!)////////////////////////////////////////
/*
if (cible != oldCible) {//Serial.println(cible);
   digitalWrite(13, HIGH);
   if (cible == "vide") {Serial.println("Pas de cible"); digitalWrite(13, LOW);}
   else if (cible == ":123456") {Serial.println("Vous pointez Alarik");}                    //rouge
   else if (cible == ":986543") {Serial.println("Vous pointez Rhea");}
   else if (cible == ":184675") {Serial.println("Vous pointez Dessloch");}
   else {//Serial.print(cible); 
   Serial.println("Cible à proximite"); 
   digitalWrite(13, LOW);
   }  //orange
}
*/





if (digitalRead(A1) == LOW && millis() > debounceGachette)
  {
  panFlag = HIGH ;
  debounceGachette = millis() + 50;
  }

    
}














