#include <RFID.h>

//NRF24L01
#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI
char *IDobjet = "nrf07";
char *toIDobjet = "nrf01" ;     //ID de l'objet qui est sensé recevoir

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN,RST_PIN);
int serNum[5];
int cards[5] =   {136,4,91,233,62}  ;

int wifi[6] =   {136,4,91,233,62, 0}  ;
int telephone[6] =   {136,4,46,233,75, 0}  ;
int maison[6] =   {136,4,56,233,93, 0}  ;
int chevron[6] =   {136,4,81,233,52, 0}  ;
int reveil[6] =   {136,4,86,233,51, 0} ;
int sms[6] =   {136,4,51,233,86, 0}  ;
int bluetooth[6] =   {136,4,61,233,88, 0}  ;
int navigation[6] =   {136,4,76,233,41, 0}  ;
int power[6] =   {136,4,66,233,39, 0}  ;
int airplane[6] =   {136,4,71,233,34, 0}  ;

bool access = false;
unsigned long sscontact = 0 ;
/*
* Read a card using a mfrc522 reader on your SPI interface
* Pin layout should be as follows (on Arduino Uno):
* MOSI: Pin 11 / ICSP-4
* MISO: Pin 12 / ICSP-1
* SCK: Pin 13 / ISCP-3
* SS/SDA: Pin 10
* RST: Pin 9
*/

int vie = 0 ;
int mana = 0 ;
int ennVie = 0 ;
int ennMana = 0;
int rssi ; 

byte message_in_com ;
char message_out_rf[0] ;


bool debug_mode = HIGH;

//Message factory
char commande ;
int valeur ;
bool sendMessTicket = LOW ;

typedef struct {
  char objectStru = 'm' ;   //Grappemain
  char commande;
  int valeur;
} actionStruct;

void setup() {
    pinMode(A0, INPUT);
    Serial.begin(9600);  // Debugging only
    Serial.println("Grappemain HF 0.1");

    pinMode(A5, INPUT); //digital
    pinMode(A4, INPUT); //RSSI
    pinMode(A3, OUTPUT);//5V

    digitalWrite(A5, LOW);
    digitalWrite(A3, HIGH);

    Mirf.cePin = 8; // Broche CE sur D9
    Mirf.csnPin = 7; // Broche CSN sur D10
    Mirf.spi = &MirfHardwareSpi; // On veut utiliser le port SPI hardware
    Mirf.init(); // Initialise la bibliothèque
  
    Mirf.channel = 1; // Choix du canal de communication (128 canaux disponibles, de 0 à 127)
    Mirf.payload = sizeof(actionStruct); //32; // Taille d'un message (maximum 32 octets)
    Mirf.config(); // Sauvegarde la configuration dans le module radio
  
    Mirf.setTADDR((byte *) toIDobjet);//toIDobjet); "nrf02"); // Adresse de transmission
    Mirf.setRADDR((byte *) IDobjet);//IDobjet); //"nrf01"); // Adresse de réception

    SPI.begin();
    rfid.init();
}

void loop() {
actionStruct messageStru;


  if(sscontact < millis()) {
    if(rfid.isCard()){  //Serial.print("qdsqsd");
        if(rfid.readCardSerial()){
            /*
            Serial.print(rfid.serNum[0]);
            Serial.print(" ");
            Serial.print(rfid.serNum[1]);
            Serial.print(" ");
            Serial.print(rfid.serNum[2]);
            Serial.print(" ");
            Serial.print(rfid.serNum[3]);
            Serial.print(" ");
            Serial.print(rfid.serNum[4]);
            Serial.println("");*/
            
            //for(int x = 0; x < sizeof(cards); x++){

              for(int i = 0; i < 5; i++ ){
                  if(rfid.serNum[i] == wifi[i]) { wifi[5]++ ;} 
                  if(rfid.serNum[i] == telephone[i]) {telephone[5]++ ;} 
                  if(rfid.serNum[i] == maison[i]) { maison[5]++ ;}
                  if(rfid.serNum[i] == chevron[i]) { chevron[5]++ ;} 
                  if(rfid.serNum[i] == reveil[i]) { reveil[5]++ ;} 
                  
                  if(rfid.serNum[i] == sms[i]) { sms[5]++ ;} 
                  if(rfid.serNum[i] == bluetooth[i]) { bluetooth[5]++ ;} 
                  if(rfid.serNum[i] == navigation[i]) { navigation[5]++ ;} 
                  if(rfid.serNum[i] == power[i]) { power[5]++ ;} 
                  if(rfid.serNum[i] == airplane[i]) { airplane[5]++ ;} 

                  /*
                  Serial.print(i);
                  Serial.print(" ");
                  Serial.print(rfid.serNum[i]);
                  Serial.print(" ");
                  Serial.println(wifi[i]);*/
              }
              String messCarte = "?";
              
              if (wifi[5] >= 5)      {sendMessTicket=HIGH; commande='s'; valeur=10;}        //Borne de soins
              if (telephone[5] >= 5) {sendMessTicket=HIGH; commande='s'; valeur=20; }       //Amulette
              if (maison[5] >= 5)    {sendMessTicket=HIGH; commande='s'; valeur=30; }       //Red key
              if (chevron[5] >= 5)   {sendMessTicket=HIGH; commande='s'; valeur=40; }       //BFG
              if (reveil[5] >= 5)    {sendMessTicket=HIGH; commande='s'; valeur=50; }       //Coffre

              if (sms[5] >= 5)       {sendMessTicket=HIGH; commande='s'; valeur=60; }
              if (bluetooth[5] >= 5) {sendMessTicket=HIGH; commande='s'; valeur=70; }
              if (navigation[5] >= 5){sendMessTicket=HIGH; commande='s'; valeur=80; }
              if (power[5] >= 5)     {sendMessTicket=HIGH; commande='s'; valeur=90; }       //Grimoire
              if (airplane[5] >= 5)  {sendMessTicket=HIGH; commande='s'; valeur=100; }      //Epée
            //}

              Serial.println(messCarte) ;
        }
    wifi[5] = 0 ;
    telephone[5] = 0 ;
    maison[5] = 0 ;
    chevron[5] = 0 ;
    sms[5] = 0 ;
    
    reveil[5] = 0 ;
    bluetooth[5] = 0 ;
    navigation[5] = 0 ;
    power[5] = 0 ;
    airplane[5] = 0 ;
    //rfid.halt();
    }
  sscontact = millis() + 200 ;
  }
  if (sendMessTicket) {
        messageStru.commande = commande ;     //s : scanne
        messageStru.valeur = valeur ;         //valeur : cible
        
        Mirf.send((byte*) &messageStru); // On envoie le message (Strings) et strucutre
        while(Mirf.isSending()); // On attend la fin de l'envoi
        commande = ' ';
        valeur = 0 ;
        sendMessTicket=LOW;
  }


}
