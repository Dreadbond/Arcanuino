//#include <VirtualWire.h>
#include <IRremote.h>
#include <Wire.h> 

//nrf24l01
#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI

int p ;
int i ;
int m ;
int an;
int au;

int valeursGant[8] ;

bool pFlag ;
bool iFlag ;
bool mFlag ;
bool anFlag;
bool auFlag;

//int mainPattern[5];
//int eclairPattern[] = {0, 0, 0, 1, 1};
//int feuPattern[] = {0, 1, 1, 1, 1};
//int soinsPattern[] = {1, 0, 0, 0, 0};

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

int message_moniteur = 0 ; //49 pour données

const int led_pin = 9;
const int transmit_pin = 10;
const int receive_pin = 2;
const int transmit_en_pin = 3;


const int RECV_PIN = 6;
IRrecv irrecv(RECV_PIN);
decode_results results;

bool getValue = HIGH ;
unsigned long nextGetValue = 0 ;
int refrRate = 200 ;

String selfObject = "gant" ;
String selfPlayer = ":111111" ;
String cible = "vide" ; // ou char ou 

unsigned long gateFeuPrepa ;
unsigned long gatePunchPrepa;
unsigned long gatePunch ;
unsigned long gateFeu ;
unsigned long coolEclair = 750 ;
unsigned long coolSoins = 10000 ;
bool flagEclair = HIGH ;
bool flagNova = HIGH ;
bool debug_mode = LOW ;

bool sup_punch_prepa = LOW ;
bool boule_feu_prepa = LOW ;


byte message[32] = "obj_:#gant1_reg_:x_val_:xxxxx";


typedef struct {
  char objectStru = 'g' ;
  char commande;
  int valeur;
  //String cibleStru = cible ;
  //String proprioStru = selfPlayer ;
  //String objectStru = selfObject ;
} MaStructure;
 
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////SETUP/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Mirf.cePin = 9; // Broche CE sur D9
  Mirf.csnPin = 10; // Broche CSN sur D10
  Mirf.spi = &MirfHardwareSpi; // On veut utiliser le port SPI hardware
  Mirf.init(); // Initialise la bibliothèque

  Mirf.channel = 1; // Choix du canal de communication (128 canaux disponibles, de 0 à 127)
  Mirf.payload = sizeof(MaStructure); //32; // Taille d'un message (maximum 32 octets)
  Mirf.config(); // Sauvegarde la configuration dans le module radio

  Mirf.setTADDR((byte *) "nrf02"); // Adresse de transmission
  Mirf.setRADDR((byte *) "nrf01"); // Adresse de réception
  

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
  
  Serial.begin(9600); 
  irrecv.enableIRIn(); // Start the receiver
  //irrecv.blink13(true);
  
  Serial.println("Gant V0.6 structure");
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





///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////LOOP/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

void loop() {
//boule_feu_launch(); delay(2000);
MaStructure messageStru;

if (nextGetValue < millis()) {getValue = HIGH; nextGetValue = millis() + refrRate ;} 
else {getValue = LOW; }

oldx = x;
oldy = y;
oldz = z;

valeursGant[0] = x ;
valeursGant[1] = y ;
valeursGant[2] = z ;
 
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

valeursGant[3] = p ;
valeursGant[4] = i ;
valeursGant[5] = m ;
valeursGant[6] = an ;
valeursGant[7] = au ;

if (Serial.available() > 0) {message_moniteur = Serial.read() ; Serial.println(message_moniteur);}

if (message_moniteur == 49) {debug_mode = HIGH ;} else //if (message_moniteur == 50) 
{debug_mode = LOW;}

if (debug_mode) {

     Serial.print(x);   Serial.print(" ");
     Serial.print(y);   Serial.print(" ");
     Serial.print(z);   Serial.print(" ");
     
     Serial.print(p);   
     Serial.print(" ");
     Serial.print(i);   
     Serial.print(" ");
     Serial.print(m);   
     Serial.print(" ");
     Serial.print(an);   
     Serial.print(" ");
     Serial.println(au);  
    }

///////////////////////////////////////////////////////////////////////////////////////////


  
  
  if (getValue == HIGH && debug_mode == LOW) {

    for (int i=0; i<8; i++) {
      if (debug_mode) {
        Serial.print("to_"); Serial.print(selfPlayer); Serial.print("_from_:"); Serial.print(selfObject); Serial.print("_valAdresse_:"); 
        Serial.print(i); Serial.print("_valeur_:"); Serial.println(valeursGant[i]);
      }
  
    
  
    delay(30);
    
    messageStru.commande = i + '0';//Serial.read();
    messageStru.valeur = valeursGant[i];//Serial.parseInt();
    messageStru.objectStru = 'g' ;
    
    Mirf.send((byte*) &messageStru); // On envoie le message (Strings) et strucutre
    while(Mirf.isSending()); // On attend la fin de l'envoi
  
    
    
    }
  Serial.println();
  //envoi de cible
  if (debug_mode) {Serial.print("cible_"); Serial.println(cible);}
  }

}


//while (1==1){}





/*
if (p < 1000) {pFlag = HIGH;} else {pFlag = LOW;}
if (i < 1000) {iFlag = HIGH;} else {iFlag = LOW;}
if (m < 1000) {mFlag = HIGH;} else {mFlag = LOW;}
if (an < 1000) {anFlag = HIGH;} else {anFlag = LOW;}
if (au < 1000) {auFlag = HIGH;} else {auFlag = LOW;}


if (p < 1000 && i > 1000 && m > 1000 && an <1000 && au < 1000 && gateEclair < millis()) {eclair_launch(); digitalWrite(13, HIGH); delay(500);} else {digitalWrite(13, LOW);}
if (pFlag && iFlag == LOW && mFlag == LOW && anFlag == LOW && auFlag == LOW && y > 80.00) {bouclier_launch();}
if (p > 800 && i < 800 && m < 800 && an < 800 && au < 800 && x < -80.00 && gatePunchPrepa < millis() ) {gatePunch = millis() + 2000; }
if (pFlag == LOW && iFlag == LOW && m < 1000 && an < 1000 && gateFeuPrepa < millis() ) {gateFeu = millis() + 500;}


    if (gatePunch > millis()) {sup_punch_prepa = HIGH ;  //chargement de sort (accumulation puissance, délai)
      digitalWrite(13, HIGH);
      byte messageConv = byte(4); Serial.write(messageConv);           //pour Bluetooth
      if (debug_mode) {Serial.println("Haaaaaadukun !");}
      }
    else {digitalWrite(13, LOW);}
      
    if (gateFeu > millis()) {boule_feu_prepa = HIGH; //chargement de sort (accumulation puissance, délai)
      digitalWrite(13, HIGH);
      byte messageConv = byte(5); Serial.write(messageConv);           //pour Bluetooth
      if (debug_mode) {Serial.println("Froup !");}
      }
    else {digitalWrite(13, LOW);}
    
    if (sup_punch_prepa && y > 90) {super_punch_launch(); gatePunch = millis() ; gatePunchPrepa = millis()+2000;} //lancement de sort
    if (boule_feu_prepa) {boule_feu_launch() ; gateFeu = millis() ; gateFeuPrepa = millis()+2000;}

sup_punch_prepa = LOW ;
boule_feu_prepa = LOW ;
*/
//nextValue = LOW ;
//cible = 0 ;


//delay(100);

