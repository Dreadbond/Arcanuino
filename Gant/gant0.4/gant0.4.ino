#include <VirtualWire.h>
#include <IRremote.h>
#include <Wire.h> 

int p ;
int i ;
int m ;
int an;
int au;

bool pFlag ;
bool iFlag ;
bool mFlag ;
bool anFlag;
bool auFlag;

int mainPattern[5];
int eclairPattern[] = {0, 0, 0, 1, 1};
int feuPattern[] = {0, 1, 1, 1, 1};
int soinsPattern[] = {1, 0, 0, 0, 0};

byte Version[3];
int8_t x_data;
int8_t y_data;
int8_t z_data;
byte range=0x00;
float divi=16;
float x,y,z;
int oldx, oldy, oldz ;
int diffx, diffy, diffz;
int mainx, mainy, mainz;
int diffxMax;

const int led_pin = 9;
const int transmit_pin = 10;

char mess = '0';   // https://www.arduino.cc/en/Tutorial/StringConstructors
const char *msg1 = "N";
const char *msg2 = "O";
const char *msg3 = "P";
const char *msg4 = "X";
const char *msg5 = "Y";
const char *msg6 = "Z";

const int RECV_PIN = 6;
IRrecv irrecv(RECV_PIN);
decode_results results;


int player = 4 ;
long cible ; // ou char ou 

unsigned long coolPunch ;
unsigned long coolFeu ;
unsigned long coolEclair = 750 ;
unsigned long coolSoins = 10000 ;
bool flagEclair = HIGH ;
bool flagNova = HIGH ;

bool sup_punch_prepa = LOW ;
bool boule_feu_prepa = LOW ;

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////SETUP/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  pinMode(13, OUTPUT);
  vw_setup(2000);     // initialisation de la librairie VirtualWire à 2000 bauds (note: je n'utilise pas la broche PTT)

  Wire.begin(); 
  Wire.beginTransmission(0x0A); // address of the accelerometer 
  // range settings
  Wire.write(0x22); //register address
  Wire.write(range); //can be set at"0x00""0x01""0x02""0x03", refer to Datashhet on wiki
  // low pass filter  
  Wire.write(0x20); //register address
  Wire.write(0x05); //can be set at"0x05""0x04"......"0x01""0x00", refer to Datashhet on wiki
  Wire.endTransmission();
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A6, INPUT);

  pinMode(10, OUTPUT); //émetteur hf
  pinMode(11, OUTPUT); //ground
  pinMode(12, OUTPUT); //VCC

  digitalWrite(11, LOW); 
  digitalWrite(12, HIGH);   

  vw_set_tx_pin(transmit_pin);
  //vw_set_rx_pin(receive_pin);
  //vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);       // Bits per sec

  pinMode(13, OUTPUT);
  
  Serial.begin(9600); 
  irrecv.enableIRIn(); // Start the receiver
  //irrecv.blink13(true);
  
  Serial.println("Gant V0.4");
}

void sort_eclair( ) {

  char msg[8]= "Eclair :";
  Serial.println(msg);
  //Serial.println(puissance);
  //msg[11] = puissance ;
  //msg[23] = ".";
  digitalWrite(13, HIGH); 
  vw_send((uint8_t *)msg, strlen(msg)); //strlen(msg) + x
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(13, LOW);
  //delay(1000);
  //count = count + 1;
}

void sort_soins() {

  char msg[7]= "Soins :";
  Serial.println(msg);
  //Serial.println(puissance);
  //msg[11] = puissance ;
  //msg[23] = ".";
  digitalWrite(13, HIGH); 
  vw_send((uint8_t *)msg, strlen(msg)); //strlen(msg) + x
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(13, LOW);
  //delay(1000);
  //count = count + 1;
}

void sort_feu() {

  char msg[12]= "Boule de feu";
  Serial.println(msg);
  //Serial.println(puissance);
  //msg[11] = puissance ;
  //msg[23] = ".";
  digitalWrite(13, HIGH); 
  vw_send((uint8_t *)msg, strlen(msg)); //strlen(msg) + x
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(13, LOW);
  //delay(1000);
  //count = count + 1;
}

void AccelerometerInit() 
{ 
  Wire.beginTransmission(0x0A); // address of the accelerometer 
  // reset the accelerometer 
  Wire.write(0x04); // Y data
  Wire.endTransmission(); 
  Wire.requestFrom(0x0A,1);    // request 6 bytes from slave device #2
  while(Wire.available())    // slave may send less than requested
  { 
    Version[0] = Wire.read(); // receive a byte as characte
  }  
  x_data=(int8_t)Version[0]>>2;
   
  Wire.beginTransmission(0x0A); // address of the accelerometer 
  // reset the accelerometer 
  Wire.write(0x06); // Y data
  Wire.endTransmission(); 
  Wire.requestFrom(0x0A,1);    // request 6 bytes from slave device #2
  while(Wire.available())    // slave may send less than requested
  { 
    Version[1] = Wire.read(); // receive a byte as characte
  }  
  y_data=(int8_t)Version[1]>>2;
    
  Wire.beginTransmission(0x0A); // address of the accelerometer 
  // reset the accelerometer 
  Wire.write(0x08); // Y data
  Wire.endTransmission(); 
  Wire.requestFrom(0x0A,1);    // request 6 bytes from slave device #2
   while(Wire.available())    // slave may send less than requested
  { 
    Version[2] = Wire.read(); // receive a byte as characte
  }
   z_data=(int8_t)Version[2]>>2; 
    
   x=(float)x_data/divi*100; 
   y=(float)y_data/divi*100;
   z=(float)z_data/divi*100;
}

void sendCoup() {
  digitalWrite(13, HIGH); 

  char msg1[15]= "to: {dreadbond}";
  vw_send((uint8_t *)msg1, 15); //strlen(msg) + x
  vw_wait_tx(); // Wait until the whole message is gone

  digitalWrite(13, LOW);

}



void loop() {
//sendCoup(); delay(2000);
  
oldx = x;
oldy = y;
oldz = z;
 
  switch(range)  //change the data dealing method based on the range u've set
  {
  case 0x00:divi=16;  break;
  case 0x01:divi=8;  break;
  case 0x02:divi=4;  break;
  case 0x03:divi=2;  break;
  default: Serial.println("range setting is Wrong,range:from 0to 3.Please check!");while(1); 
  }
  AccelerometerInit(); 




p = analogRead(A0);
i = analogRead(A1);
m = analogRead(A2);
an = analogRead(A3);
au = analogRead(A6);

/*
     Serial.print(x);   Serial.print(" ");
     Serial.print(y);   Serial.print(" ");
     Serial.print(z);   Serial.println(" ");
     */
     Serial.print(p);   
     Serial.print(" ");
     Serial.print(i);   
     Serial.print(" ");
     Serial.print(m);   
     Serial.print(" ");
     Serial.print(an);   
     Serial.print(" ");
     Serial.println(au);  
/*
p = mainPattern[0];
i = mainPattern[1];
m = mainPattern[2];
an = mainPattern[3];
au = mainPattern[4];*/

///////////////////////////////////////////////////////////////////////////////////////////

if (irrecv.decode(&results)) {
    irrecv.resume(); // Receive the next value
   // coolCible = millis() + 1000 ;
  }
    cible = results.value ;/*
    Serial.print("Cible : ");
Serial.println(cible);
/*
if (irrecv.decode(&results)) { irrecv.resume(); } // Receive the next value

cible = results.value ;
Serial.println(cible);*/

if (p < 850 || i < 850 || m < 850 || an < 850 || au < 850 ){  digitalWrite(13, HIGH);  }
else {  digitalWrite(13, LOW);}


if (p < 1000) {pFlag = HIGH;} else {pFlag = LOW;}
if (i < 1000) {iFlag = HIGH;} else {iFlag = LOW;}
if (m < 1000) {mFlag = HIGH;} else {mFlag = LOW;}
if (an < 1000) {anFlag = HIGH;} else {anFlag = LOW;}
if (au < 1000) {auFlag = HIGH;} else {auFlag = LOW;}


if (pFlag == LOW && iFlag == LOW && mFlag == LOW && anFlag && auFlag ) {Serial.println("Eclair");}
if (pFlag && iFlag == LOW && mFlag == LOW && anFlag == LOW && auFlag == LOW ) {Serial.println("Bouclier");}
if (iFlag == HIGH && mFlag == HIGH && anFlag == HIGH && auFlag == HIGH && x < -50.00) {coolPunch = millis() + 2000; Serial.println("Haaaaaadukun !");}
if (pFlag == LOW && iFlag == HIGH && m < 1000 && an < 1000 && auFlag == LOW && y > 80.00 ) {coolFeu = millis() + 2000; Serial.println("Froum !");}

if (coolPunch > millis()) {sup_punch_prepa = HIGH ;}
if (coolFeu > millis()) {boule_feu_prepa = HIGH;}

if (boule_feu_prepa && y > 50) {Serial.println("Boule de feu !"); coolPunch = millis();}
if (sup_punch_prepa && y > 90) {Serial.println("Super punch !"); coolPunch = millis();}


if (mess != '0') { 
  //int len = 0 ; //length(mess) ;
  Serial.print("Message : ");
  Serial.println(mess);
  vw_send((uint8_t *)mess, 1) ;
  vw_wait_tx();
  }


mess = '0' ;
cible = 0 ;


delay(100);
}
