    /*
      1 - detection infra -> led s'allume
      2 - detection infra -> led pulse + fades
      3 - éteint led 5s si bouton ok pressé
    */

#include <IRremote.h>

/* 
*  Default is Arduino pin D11. 
*  You can change this to another available Arduino Pin.
*  Your IR receiver should be connected to the pin defined here
*/
int RECV_PIN = 2; 
unsigned long Temps = 0;
unsigned long Cible = 0;
const long inertie = 500 ;

const int led = 13;

/*
const int LedJolie = 9;
int intensiteLJ = 0;
int pasLJ = 5;
int tempsLJ ; */

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(led, OUTPUT);      
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}


void dump(decode_results *results) {
  // Dumps out the decode_results structure.
  // Call this after IRrecv::decode()
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
  }
  else if (results->decode_type == RC5) {
    Serial.print("Decoded RC5: ");
  }
  Serial.print(results->value, HEX);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");
  for (int i = 1; i < count; i++) {
    if (i & 1) {
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    }
    else {
      Serial.write('-');
      Serial.print((unsigned long) results->rawbuf[i]*USECPERTICK, DEC);
    }
    Serial.print(" ");
  }
  Serial.println();
}

void loop() {
  Temps = millis() ;

  if (irrecv.decode(&results)) {
    digitalWrite(led, HIGH);
    Cible = Temps + inertie ; //si quelque chose, Chrono marque le temps et anticipe
    
    
    Serial.println(results.value, HEX);
    dump(&results);
    irrecv.resume(); // Receive the next value
    }

if ( Temps >= Cible){ //si temps actu sup ou égal cible, stop lumière
    digitalWrite(led, LOW);

}

/* valeur d'intensité de la ledjolie :

if (Temps +  ){

LedJolie
intensiteLJ
pasLJ
tempsLJ
   if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ;
  }
analogWrite (LedJolie = ); 
} */

}
