#include <IRremote.h>

int RECV_PIN = 11;   
IRrecv irrecv(RECV_PIN);
IRsend irsend;          // pour la Led IR = toujours sortie 3PWM

// pour la Led IR = toujours sortie 3PWM
const int buttonPin1 = 4;     // the number of the pushbutton pin
const int buttonPin2 = 5;
const int buttonPin3 = 6;
const int buttonPin4 = 7;
const int healthLED = 10 ;
const int ledT =  13;      // Led témoin (réception)
int intenHL = 0 ;          //intensité healthLed


unsigned long Temps = 0;     //horloge
unsigned long Cible = 0;     //temps-cible led
unsigned long Cible1 = 0;    // tc sort 1
unsigned long Cible2 = 0;
unsigned long Cible3 = 0;
const long inertie = 200 ;   // cooldown led 13
const long cooldown1 = 200 ;
const long cooldown2 = 2000 ;

float health = 100 ;
float degFinaux = 0 ;
int degHealth = 0 ;
int degDeg = 0 ;
float degDef = 0 ;
int message = 0 ;
int Mort = 0 ;
String messagestr ;

int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;

int state = 0;
int flag = 0;        // make sure that you return the state only once


decode_results results;

void setup() {
  Serial.begin(9600);

  pinMode(healthLED, OUTPUT);  
  pinMode(ledT, OUTPUT);

  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  
  irrecv.enableIRIn(); // Start the receiver
  health = 100 ; 
}


void attaqueSend() {
        irsend.sendSony(0xa10, 12);
        Cible1 = Temps + cooldown1 ;   // heure pour réutiliser le sort = instant T + cooldown
        irrecv.enableIRIn();  
        Serial.println("Attaque");            
        }
        
void attaque2Send() {
        irsend.sendSony(0xb10, 12);
        Cible2 = Temps + cooldown2 ;   // heure pour réutiliser le sort = instant T + cooldown
        irrecv.enableIRIn();  
        Serial.println("Grosse attaque !");            
        }
        
void attaqueRcv () {
    degDeg = -5 ;
    }

void attaque2Rcv() {
    degDeg = -15 ;
    }

int defenseRcv(int val) {
switch (val) {
  case 1:
    degDef = 0.5 ;
    break;
  case 2:
    degDef = 1 ;
    break;
    }
  }

void soinsRcv() {
    degHealth = 3 ;
    Cible3 = Temps + cooldown1 ;
    Serial.print("Soins ");
    }

void mort() {
       //health = 0 ;  
       analogWrite(healthLED, 0);
       Mort = Mort + 1 ;
       Serial.print("Player 1 est mort ");
       Serial.print(Mort);
       Serial.println(" fois.");

delay (5000) ;    //nope
health = 100 ;
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
    
    intenHL = 2.55 * health / 2 ;
    intenHL = constrain(intenHL, 0, 255);
    analogWrite(healthLED, intenHL) ;

///////////////////////////////////////////////////////////////
////////////////////////////BOUTONS////////////////////////////
///////////////////////////////////////////////////////////////
  
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  
  if (buttonState1 == HIGH && Temps > Cible1 ) {attaqueSend();}           // bouton 1 : attaque canalisée
  if (buttonState2 == HIGH && Temps > Cible2 ) {attaque2Send();}          // bouton 2 : grosse attaque
  if (buttonState3 == HIGH ) {defenseRcv(1);}                             // bouton 3 : réduit les dégâts
        else if (buttonState3 == LOW) {defenseRcv(2);}
  if (buttonState4 == HIGH && Temps > Cible3 ) {soinsRcv();}              // bouton 4 : soins

     
///////////////////////////////////////////////////////////////
/////////////////////////RECEPTION/////////////////////////////
///////////////////////////////////////////////////////////////

  if (irrecv.decode(&results)) {
    digitalWrite(ledT, HIGH);
    Cible = Temps + inertie ; //si quelque chose, cible marque le temps et anticipe (temps cible) pour la Led 13
   
    //dump(&results);
    irrecv.resume(); // Receive the next value

    message = int(results.value);
    //Serial.println(message);
    }
       if (message == 2576 && health > 0) {attaqueRcv();}   //a10 2576 : grosse attaque
       if (message == 2832 && health > 0) {attaque2Rcv();}    //b10 2832 : dégâts 

///////////////////////////////////////////////////////////////
/////////////////////////////SANTE/////////////////////////////
///////////////////////////////////////////////////////////////

       degFinaux = degDef * degDeg + degHealth  ;
       health = health + degFinaux ;
         if (degFinaux != 0 ) {Serial.println(health);}
         if (health <= 0 ) { mort();}
      /* if (health >= 100) {
         Serial.println("Vie au maximum.") ; 
         health = 100 ;
}
*/
    
degFinaux = 0 ;
degHealth = 0 ;
degDeg = 0 ;
degDef = 0 ;
message = 0;
if ( Temps >= Cible){ digitalWrite(ledT, LOW);}  //si temps actu sup ou égal cible, stop lumière


}
