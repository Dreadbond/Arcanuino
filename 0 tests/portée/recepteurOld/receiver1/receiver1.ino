// receiver.pde
//
// Simple example of how to use VirtualWire to receive messages
// Implements a simplex (one-way) receiver with an Rx-B1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: receiver.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>

String result = "";

const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 9;
const int transmit_en_pin = 3;

unsigned long nextPoll = 0 ;

int pollLength = 50 ;
int grille[50] ;

int iPoll = 0 ;


void setup()
{
    delay(1000);
    Serial.begin(9600);	// Debugging only
    Serial.println("setup");

    pinMode(11, OUTPUT);
    pinMode(8, OUTPUT);

    digitalWrite(11, HIGH);
    vw_set_rx_pin(9);
    digitalWrite(8, LOW);

    // Initialise the IO and ISR
    vw_set_tx_pin(transmit_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec

    vw_rx_start();       // Start the receiver PLL running

    pinMode(led_pin, OUTPUT);
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
	int i;

        digitalWrite(led_pin, HIGH); // Flash a light to show received good message
	// Message with a good checksum received, dump it.
	//Serial.print("Got: ");
	
	for (i = 0; i < buflen; i++)
	{
  int qsd ;
  //result[i] = buf[i] ;
  result += char(buf[i]) ;
	    //Serial.print(result);  //, HEX
	    //Serial.print(' ');
	}
 //Serial.println(result);
	
        digitalWrite(led_pin, LOW);
    }




if (nextPoll < millis() ) {



 if (result.equals("!11")){
  grille[iPoll] = 1 ;
 }
 else
 {
 grille[iPoll] = 0 ;
 }
  
  iPoll++ ;
if (iPoll > pollLength ) {iPoll = 0 ;}


int moyenne ;
for (int i=0 ; i<pollLength ; i++) {
  moyenne += grille[i] ;
  //Serial.print(grille[i]);
  }
//Serial.println();
Serial.println(moyenne);

  nextPoll = millis() + 100 ;
  result = "" ;

  


}





}
