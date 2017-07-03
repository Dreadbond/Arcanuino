#include <IRremote.h>

const int buttonPin1 = 7;     // the number of the pushbutton pin
const int buttonPin2 = 6;
const int ledPin =  13;      // the number of the LED pin
// const int IRLed =  12;    NOPE
unsigned long Temps = 0;
unsigned long Cible1 = 0;
unsigned long Cible2 = 0;
const long cooldown1 = 100 ;
const long cooldown2 = 100 ;

int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;

IRsend irsend;       //pin 3 pour émetteur

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
}

void loop() {
    Temps = millis() ;
  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  
  if (buttonState1 == HIGH && Cible2 < Temps) {           // bouton 1 : lumière et envoi "soins"
    digitalWrite(ledPin, HIGH);         
        irsend.sendSony(0xa10, 12);
        Cible2 = Temps + cooldown2 ;   // heure pour réutiliser le sort = instant T + cooldown2
        Serial.println(Cible2, DEC);
        Serial.println(Temps, DEC);
        //delay(40);
  }
  digitalWrite(ledPin, LOW);   
  
  
    if (buttonState2 == HIGH && Cible1 < Temps) {           // bouton 2 : lumière et envoi 20 dégâts si pas en cooldown
    digitalWrite(ledPin, HIGH);         
        irsend.sendSony(0xb10, 12);
        //delay(2000);                     //cooldown général : 2secondes
        Cible1 = Temps + cooldown1 ;   // heure pour réutiliser le sort = instant T + cooldown
        Serial.println(Cible1, DEC);
        Serial.println(Temps, DEC);
      }

digitalWrite(ledPin, LOW);   

}
      
