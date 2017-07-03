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
int attaqueCap[5] ;
int defenseCap[5] ;
int soinsCap[5] ;
int coolDownAtt;
int coolDownDef;
int coolDownSoi;
unsigned long temps;
bool attaqueState;
bool defenseState;
bool soinsState;

const int ledAtt=4;
const int ledDef=5;
const int ledSoi=6;
const int Led13=13;

const int butPin = 2 ;
bool butState ;
int butCount = 0 ;

int marge = 6;   //5, bien

void attaque () {
  Serial.println("Attaque !");
  digitalWrite(ledAtt, HIGH);
  coolDownAtt = millis()+200;
}

void defense () {
}

void soins () {
}

void setup() {
  
Serial.begin(9600);
pinMode(ledAtt, OUTPUT);
pinMode(ledDef, OUTPUT);
pinMode(ledSoi, OUTPUT);
pinMode(butPin, INPUT);
pinMode(Led13, OUTPUT);

delay (500);
digitalWrite(ledAtt, HIGH);
delay (500);
digitalWrite(ledDef, HIGH);
delay (500);
digitalWrite(ledSoi, HIGH);
delay (500);
digitalWrite(Led13, HIGH);
delay (500);
digitalWrite(ledSoi, LOW);
digitalWrite(ledDef, LOW);
digitalWrite(ledAtt, LOW);
digitalWrite(Led13, LOW);
}

void loop() {
temps = millis() ;
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

butState = digitalRead(butPin);
if (butState == HIGH) {butCount ++ ;

switch (butCount) {
  case 1:
digitalWrite(Led13, HIGH);
digitalWrite(ledAtt, HIGH);
attaqueCap[0] = pS ;
attaqueCap[1] = iS ;
attaqueCap[2] = mS ;
attaqueCap[3] = anS ;
attaqueCap[4] = auS ;
Serial.print(attaqueCap[0]);
Serial.print("p ");
Serial.print(attaqueCap[1]);
Serial.print("i ");
Serial.print(attaqueCap[2]);
Serial.print("m ");
Serial.print(attaqueCap[3]);
Serial.print("an ");
Serial.print(attaqueCap[4]);
Serial.println("au ATTAQUE");
delay (1000);
digitalWrite(ledAtt, LOW);
digitalWrite(Led13, LOW);
  break;
  

  case 2:
digitalWrite(Led13, HIGH);
digitalWrite(ledDef, HIGH);
defenseCap[0] = pS ;
defenseCap[1] = iS ;
defenseCap[2] = mS ;
defenseCap[3] = anS ;
defenseCap[4] = auS ;
Serial.print(defenseCap[0]);
Serial.print("p ");
Serial.print(defenseCap[1]);
Serial.print("i ");
Serial.print(defenseCap[2]);
Serial.print("m ");
Serial.print(defenseCap[3]);
Serial.print("an ");
Serial.print(defenseCap[4]);
Serial.println("au DEFENSE");
delay (1000);
digitalWrite(ledDef, LOW);
digitalWrite(Led13, LOW);
  break;

  case 3:
digitalWrite(Led13, HIGH);
digitalWrite(ledSoi, HIGH);
soinsCap[0] = pS ;
soinsCap[1] = iS ;
soinsCap[2] = mS ;
soinsCap[3] = anS ;
soinsCap[4] = auS ;
Serial.print(soinsCap[0]);
Serial.print("p ");
Serial.print(soinsCap[1]);
Serial.print("i ");
Serial.print(soinsCap[2]);
Serial.print("m ");
Serial.print(soinsCap[3]);
Serial.print("an ");
Serial.print(soinsCap[4]);
Serial.println("au SOINS");
delay (1000);
digitalWrite(ledSoi, LOW);
digitalWrite(Led13, LOW);
  break;
  
  default:
  break;
}
}

if (butCount >= 3) {butCount = 0;} 





if (pS <= attaqueCap[0] + marge 
&& pS >= attaqueCap[0] - marge 
&& iS <= attaqueCap[1] + marge 
&& iS >= attaqueCap[1] - marge 
&& mS <= attaqueCap[2] + marge  
&& mS >= attaqueCap[2] - marge 
&& anS <= attaqueCap[3] + marge 
&& anS >= attaqueCap[3] - marge 
&& auS <= attaqueCap[4] + marge 
&& auS >= attaqueCap[4] - marge )  
{
attaque ()  ;
Serial.println(coolDownAtt);
}
  
if (pS <= defenseCap[0] + marge 
&& pS >= defenseCap[0] - marge 
&& iS <= defenseCap[1] + marge 
&& iS >= defenseCap[1] - marge 
&& mS <= defenseCap[2] + marge  
&& mS >= defenseCap[2] - marge 
&& anS <= defenseCap[3] + marge 
&& anS >= defenseCap[3] - marge 
&& auS <= defenseCap[4] + marge 
&& auS >= defenseCap[4] - marge )  
{
defense ();
}
  
if (pS <= soinsCap[0] + marge 
&& pS >= soinsCap[0] - marge 
&& iS <= soinsCap[1] + marge 
&& iS >= soinsCap[1] - marge 
&& mS <= soinsCap[2] + marge  
&& mS >= soinsCap[2] - marge 
&& anS <= soinsCap[3] + marge 
&& anS >= soinsCap[3] - marge 
&& auS <= soinsCap[4] + marge 
&& auS >= soinsCap[4] - marge )  
{
soins ()  ;
}




if (coolDownAtt < millis()) {digitalWrite(ledAtt, LOW); }






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

delay(100);
}


