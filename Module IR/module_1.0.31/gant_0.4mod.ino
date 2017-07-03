/*
//#include <Firmata.h>
#include <IRremote.h>
IRsend irsend;       //pin 3 pour émetteur
*/

int pS ;
int iS ;
int mS ;
int anS ;
int auS ;
int minp = 0;
int maxp = 1023 ;
int mini = 0;
int maxi = 1023;
int minm = 0;
int maxm = 1023;
int minan = 0;
int maxan = 1023;
int minau = 0;
int maxau = 1023;
int attaqueCap[5] ;
int defenseCap[5] ;
int soinsCap[5] ;
int attaqueCapb[5] ;
int defenseCapb[5] ;
int soinsCapb[5] ;
int attaqueCapt[5] ;
int defenseCapt[5] ;
int soinsCapt[5] ;
int coolDownAtt;
int coolDownDef;
int coolDownSoi;
unsigned long temps;  
bool attaqueState;
bool defenseState;
bool soinsState;

const int ledAtt=5;
const int ledDef=6;
const int ledSoi=7;
const int Led13=13;

const int butCal = 4 ;
bool butCalState ;

const int butPin = 2 ;
bool butState ;
int butCount = 0 ;

int marge = 10;   //5, bien







/*
void calibrage() {
    while (millis() < 1500) {
digitalWrite(Led13, HIGH);        
pS = analogRead(0);
iS = analogRead(1);
mS = analogRead(2);
anS = analogRead(3);
auS = analogRead(4);
if (pS < maxp) { maxp = pS ;}
if (pS > minp) { minp = pS ;}
if (iS < maxi) { maxi = iS ;}
if (iS > mini) { mini = iS ;}
if (mS < maxm) { maxm = mS ;}
if (mS > minm) { minm = mS ;}
if (anS < maxan) { maxan = anS ;}
if (anS > minan) { minan = anS ;}
if (auS < maxau) { maxau = auS ;}
if (auS > minau) { minau = auS ;}

  }
  digitalWrite(Led13, LOW);
}*/

void attaque () {
  Serial.println("Attaque !");
  digitalWrite(ledAtt, HIGH);
  coolDownAtt = temps +200;
}

void defense () {
  Serial.println("Defense !");
  digitalWrite(ledDef, HIGH);
  coolDownDef = temps +200;
}

void soins () {
  Serial.println("Soins !");
  digitalWrite(ledSoi, HIGH);
  coolDownSoi = temps +200;
}










void setup() {
  
Serial.begin(9600);
pinMode(ledAtt, OUTPUT);
pinMode(ledDef, OUTPUT);
pinMode(ledSoi, OUTPUT);
pinMode(butCal, INPUT);
pinMode(butPin, INPUT);
pinMode(Led13, OUTPUT);

delay (100);
digitalWrite(ledAtt, HIGH);
delay (100);
digitalWrite(ledDef, HIGH);
delay (100);
digitalWrite(ledSoi, HIGH);
delay (100);
digitalWrite(Led13, HIGH);
delay (100);
digitalWrite(ledSoi, LOW);
digitalWrite(ledDef, LOW);
digitalWrite(ledAtt, LOW);
digitalWrite(Led13, LOW);


}

void loop() {
temps = millis() ;


    while (millis() < 4000 && millis() > 500) { 
pS = analogRead(1);
iS = analogRead(2);
mS = analogRead(3);
anS = analogRead(4);
auS = analogRead(5);
if (pS < maxp) { maxp = pS ;}
if (pS > minp) { minp = pS ;}
if (iS < maxi) { maxi = iS ;}
if (iS > mini) { mini = iS ;}
if (mS < maxm) { maxm = mS ;}
if (mS > minm) { minm = mS ;}
if (anS < maxan) { maxan = anS ;}
if (anS > minan) { minan = anS ;}
if (auS < maxau) { maxau = auS ;}
if (auS > minau) { minau = auS ;}

Serial.print(maxp);
Serial.print(" ");
Serial.print(maxi);
Serial.print(" ");
Serial.print(maxm);
Serial.print(" ");
Serial.print(maxan);
Serial.print(" ");
Serial.print(maxau);
Serial.println(" ");  
Serial.print(minp);
Serial.print(" ");
Serial.print(mini);
Serial.print(" ");
Serial.print(minm);
Serial.print(" ");
Serial.print(minan);
Serial.print(" ");
Serial.print(minau);
Serial.println(" ");  
  }


pS = analogRead(A1);
pS = map (pS, minp, maxp, 0, 100);

iS = analogRead(A2);
iS = map (iS, mini, maxi, 0, 100);

mS = analogRead(A3);
mS = map (mS, minm, maxm, 0, 100);
delay(10);
anS = analogRead(A4);
anS = map (anS, minan, maxan, 0, 100);

auS = analogRead(A5);
auS = map (auS, minau, maxau, 0, 100);


butState = digitalRead(butPin);
butCalState = digitalRead(butCal);


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

//if (butCalState == HIGH) {calibrage();}
if (butState ==   LOW) {butCount ++ ;






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
    case 4:
digitalWrite(Led13, HIGH);
digitalWrite(ledAtt, HIGH);
attaqueCapb[0] = pS ;
attaqueCapb[1] = iS ;
attaqueCapb[2] = mS ;
attaqueCapb[3] = anS ;
attaqueCapb[4] = auS ;
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
    case 7:
digitalWrite(Led13, HIGH);
digitalWrite(ledAtt, HIGH);
attaqueCapt[0] = pS ;
attaqueCapt[1] = iS ;
attaqueCapt[2] = mS ;
attaqueCapt[3] = anS ;
attaqueCapt[4] = auS ;
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
  case 5:
digitalWrite(Led13, HIGH);
digitalWrite(ledDef, HIGH);
defenseCapb[0] = pS ;
defenseCapb[1] = iS ;
defenseCapb[2] = mS ;
defenseCapb[3] = anS ;
defenseCapb[4] = auS ;
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
    case 8:
digitalWrite(Led13, HIGH);
digitalWrite(ledDef, HIGH);
defenseCapt[0] = pS ;
defenseCapt[1] = iS ;
defenseCapt[2] = mS ;
defenseCapt[3] = anS ;
defenseCapt[4] = auS ;
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
  case 6:
digitalWrite(Led13, HIGH);
digitalWrite(ledSoi, HIGH);
soinsCapb[0] = pS ;
soinsCapb[1] = iS ;
soinsCapb[2] = mS ;
soinsCapb[3] = anS ;
soinsCapb[4] = auS ;
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
    case 9:
digitalWrite(Led13, HIGH);
digitalWrite(ledSoi, HIGH);
soinsCapt[0] = pS ;
soinsCapt[1] = iS ;
soinsCapt[2] = mS ;
soinsCapt[3] = anS ;
soinsCapt[4] = auS ;
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
}
}

if (butCount >= 9) {butCount = 0;} 





if (pS <= attaqueCap[0] + marge 
&& pS >= attaqueCap[0] - marge 
&& iS <= attaqueCap[1] + marge 
&& iS >= attaqueCap[1] - marge 
&& mS <= attaqueCap[2] + marge  
&& mS >= attaqueCap[2] - marge 
&& anS <= attaqueCap[3] + marge 
&& anS >= attaqueCap[3] - marge 
&& auS <= attaqueCap[4] + marge 
&& auS >= attaqueCap[4] - marge 
)  
{
attaque ()  ;
}
if (pS <= attaqueCapb[0] + marge 
&& pS >= attaqueCapb[0] - marge 
&& iS <= attaqueCapb[1] + marge 
&& iS >= attaqueCapb[1] - marge 
&& mS <= attaqueCapb[2] + marge  
&& mS >= attaqueCapb[2] - marge 
&& anS <= attaqueCapb[3] + marge 
&& anS >= attaqueCapb[3] - marge 
&& auS <= attaqueCapb[4] + marge 
&& auS >= attaqueCapb[4] - marge 
)  
{
attaque ()  ;
}
if (pS <= attaqueCapt[0] + marge 
&& pS >= attaqueCapt[0] - marge 
&& iS <= attaqueCapt[1] + marge 
&& iS >= attaqueCapt[1] - marge 
&& mS <= attaqueCapt[2] + marge  
&& mS >= attaqueCapt[2] - marge 
&& anS <= attaqueCapt[3] + marge 
&& anS >= attaqueCapt[3] - marge 
&& auS <= attaqueCapt[4] + marge 
&& auS >= attaqueCapt[4] - marge 
)  
{
attaque ()  ;
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
if (pS <= defenseCapb[0] + marge 
&& pS >= defenseCapb[0] - marge 
&& iS <= defenseCapb[1] + marge 
&& iS >= defenseCapb[1] - marge 
&& mS <= defenseCapb[2] + marge  
&& mS >= defenseCapb[2] - marge 
&& anS <= defenseCapb[3] + marge 
&& anS >= defenseCapb[3] - marge 
&& auS <= defenseCapb[4] + marge 
&& auS >= defenseCapb[4] - marge )  
{
defense ();
}
if (pS <= defenseCapt[0] + marge 
&& pS >= defenseCapt[0] - marge 
&& iS <= defenseCapt[1] + marge 
&& iS >= defenseCapt[1] - marge 
&& mS <= defenseCapt[2] + marge  
&& mS >= defenseCapt[2] - marge 
&& anS <= defenseCapt[3] + marge 
&& anS >= defenseCapt[3] - marge 
&& auS <= defenseCapt[4] + marge 
&& auS >= defenseCapt[4] - marge )  
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
if (pS <= soinsCapb[0] + marge 
&& pS >= soinsCapb[0] - marge 
&& iS <= soinsCapb[1] + marge 
&& iS >= soinsCapb[1] - marge 
&& mS <= soinsCapb[2] + marge  
&& mS >= soinsCapb[2] - marge 
&& anS <= soinsCapb[3] + marge 
&& anS >= soinsCapb[3] - marge 
&& auS <= soinsCapb[4] + marge 
&& auS >= soinsCapb[4] - marge )  
{
soins ()  ;
}
if (pS <= soinsCapt[0] + marge 
&& pS >= soinsCapt[0] - marge 
&& iS <= soinsCapt[1] + marge 
&& iS >= soinsCapt[1] - marge 
&& mS <= soinsCapt[2] + marge  
&& mS >= soinsCapt[2] - marge 
&& anS <= soinsCapt[3] + marge 
&& anS >= soinsCapt[3] - marge 
&& auS <= soinsCapt[4] + marge 
&& auS >= soinsCapt[4] - marge )  
{
soins ()  ;
}




//if (coolDownAtt < millis()) {digitalWrite(ledAtt, LOW); }








delay(100);
digitalWrite(ledSoi, LOW);
digitalWrite(ledDef, LOW);
digitalWrite(ledAtt, LOW);
digitalWrite(Led13, LOW);
}


