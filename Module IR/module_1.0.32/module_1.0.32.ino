#include <IRremote.h>

int RECV_PIN = 11;   
IRrecv irrecv(RECV_PIN);
IRsend irsend;          // pour la Led IR = toujours sortie 3PWM

// pour la Led IR = toujours sortie 3PWM
/*
const int buttonPin1 = 4;     // the number of the pushbutton pin
const int buttonPin2 = 5;
const int buttonPin3 = 6;
const int buttonPin4 = 7;*/
const int healthLED = 10 ;
const int ledT =  13;      // Led témoin (réception)
int intenHL = 0 ;          //intensité healthLed


unsigned long temps = 0;     //horloge
unsigned long Cible = 0;     //temps-cible led
unsigned long Cible1 = 0;    // tc sort 1
unsigned long Cible2 = 0;
unsigned long Cible3 = 0;
const long inertie = 200 ;   // cooldown led 13
const long cooldown1 = 200 ;
const long cooldown2 = 7000 ;

float health = 100 ;
float degFinaux = 0 ;
int degHealth = 0 ;
int degDeg = 0 ;
float degDef = 1 ;
int message = 0 ;
int Mort = 0 ;
String messagestr ;

int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
/*
int state = 0;
int flag = 0;        // make sure that you return the state only once
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
bool attaqueState;
bool defenseState;
bool soinsState;

const int ledAtt=5;
const int ledAtt2=6;
const int ledDef=7;
const int ledSoi=8;
const int Led13=13;

const int butCal = 4 ;
bool butCalState ;

const int butPin = 2 ;
bool butState ;
int butCount = 0 ;

int marge = 10;   //5, bien 10 gant marron, 7 mitaine






decode_results results;

void setup() {
  Serial.begin(9600);

  pinMode(healthLED, OUTPUT);  
  pinMode(ledT, OUTPUT);
/*
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);*/

pinMode(ledAtt, OUTPUT);
pinMode(ledAtt2, OUTPUT);
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

  
  irrecv.enableIRIn(); // Start the receiver
  health = 100 ; 
}


void attaqueSend() {
        irsend.sendSony(0xa10, 12);
        Cible1 = temps + cooldown1 ;   // heure pour réutiliser le sort = instant T + cooldown
        irrecv.enableIRIn();  
        digitalWrite(ledAtt, HIGH);
        Serial.println("Attaque !");            
        }
        
void attaque2Send() {
        irsend.sendSony(0xb10, 12);
        Cible2 = temps + cooldown2 ;   // heure pour réutiliser le sort = instant T + cooldown
        irrecv.enableIRIn();  
        Serial.println("Grosse attaque !");            
        }
        
void attaqueRcv () {
    degDeg = -5 ;
    }

void attaque2Rcv() {
    degDeg = -15 ;
    }
/*
int defenseRcv(int val) {
switch (val) {
  case 1:
    degDef = 0.5 ;
    break;
  case 2:
    degDef = 1 ;
    break;
    }
  }*/
void defenseRcv() {
    degDef = 0.5 ;
    Serial.println("Defense ");
    digitalWrite(ledDef, HIGH);
   // coolDownDef = temps +200;
    }

void soinsRcv() {
    degHealth = 3 ;
    Cible3 = temps + cooldown1 ;
    Serial.print("Soins ");
    digitalWrite(ledSoi, HIGH);
  //  coolDownSoi = temps +200;
    }

void mort() {
       //health = 0 ;  
       analogWrite(healthLED, 0);
       Mort = Mort + 1 ;
       Serial.print("Player 1 est mort ");
       Serial.print(Mort);
       Serial.println(" fois.");

delay (5000) ;    //nope
health = 100 ;
}





void dump(decode_results *results) {
  // Dumps out the decode_results structure.
  // Call this after IRrecv::decode()
  int count = results->rawlen;

  
  if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
  }
  else if (results->decode_type == RC5) {
    Serial.print("Decoded RC5: ");
  }
  Serial.print(results->value, HEX);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");
  for (int i = 1; i < count; i++) {
    if (i & 1) {
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    }
    else {
      Serial.write('-');
      Serial.print((unsigned long) results->rawbuf[i]*USECPERTICK, DEC);
    }
    Serial.print(" ");
  }
  Serial.println();
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

/*
Serial.print(pS);
Serial.print("p ");
Serial.print(iS);
Serial.print("i ");
Serial.print(mS);
Serial.print("m ");
Serial.print(anS);
Serial.print("an ");
Serial.print(auS);
Serial.println("au ");*/

//if (butCalState == HIGH) {calibrage();}
if (butState ==   HIGH) {butCount ++ ;






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
attaqueSend()  ;
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
&& temps > Cible1  
)  
{
attaqueSend()  ;
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
&& temps > Cible1 
)  
{
attaqueSend()  ;
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
defenseRcv();
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
defenseRcv();
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
defenseRcv();
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
&& auS >= soinsCap[4] - marge 
&& temps > Cible3)  
{
soinsRcv()  ;
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
&& auS >= soinsCapb[4] - marge 
&& temps > Cible3)  
{
soinsRcv()  ;
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
&& auS >= soinsCapt[4] - marge 
&& temps > Cible3 )  
{
soinsRcv()  ;
}


delay(100);
digitalWrite(ledSoi, LOW);
digitalWrite(ledDef, LOW);
digitalWrite(ledAtt, LOW);
digitalWrite(Led13, LOW);






    intenHL = 2.55 * health / 2 ;
    intenHL = constrain(intenHL, 0, 255);
    analogWrite(healthLED, intenHL) ;

///////////////////////////////////////////////////////////////
////////////////////////////BOUTONS////////////////////////////
///////////////////////////////////////////////////////////////
  /*
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  
  if (buttonState1 == HIGH && temps > Cible1 ) {attaqueSend();}           // bouton 1 : attaque canalisée
  if (buttonState2 == HIGH && temps > Cible2 ) {attaque2Send();}          // bouton 2 : grosse attaque
  if (buttonState3 == HIGH ) {defenseRcv(1);}                             // bouton 3 : réduit les dégâts
        else if (buttonState3 == LOW) {defenseRcv(2);}
  if (buttonState4 == HIGH && temps > Cible3 ) {soinsRcv();}              // bouton 4 : soins
*/
     
///////////////////////////////////////////////////////////////
/////////////////////////RECEPTION/////////////////////////////
///////////////////////////////////////////////////////////////

  if (irrecv.decode(&results)) {
    digitalWrite(ledT, HIGH);
    Cible = temps + inertie ; //si quelque chose, cible marque le temps et anticipe (temps cible) pour la Led 13
   
    //dump(&results);
    irrecv.resume(); // Receive the next value

    message = int(results.value);
    //Serial.println(message);
    }
       if (message == 2576 && health > 0) {attaqueRcv();}   //a10 2576 : grosse attaque
       if (message == 2832 && health > 0) {attaque2Rcv();}    //b10 2832 : dégâts 

///////////////////////////////////////////////////////////////
/////////////////////////////SANTE/////////////////////////////
///////////////////////////////////////////////////////////////

       degFinaux = degDef * degDeg + degHealth  ;
       health = health + degFinaux ;
         if (degFinaux != 0 ) {Serial.println(health);}
         if (health <= 0 ) { mort();}
         if (health > 100) {
         Serial.println("Vie au maximum.") ; 
         health = 100 ;
}

    
degFinaux = 0 ;
degHealth = 0 ;
degDeg = 0 ;
degDef = 1 ;
message = 0;
if ( temps >= Cible){ digitalWrite(ledT, LOW);}  //si temps actu sup ou égal cible, stop lumière


}
