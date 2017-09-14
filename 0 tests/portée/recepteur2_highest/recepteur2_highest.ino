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
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3f,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


const int led_pin = 13;
//const int transmit_pin = 12;
const int receive_pin = 11;
const int rssi_pin = A3 ;
const int transmit_en_pin = 3;
const int JU_pin = A4 ;
const int GD_pin = A7 ;

long rssi_score_1 = 900 ;
long rssi_score_2 = 900 ;
unsigned long refeshRssi ;

int sz = 10 ;
int rssi[10] ;

int rssiIndex ;
long rssiTotal ;
int highest ;

void setup()
{
    //delay(1000);
    //Serial.begin(9600);	// Debugging only
    //Serial.begin(115200);  // Debugging only
    //Serial.println("recept test rssi");

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

    lcd.init();                      // initialize the lcd 
    lcd.backlight();
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;


if (rssi[rssiIndex] != analogRead(rssi_pin) ){
      rssi[rssiIndex] = analogRead(rssi_pin);

//Serial.print(" ") ;
      rssiIndex++ ;
}
      if (rssiIndex >= sz) {rssiIndex = 0; }

//Serial.println(rssi[rssiIndex]) ;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
highest = 0 ;

  for (int i=0 ; i<sz ; i++)  {
      //Serial.print(rssi[i]);  Serial.print(" ");
      
      if (rssi[i] > highest) {highest = rssi[i] ;}
      
      }
      //Serial.println();
  
    //rssiTotal /= sz ;
    //Serial.println(rssiTotal) ;
    //Serial.println();
   

  
    if(buf[0] == 49) {
      rssi_score_1 = highest ;
      //Serial.print("Tag 1 ");       Serial.println(rssi_score_1); 
      
      //Serial.println(0);
      }


    if(buf[0] == 50) {
      rssi_score_2 = highest ;
      //Serial.print("Tag 2 ");       Serial.println(rssi_score_2); 
      
      //Serial.println(1200);
    }
//Serial.print(rssi_score_1);Serial.print(" ");Serial.print(rssi_score_2);Serial.println();
 rssiTotal=0;

   lcd.setCursor(0, 0);
  lcd.print("Tag 1 ");
  lcd.print(rssi_score_1);
  lcd.setCursor(0, 1);
  lcd.print("Tag 2 ");
  lcd.print(rssi_score_2);
    }

//Serial.println();

/*
Serial.print(rssi[rssiIndex]) ;
Serial.print(" ") ;
Serial.print(rssi_score_1);Serial.print(" ");Serial.print(rssi_score_2);Serial.println();
*/


    
}
