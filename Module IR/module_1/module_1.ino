#include <IRremote.h>


int RECV_PIN = 2;         
// pour la Led IR = toujours sortie 3PWM
const int buttonPin1 = 4;     // the number of the pushbutton pin
const int buttonPin2 = 7;
const int healthLED = 9 ;
const int ledT =  13;      // Led témoin (réception)
int intenHL = 0 ;          //intensité healthLed


unsigned long Temps = 0;     //horloge
unsigned long Cible = 0;     //temps-cible led
unsigned long Cible1 = 0;    // tc sort 1
unsigned long Cible2 = 0;
const long inertie = 500 ;   // cooldown led 13
const long cooldown1 = 1500 ;
const long cooldown2 = 400 ;

int health = 100 ;
int message = 0 ;
int Mort = 0 ;
String messagestr ;

int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;

IRsend irsend;      
IRrecv irrecv(RECV_PIN);
decode_results results;




void setup() {
  // initialize the LED pin as an output:
  pinMode(healthLED, OUTPUT);  
  pinMode(ledT, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
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
    
    intenHL = 2.55 * health ;
  analogWrite(healthLED, intenHL) ;
  
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  
  if (buttonState1 == HIGH && Cible2 < Temps) {           // bouton 1 : lumière et envoi "soins"
    digitalWrite(ledT, HIGH);         
        irsend.sendSony(0xa10, 12);
        Cible2 = Temps + cooldown2 ;   // heure pour réutiliser le sort = instant T + cooldown2
        Serial.println(Cible2, DEC);
        Serial.println(Temps, DEC);
        //delay(40);
  }
  digitalWrite(ledT, LOW);   
  
  
    if (buttonState2 == HIGH && Cible1 < Temps) {           // bouton 2 : lumière et envoi 20 dégâts si pas en cooldown
    digitalWrite(ledT, HIGH);         
        irsend.sendSony(0xb10, 12);
        //delay(2000);                     //cooldown général : 2secondes
        Cible1 = Temps + cooldown1 ;   // heure pour réutiliser le sort = instant T + cooldown
        Serial.println(Cible1, DEC);
        Serial.println(Temps, DEC);
      }
      
/////////////////////////RECEPTION/////////////////////////////      
      
      
  if (irrecv.decode(&results)) {
    digitalWrite(ledT, HIGH);
    Cible = Temps + inertie ; //si quelque chose, cible marque le temps et anticipe (temps cible) pour la Led 13
    
    //dump(&results);
    irrecv.resume(); // Receive the next value
    
    message = int(results.value);
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
if ( Temps >= Cible){ digitalWrite(ledT, LOW);}  //si temps actu sup ou égal cible, stop lumière




digitalWrite(ledT, LOW);   

}
