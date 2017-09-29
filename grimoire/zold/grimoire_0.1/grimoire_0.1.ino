#include <VirtualWire.h>
#include <CapacitiveSensor.h>

const int ledPin = 13;      // led connected to digital pin 13

bool bouton_1;
bool bouton_2;
bool bouton_3;

const char *msg1 = "T";
const char *msg2 = "U";
const char *msg3 = "V";

int sensi = 20 ;
CapacitiveSensor   cs_9_2 = CapacitiveSensor(9, 2);       // 10 megohm resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil
CapacitiveSensor   cs_9_5 = CapacitiveSensor(9, 5);       // 10 megohm resistor between pins 4 & 6, pin 6 is sensor pin, add wire, foil
CapacitiveSensor   cs_9_11 = CapacitiveSensor(9, 11);       // 10 megohm resistor between pins 4 & 8, pin 8 is sensor pin, add wire, foil

void boubou(long total){
        digitalWrite(ledPin, HIGH);
        Serial.println("Protection"); // On signale le début de l'envoi
        Serial.println(total);
        vw_send((uint8_t *)msg1, 1); // On envoie le message
        vw_wait_tx(); // On attend la fin de l'envoi
        //Serial.println("Done !"); // On signal la fin de l'envoi
        delay(500);
}

void feu(long total){
        digitalWrite(ledPin, HIGH);
        Serial.println("Nova de feu"); // On signale le début de l'envoi
        Serial.println(total);
        vw_send((uint8_t *)msg2, 1); // On envoie le message
        vw_wait_tx(); // On attend la fin de l'envoi
        //Serial.println("Done !"); // On signal la fin de l'envoi
        delay(500);
}

void soins(long total){
        digitalWrite(ledPin, HIGH);
        Serial.print("Soins "); // On signale le début de l'envoi
        Serial.println(total);
        vw_send((uint8_t *)msg3, 1); // On envoie le message
        vw_wait_tx(); // On attend la fin de l'envoi
        //Serial.println("Done !"); // On signal la fin de l'envoi
        delay(500);
}

void setup() {
pinMode(ledPin, OUTPUT);
vw_setup(2000);
Serial.begin(9600);
Serial.println("Grimoire V0.1");
}

void loop() {
  long start = millis();
  long total1 =  cs_9_2.capacitiveSensor(30);
  long total2 =  cs_9_5.capacitiveSensor(30);
  long total3 =  cs_9_11.capacitiveSensor(30);

if (total1>110) {boubou(total1);}
if (total2>90) {feu(total2);}
if (total3>70) {soins(total3);}

digitalWrite(ledPin, LOW);
}
