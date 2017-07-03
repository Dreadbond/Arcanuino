/*
const int S1 = A1;
const int S2 = A2;
const int S3 = A3;
const int S4 = A4;
const int S5 = A5;

int val1 ;
int val2 ;
int val3 ;
int val4 ;
int val5 ;
*/
//#include <Firmata.h>
#include <IRremote.h>
IRsend irsend;       //pin 3 pour émetteur

int pS ;
int iS ;
int mS ;
int anS ;
int auS ;

const int Led1 = 10 ;
const int Led2 = 11 ;
const int Led13=13;
int iLed1 = 0;
int iLed2 = 0;

const int butPin = 2 ;


int marge = 10;
int cibleP = 10;
int cibleI = 100;
int cibleM = 100;
int cibleAN = 100;
int cibleAU = 100;


void setup() {
  
Serial.begin(9600);
pinMode(Led1, OUTPUT);
pinMode(Led2, OUTPUT);
pinMode(butPin, INPUT);
pinMode(Led13, OUTPUT);
}


void loop() {
pS = analogRead(A1);
iS = analogRead(A2);
mS = analogRead(A3);
anS = analogRead(A4);
auS = analogRead(A5);

pS = map (pS, 0, 1023, 0, 255);
iS = map (iS, 0, 1023, 0, 255);
mS = map (mS, 0, 1023, 0, 255);
anS = map (anS, 0, 1023, 0, 255);
auS = map (auS, 0, 1023, 0, 255);


if (digitalRead(butPin) == HIGH) {
  digitalWrite(Led13, HIGH);
cibleP=pS;
cibleI=iS;
cibleM=mS;
cibleAN=anS;
cibleAU=auS;
}

/*
if (pS <= cibleP + 10 && pS >= cibleP - 10 )  {Serial.println("pouce!");}
if (iS <= cibleI + 10 && iS >= cibleI - 10 )  {Serial.println("index!");}
if (mS <= cibleM + 10 && mS >= cibleM - 10 )  {Serial.println("majeur!");}
if (anS <= cibleAN + 10 && anS >= cibleAN- 10 )  {Serial.println("annulaire!");}
if (auS <= cibleAU + 10 && auS >= cibleAU- 10 )  {Serial.println("auriculaire!");}
*/

if (pS <= 25 && pS >= 5 && iS <= 85 && iS >= 56 && mS <= 106 && mS >= 80)  {
  Serial.println("attaque !");
  irsend.sendSony(0xb10, 12);  }
  
if (pS <= 23 && pS >= 5 && iS <= 120 && iS >= 80 && mS <= 120 && mS >= 80 && anS <= 73 && anS >= 55 && auS <= 92 && auS >= 55)  {
  Serial.println("soins !");
  irsend.sendSony(0xa10, 12);   }
  
if (pS <= 20 && pS >= 12 && iS <= 45 && iS >= 35 && mS <= 100 && mS >= 83 && anS <= 62 && anS >= 50 && auS <= 40 && auS >= 30)  {
  Serial.println("defense !");
  irsend.sendSony(0xc10, 12);   }

  
Serial.print(pS);
Serial.print("p ");
Serial.print(iS);
Serial.print("i ");
Serial.print(mS);
Serial.print("m ");
Serial.print(anS);
Serial.print("an ");
Serial.print(auS);
Serial.println("au ");


/*analogWrite(iLed1, pS);
analogWrite(iLed1, pS);
*/

 digitalWrite(Led13, LOW);
delay(100);
}


