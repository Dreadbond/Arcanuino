#include <IRremote.h>

const int buttonPin1 = 2;     // the number of the pushbutton pin
const int buttonPin2 = 7;
const int ledPin =  13;      // the number of the LED pin
const int IRLed =  12;     

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
  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
 
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState1 == HIGH) {
    digitalWrite(ledPin, HIGH);   
    {
	irsend.sendSony(0xb10, 12);
        delay(40);
  }
  }
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}
