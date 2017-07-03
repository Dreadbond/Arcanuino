#include <IRremote.h>
  String AEnvoyer = ":123456";   //Alarik
unsigned long tagGate = 0 ;

IRsend irsend;

void setup()
{

}

void loop() {
  if (tagGate < millis()) {

  for (int i = 0; i < AEnvoyer.length(); i++){

    irsend.sendRC5(AEnvoyer.charAt(i), 12); 
    delay(15);

    //Serial.print("TX:");
    //Serial.println(AEnvoyer.charAt(i));

  }/*
delay(15);
  irsend.sendRC5(13, 12);  //send a RETURN
  delay(15);
  irsend.sendRC5(10, 12); */

    tagGate = millis() + 200 ;

  }
}
