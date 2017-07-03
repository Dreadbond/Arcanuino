#include <IRremote.h>
  String AEnvoyer = "!123456";   //Alarik par défaut
unsigned long tagGate = 0 ;

IRsend irsend;

void setup()
{
pinMode(4, INPUT_PULLUP);
pinMode(5, INPUT_PULLUP);
pinMode(6, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

if (digitalRead(4) == LOW) {AEnvoyer = "!123456";}  //Alarik
if (digitalRead(5) == LOW) {AEnvoyer = "!986543";}  //Rhea
if (digitalRead(6) == LOW) {AEnvoyer = "!184675";}  //Dessloch
}

void loop() {

  if (tagGate < millis()) {
    for (int i = 0; i < AEnvoyer.length(); i++){
      irsend.sendRC5(AEnvoyer.charAt(i), 12); 
      delay(15);
    }
    tagGate = millis() + 100 ; //200 à la base
  }

}
