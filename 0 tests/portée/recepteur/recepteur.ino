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

const int led_pin = 13;
//const int transmit_pin = 12;
const int receive_pin = 11;
const int rssi_pin = A5 ;
const int transmit_en_pin = 3;
const int JU_pin = A4 ;
const int GD_pin = A7 ;

long rssi_score ;
unsigned long refeshRssi ;


int rssi;

void setup()
{
    //delay(1000);
    //Serial.begin(9600);	// Debugging only
    Serial.begin(115200);  // Debugging only
    Serial.println("recept test rssi");

    // Initialise the IO and ISR
    //vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec

    //pinMode(A1, INPUT);
    vw_rx_start();       // Start the receiver PLL running

    pinMode(led_pin, OUTPUT);   
    pinMode(GD_pin, OUTPUT); digitalWrite(GD_pin, LOW);
    pinMode(JU_pin, OUTPUT); digitalWrite(JU_pin, HIGH);
    pinMode(rssi_pin, INPUT);   
    pinMode(receive_pin, INPUT);
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

      rssi=analogRead(rssi_pin);
      //rssi=map(rssi, 530, 740, 0, 255);
      //rssi=constrain(rssi, 0, 255);
      
      Serial.println(rssi);

    //if (rssi > 650) {rssi_score += rssi ;}  //rssi > 600 || rssi < 400
    if (rssi > 600 || rssi < 400) {rssi_score += rssi ;}  


    if (millis() > refeshRssi) {
      rssi_score = 0 ;
      refeshRssi = millis() + 110 ;
      }
    
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
	    int i;
      char messActual[buflen] = " ";
      
      digitalWrite(led_pin, HIGH);

        	for (i = 0; i < buflen; i++)
        	{
          //char charBuf = ;
          messActual[i] = char(buf[i]) ;
        	}
  String messActualConv = String(messActual);
  /*
  Serial.print("Got: ");
	Serial.print(messActualConv);
  Serial.print(" ");

  */
  Serial.println(0);
  //Serial.println(rssi_score);
  rssi_score = 0 ;
  refeshRssi = millis() + 130 ;
  digitalWrite(led_pin, LOW);
    }







    
}
