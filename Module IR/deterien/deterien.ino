#include <IRremote.h>

/* 
*  Default is Arduino pin D11. 
*  You can change this to another available Arduino Pin.
*  Your IR receiver should be connected to the pin defined here
*/
//int RECV_PIN = 2; 
//unsigned long Temps = 0;   déjà présent 
//unsigned long Cible = 0;    pour la Led
//const long inertie = 500 ;

//const int led = 13;
//const int healthLED = 9 ;
//int intenHL = 0 ;

//int health = 100 ;
//int message = 0 ;
//int Mort = 0 ;
//String messagestr ;

/*
const int LedJolie = 9;
int intenHLLJ = 0;
int pasLJ = 5;
int tempsLJ ; */

//IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
 // pinMode(led, OUTPUT); 
 // pinMode(healthLED, OUTPUT);  
 // Serial.begin(9600);
 // irrecv.enableIRIn(); // Start the receiver
 // health = 100 ;
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
  intenHL = 2.55 * health ;
  analogWrite(healthLED, intenHL) ;
  
  
  if (irrecv.decode(&results)) {
    digitalWrite(led, HIGH);
    Cible = Temps + inertie ; //si quelque chose, cible marque le temps et anticipe (temps cible)
    
    //Serial.println(results.value, HEX);
    //dump(&results);
    irrecv.resume(); // Receive the next value
    
    message = int(results.value);
    //Serial.print("Le nombre est : ");
    //Serial.println(message, HEX);
    //Serial.println(message, DEC);
    }
    
       if (health <= 0 ) {   
       Mort = Mort + 1 ;
       Serial.print("Player 1 est mort ");
       Serial.print(Mort);
       Serial.println(" fois.");
delay (10000) ;    //nope
health = 100 ;
}
    
       if (message == 2832 && health > 0) {    //b10 2832 : dégâts 
  health = (health - 20) ;
    Serial.print("health ");
    Serial.println(health, DEC);  
}

       if (message == 2576 && health < 100) {    //a10 2576 soins
  health = health + 5 ;
    Serial.print("health ");
    Serial.println(health, DEC);    
}
       if (message == 2576 && health >= 100) {
         Serial.println("Vie au maximum.") ;    
}

//intenHL = health ;
//analogWrite(healthLED, health) ;
 
message = 0;
if ( Temps >= Cible){ digitalWrite(led, LOW);}  //si temps actu sup ou égal cible, stop lumière





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
