/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */
unsigned long qsd ;
unsigned long oldQsd ;
long reslt;


#include <IRremote.h>

int RECV_PIN = 5;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  
  if (irrecv.decode(&results)) {
    
    

    


qsd = millis();
reslt = qsd - oldQsd ;
oldQsd = qsd ;

irrecv.resume();

if (results.value == 1) {Serial.print("hub 1 ");}
else if (results.value == 2) {Serial.print("hub n2 ");}
else {
  //char erf = char(results.value);
  Serial.print(results.value, DEC);
  //Serial.print(erf);
  Serial.print(" ");
  }

Serial.println(reslt);


  }


  
  //delay(100);
}
