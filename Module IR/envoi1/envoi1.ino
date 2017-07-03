#include <IRremote.h>

const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
const int IRLed =  12;     

int buttonState = 0;         // variable for reading the pushbutton status

IRsend irsend;       //pin 3 pour émetteur

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
 
 
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);   
    {
	irsend.sendSony(0xa90, 12);
        delay(40);
  }
  }
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}
