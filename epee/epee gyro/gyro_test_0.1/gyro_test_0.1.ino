#include <Wire.h>
#include <L3G.h>

L3G gyro;

long x_data;
long y_data;
long z_data;

long arf;

bool flagxPos = HIGH ;
bool flagxNeg = HIGH ;
bool flagyPos = HIGH ;
bool flagyNeg = HIGH ;
bool flagzPos = HIGH ;
bool flagzNeg = HIGH ;

bool flagHit = LOW;
long buff[20];
int posGeste;
int i ;

unsigned long coolReset ;
unsigned long resetTime = 2000 ;

int currentGeste;
int currentMouvement[20]; // = {0, 0, 0} 
int mouvement1[3] = {5, 6, 4} ;
int mouvement2[3] = {5, 6, 5} ;
int mouvement3[3] = {3, 2, 4} ;
int mouvement4[3] = {5, 2, 4} ;
int mouvement5[3] = {6, 2, 4} ;
int mouvement6[3] = {1, 3, 4} ;

int xPos(){
  currentGeste = 1;
  coolReset = millis() + resetTime;
  flagxPos = LOW;
}

int xNeg(){
  currentGeste = 2;
  coolReset = millis() + resetTime;
  flagxNeg = LOW;
}

int yPos(){
  currentGeste = 3;
  coolReset = millis() + resetTime;
  flagyPos = LOW;
}
int yNeg(){
  currentGeste = 4;
  coolReset = millis() + resetTime;
  flagyNeg = LOW;
}
int zPos(){
  currentGeste = 5;
  coolReset = millis() + resetTime;
  flagzPos = LOW;
}
int zNeg(){
  currentGeste = 6;
  coolReset = millis() + resetTime;
  flagzNeg = LOW;
}

int posReset(){
  posGeste = 0 ;
  currentGeste = 0;
  currentMouvement[0] = 0 ;
  currentMouvement[1] = 0 ;
  currentMouvement[2] = 0 ;
  flagxPos = HIGH ;
  flagxNeg = HIGH ;
  flagyPos = HIGH ;
  flagyNeg = HIGH ;
  flagzPos = HIGH ;
  flagzNeg = HIGH ;
  }

int resetFlags(){
  flagxPos = HIGH ;
  flagxNeg = HIGH ;
  flagyPos = HIGH ;
  flagyNeg = HIGH ;
  flagzPos = HIGH ;
  flagzNeg = HIGH ;
}

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!gyro.init())
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }

  gyro.enableDefault();
}

void loop() {
  gyro.read();
/*
x_data = (int)gyro.g.x;
y_data = (int)gyro.g.y;
z_data = (int)gyro.g.z;*/

  //Serial.print("G ");
  //Serial.print("X: ");
  //Serial.println(gyro.g.x);
  //Serial.print(" Y: ");
  //Serial.println(gyro.g.y);
  //Serial.print(" Z: ");
  //Serial.println(gyro.g.z);





if(gyro.g.z <= -10000) {flagHit = HIGH;}


    if (flagHit == HIGH && gyro.g.z > -10000) { 
  i++;
  //if(gyro.g.z < 0) {gyro.g.z = gyro.g.z * -1;}
  buff[i] = gyro.g.z;   }

if(i==19)  {
  flagHit=LOW; 
  i=0; 
  
  arf = buff[2] + buff[3] + buff[4] + buff[5] + buff[6] + buff[7] + buff[8] + buff[9] + buff[10] ; 
  arf = arf + buff[11] + buff[12] + buff[13] + buff[14] + buff[15] + buff[16] + buff[17] + buff[18] + buff[19];

  /*
  Serial.println(arf);
  
  Serial.println(" ");
  Serial.println(buff[1]);
  Serial.println(buff[2]);
  Serial.println(buff[3]);
  Serial.println(buff[4]);
  Serial.println(buff[5]);
  Serial.println(buff[6]);
  Serial.println(buff[7]);
  Serial.println(buff[8]);
  Serial.println(buff[9]);
  Serial.println(buff[10]);

  Serial.println(buff[11]);
  Serial.println(buff[12]);
  Serial.println(buff[13]);
  Serial.println(buff[14]);
  Serial.println(buff[15]);
  Serial.println(buff[16]);
  Serial.println(buff[17]);
  Serial.println(buff[18]);
  Serial.println(buff[19]);
  //Serial.println(buff[20]);
  Serial.println(" ");*/
  /*
  if(arf > 40000) {
    Serial.print("Coup : deg : ");
    Serial.println(arf);}
  if(arf <= 40000) {Serial.println("Rate !");}*/
  }  

if (gyro.g.x >  10000 && flagxPos == HIGH) {resetFlags(); xPos();}
if (gyro.g.x < -10000 && flagxNeg == HIGH) {resetFlags(); xNeg();}
if (gyro.g.y >  10000 && flagyPos == HIGH) {resetFlags(); yPos();}
if (gyro.g.y < -10000 && flagyNeg == HIGH) {resetFlags(); yNeg();}
if (gyro.g.z >  10000 && flagzPos == HIGH) {resetFlags(); zPos();}
if (gyro.g.z < -10000 && flagzNeg == HIGH) {resetFlags(); zNeg();}



if (currentGeste != 0) {
   Serial.println(posGeste);
currentMouvement[posGeste] = currentGeste;
posGeste++;
}


if ( memcmp( (const void *)currentMouvement, (const void *)mouvement1, sizeof(mouvement1)) == 0) {Serial.println("qsf q65fqsf56 "); coolReset = millis();}  //sizeof(mouvement1)
if ( memcmp( (const void *)currentMouvement, (const void *)mouvement2, sizeof(mouvement2)) == 0) {Serial.println("lk tykotyjoky"); coolReset = millis();}
if ( memcmp( (const void *)currentMouvement, (const void *)mouvement3, sizeof(mouvement3)) == 0) {Serial.println("3");}
if ( memcmp( (const void *)currentMouvement, (const void *)mouvement4, sizeof(mouvement4)) == 0) {Serial.println("4");}
if ( memcmp( (const void *)currentMouvement, (const void *)mouvement5, sizeof(mouvement5)) == 0) {Serial.println("5");}
if ( memcmp( (const void *)currentMouvement, (const void *)mouvement6, sizeof(mouvement6)) == 0) {Serial.println("6");}

Serial.println(currentMouvement[0]);
Serial.println(currentMouvement[1]);
Serial.println(currentMouvement[2]);



currentGeste = 0;
if(coolReset < millis()) {posReset();}

  delay(20);  
}



