#include <VirtualWire.h>

const int ledPin = 13;      // led connected to digital pin 13

int bouton_1;
int bouton_2;
int bouton_3;

void feu(){
        digitalWrite(ledPin, HIGH);
  char msg1[17]= "gr_aoe_fe_to_red";

    vw_send((uint8_t *)msg1, 17); //strlen(msg) + x
    vw_wait_tx(); // Wait until the whole message is gone
        delay(500);
}

void bouclier(){
        digitalWrite(ledPin, HIGH);
  char msg1[17]= "gr_aoe_bo_to_blue";

    vw_send((uint8_t *)msg1, 17); //strlen(msg) + x
    vw_wait_tx(); // Wait until the whole message is gone
        delay(500);
}

void soins(){
        digitalWrite(ledPin, HIGH);
  char msg1[17]= "gr_aoe_so_to_blue";

    vw_send((uint8_t *)msg1, 17); //strlen(msg) + x
    vw_wait_tx(); // Wait until the whole message is gone
        delay(500);
}

void setup() {
pinMode(A1, INPUT);
pinMode(A5, INPUT);
pinMode(A7, INPUT);
pinMode(ledPin, OUTPUT);
vw_set_tx_pin(12);
vw_setup(2000);
Serial.begin(9600);
Serial.println("Grimoire par contact V1");
}

void loop() {
  feu();
  delay(1000);
/*
bouton_1 = analogRead(A1);
bouton_2 = analogRead(A5);
bouton_3 = analogRead(A7);

//Serial.print(bouton_1) ; Serial.print(bouton_2) ; Serial.println(bouton_3) ; 
if (bouton_1 < 800) {feu();}
if (bouton_2 < 800) {bouclier();}
if (bouton_3 < 800) {soins();}

digitalWrite(ledPin, LOW);
*/

}
