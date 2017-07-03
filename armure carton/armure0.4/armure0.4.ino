#include <VirtualWire.h> // inclusion de la librairie VirtualWire

const int ledPin = 13;      // led connected to digital pin 13
const int SensPlas = A0; // the piezo is connected to analog pin 0
const int SensAbG = A1;
const int SensAbD = A2;
const int thresPlas = 40;  // threshold value to decide when the detected sound is a knock or not
const int thresAbG = 40;
const int thresAbD = 40;
const int thresSw = 40;
int coupRecu ; //char ?


bool FlagPlas = HIGH ;
bool FlagAbG = HIGH ;
bool FlagAbD = HIGH ;
bool FlagSw = HIGH ;
bool FlagCoup = LOW ;


unsigned long temps ;

unsigned long GatePlas = 0 ;
unsigned long GateAbG = 0 ;
unsigned long GateAbD = 0 ;
unsigned long GateSw = 0 ;
unsigned long GateCoup = 0 ;

unsigned long CoolPlas = 200 ;
unsigned long CoolAbG = 200 ;
unsigned long CoolAbD = 200 ;
unsigned long CoolSw = 50 ;
unsigned long CoolCoup = 100 ;
      
int puissPlas ;
int puissAbG ;
int puissAbD ;
int puissSw ;

int sensorReadPlas = 0;
int sensorReadAbG = 0;
int sensorReadAbD = 0;
int sensorReadSw = 0;

int OldsensorReadPlas = 0;
int OldsensorReadAbG = 0;
int OldsensorReadAbD = 0;
int OldsensorReadSw = 0;

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

       //if (vw_wait_rx_max(200)) // Si un message est reçu dans les 200ms qui viennent
        //{
            if (vw_get_message(buf, &buflen)) // On copie le message, qu'il soit corrompu ou non
            {
                //Serial.print("RX : ");
                for (byte i = 0; i < buflen; i++) // Si il n'est pas corrompu on l'affiche via Serial
                message = int(buf[i]- '0');
                //Serial.print(message);   //Conversion ASCII des chiffres 0-9
                //Serial.print(buf);   //Conversion ASCII
                 {
                 

                 }
                 //Serial.println("");
                }

           //  if (message != 0) {Serial.println("Ok.");}
        /*    vie = actions(message);
            Serial.print("Vie : ");
            Serial.println(vie);*/
        //}
            


  if (message != 0) {
  FlagCoup = HIGH;
  GateCoup = temps + CoolCoup;
  digitalWrite(ledPin, HIGH);
  Serial.println("Coup !");
  message = 0;
  }
  
  if (GateCoup < temps) {
    FlagCoup = LOW ;
    digitalWrite(ledPin, LOW);
  } 

//FlagCoup = HIGH ;   //  Pour simuler l'épée
  

  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////Arme///A3///////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////

  /*

    if(analogRead(SensSw) != 0) {sensorReadSw = analogRead(SensSw);}


    if (sensorReadSw >= thresSw && FlagSw == HIGH) {
      Serial.print("Epee ");
      Serial.println(sensorReadSw);
      FlagSw = LOW ;
      GateSw = temps + CoolSw ;
    }

    if (GateSw < temps) {FlagSw = HIGH ;}
  */

  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////Torse/////A0////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////

  sensorReadPlas = analogRead(SensPlas);

  if (sensorReadPlas >= thresPlas && temps > GatePlas)   {  FlagPlas = HIGH;  }
  
  if (FlagPlas == HIGH && FlagCoup == HIGH) { 
    Serial.print("Avant-bras Plastron ");
    Serial.println(sensorReadPlas);
    
   GatePlas = temps + CoolPlas ;
    
  }
FlagPlas = LOW;

  ////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////Avant-bras Gauche//A1//////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////


  sensorReadAbG = analogRead(SensAbG);

  if (sensorReadAbG >= thresAbG && temps > GateAbG)   {  FlagAbG = HIGH;  }
  
  if (FlagAbG == HIGH && FlagCoup == HIGH) { //&& FlagCoup == HIGH
    Serial.print("Avant-bras Gauche ");
    Serial.println(sensorReadAbG);
    
   GateAbG = temps + CoolAbG ;
   
  }
  
FlagAbG = LOW;

  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////Avant-bras droit//A2///////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////



  sensorReadAbD = analogRead(SensAbD);

  if (sensorReadAbD >= thresAbD )   {  GateAbD = temps + CoolAbD ;  


  if (GateAbD > temps) {FlagAbD = HIGH;}
  else {FlagAbD = LOW;}

}
  
  if (FlagAbD == HIGH && FlagCoup == HIGH) { //&& FlagCoup == HIGH
    Serial.print("Avant-bras Droit ");
    Serial.println(sensorReadAbD);
    
   //GateAbD = temps + CoolAbD ;
   FlagAbD = LOW;

  }  
}
