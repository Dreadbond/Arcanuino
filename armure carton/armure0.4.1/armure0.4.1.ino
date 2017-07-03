#include <VirtualWire.h> // inclusion de la librairie VirtualWire

const int ledPin = 13;      // led connected to digital pin 13
const int JumperEpee = 10;  //jumper pour simu épée
const int SensPlas = A0; // the piezo is connected to analog pin 0
const int SensAbG = A1;
const int SensAbD = A2;
const int SensJg = A3;
const int SensJd = A4;


const int thresPlas = 40;  // threshold value to decide when the detected sound is a knock or not
const int thresAbG = 40;
const int thresAbD = 40;
const int thresJg = 40;
const int thresJd = 40;
int coupRecu ; //char ?


bool FlagPlas = HIGH ;
bool FlagAbG = HIGH ;
bool FlagAbD = HIGH ;
bool FlagJg = HIGH ;
bool FlagJd = HIGH ;
bool FlagCoup = LOW ;


unsigned long temps ;

unsigned long GatePlas = 0 ;
unsigned long GateAbG = 0 ;
unsigned long GateAbD = 0 ;
unsigned long GateJg = 0 ;
unsigned long GateJd = 0 ;
unsigned long GateSw = 0 ;
unsigned long GateCoup = 0 ;

int CoolPlas = 100 ;
int CoolAbG = 100 ;
int CoolAbD = 100 ;
int CoolJg = 100 ;
int CoolJd = 100 ;
int CoolCoup = 100 ;
      
int puissPlas ;
int puissAbG ;
int puissAbD ;

int sensorReadPlas = 0;
int sensorReadAbG = 0;
int sensorReadAbD = 0;
int sensorReadJg = 0;
int sensorReadJd = 0;

int OldsensorReadPlas = 0;
int OldsensorReadAbG = 0;
int OldsensorReadAbD = 0;
int OldsensorReadJg = 0;
int OldsensorReadJd = 0;

int ledState = LOW;

int message;
uint8_t buf[VW_MAX_MESSAGE_LEN]; // Tableau qui va contenir le message reçu (de taille maximum VW_MAX_MESSAGE_LEN)
uint8_t buflen = VW_MAX_MESSAGE_LEN; // Taille maximum de notre tableau
    int vie = 100;



void setup() {
  pinMode(ledPin, OUTPUT); // declare the ledPin as as OUTPUT
  Serial.begin(9600);       // use the serial port
  vw_setup(2000); // initialisation de la librairie VirtualWire à 2000 bauds (note: je n'utilise pas la broche PTT)
  vw_rx_start();  // Activation de la partie réception de la librairie VirtualWire
}




void loop() {



  
  temps  = millis() ;

            if (vw_get_message(buf, &buflen)) // On copie le message, qu'il soit corrompu ou non
            {
                for (byte i = 0; i < buflen; i++) // Si il n'est pas corrompu on l'affiche via Serial
                message = int(buf[i]- '0');
                }

  if (message != 0) {
  FlagCoup = HIGH;
  GateCoup = temps + CoolCoup;
  digitalWrite(ledPin, HIGH);
  Serial.println("Coup !");
  message = 0;
  }

//if (digitalRead(JumperEpee) == HIGH) {FlagCoup = HIGH;)     //  Pour ouvrir l'épée tout le temps
FlagCoup = HIGH;
  
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////Plastron//A0////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////

  sensorReadPlas = analogRead(SensPlas);

  if (sensorReadPlas >= thresPlas)   {  GatePlas = temps + CoolPlas;  } // && temps > GatePlas

  if (GatePlas > temps) {FlagPlas = HIGH;}

  if (FlagPlas == HIGH && FlagCoup == HIGH) { 
    Serial.print("Plastron ");
    Serial.println(sensorReadPlas);
    FlagPlas = LOW; 
  }

  ////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////Avant-bras Gauche//A1//////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////
  
  sensorReadAbG = analogRead(SensAbG);

  if (sensorReadAbG >= thresAbG)   {  GateAbG = temps + CoolAbG;  } // && temps > GateAbG

  if (GateAbG > temps) {FlagAbG = HIGH;}

  if (FlagAbG == HIGH && FlagCoup == HIGH) { 
    Serial.print("Avant-bras gauche ");
    Serial.println(sensorReadAbG);
    FlagAbG = LOW; 
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////Avant-bras droit//A2////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////

  sensorReadAbD = analogRead(SensAbD);

  if (sensorReadAbD >= thresAbD)   {  GateAbD = temps + CoolAbD;  } // && temps > GateAbD

  if (GateAbD > temps) {FlagAbD = HIGH;}

  if (FlagAbD == HIGH && FlagCoup == HIGH) { 
    Serial.print("Avant-bras droit ");
    Serial.println(sensorReadAbD);
    FlagAbD = LOW; 
  }

  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////Jambe gauche /////A3////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////

  sensorReadJg = analogRead(SensJg);

  if (sensorReadJg >= thresJg)   {  GateJg = temps + CoolJg;  } // && temps > GateJg

  if (GateJg > temps) {FlagJg = HIGH;}

  if (FlagJg == HIGH && FlagCoup == HIGH) { 
    Serial.print("Jambe gauche ");
    Serial.println(sensorReadJg);
    FlagJg = LOW; 
  }

  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////Jambe droite//////A4////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////

  sensorReadJd = analogRead(SensJd);

  if (sensorReadJd >= thresJd)   {  GateJd = temps + CoolJd;  } // && temps > GateJd   Si coup : MàJ de la fenêtre d'écoute coup

  if (GateJd > temps) {FlagJd = HIGH;}       // flag haut pendant la fenêtre "coup"

  if (FlagJd == HIGH && FlagCoup == HIGH) {    // si coup reçu coincide avec coup d'épée : validé
    Serial.print("Jambe droite ");
    Serial.println(sensorReadJd);
    FlagJd = LOW; 
  }

  ////////////////////////////////////////////////////////////////////////////////////////

FlagPlas = LOW;
FlagCoup = LOW;
FlagAbG = LOW;
FlagAbD = LOW;

}
