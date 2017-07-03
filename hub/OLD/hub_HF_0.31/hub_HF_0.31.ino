/**
 * Exemple de code pour la bibliothèque Mirf – Serveur d'envoi de structure
 */
#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI
#include <stdlib.h>
#include <IRremote.h>

IRsend irsend;

String AEnvoyer ;   //Alarik par défaut
unsigned long tagGate = 0 ;

String joueurID = ":111111" ;
//String objetID = "ohub1"; //tag unique de l'objet
String cibleID = ":vide" ;

typedef struct{
  char objectStru = 'g' ;
  char action = 'v' ;
    char commandeX = 'x' ;
  int valeurX;
    char commandeY = 'y' ;
  int valeurY;
    char commandeZ = 'z' ;
  int valeurZ;

    char commandePouce = 'p';
  int valeurPouce;
    char commandeIndex = 'i' ;
  int valeurIndex;
    char commandeMajeur = 'm' ;
  int valeurMajeur;
    char commandeAnnulaire = 'a' ;
  int valeurAnnulaire;
    char commandeAuriculaire = 'o' ;
  int valeurAuriculaire;
} infosGantStruct ;

typedef struct { //à dégager
  char commande ;
  int  valeur ;
} envoiNeopixel;

typedef struct { //à dégager
  char objet ;
  char action; //char action;
  int valeur;
} MaStructure;

char *IDobjet = "nrf01" ; //hub
char *toIDobjetSlot2 = "nrf02" ;  //flingue
char *toIDobjetSlot3 = "nrf03" ;  //brassard
char *toIDobjetSlot4 = "nrf04" ;  //gant
char *toIDobjetSlot5 = "nrf05" ;  //WizarBlast
char *toIDobjetSlot6 = "nrf06" ;  //Piquemord
char *toIDobjetSlot7 = "nrf07" ;  //Grappemain
char *toIDobjetSlot8 = "nrf08" ;  //Grimoire


int vieSelf ;
int wizarSelf ;
int vieCible ;
int wizarCible ;

//////////////////////////////Objet : Gant Arcanique slot 4
//////////////////////////////////////////
struct gantArcanique{
bool equipe = HIGH ;
int valeursGant[8] ;
  
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

bool flagEclair ;
bool flagNova ;
bool flagTraitDeFeu = HIGH ;


  void T2FchargeFB() {
        int messTest = 10;
        Mirf.setTADDR((byte *) toIDobjetSlot4);
        Mirf.send((byte*) &messTest);
        while(Mirf.isSending());
  }
  
  void traitDeFeuLaunch() {
    Serial.println("Trait de feu !");
        int messTest = 11;
        Mirf.setTADDR((byte *) toIDobjetSlot4);
        Mirf.send((byte*) &messTest);
        while(Mirf.isSending());
    }
  
  void traitDeFeuCancel() {
    Serial.println("Trait de feu stop");
        int messTest = 12;
        Mirf.setTADDR((byte *) toIDobjetSlot4);
        Mirf.send((byte*) &messTest);
        while(Mirf.isSending());
    }
} ;
//////////////////////////////Objet : flingue slot 3
/////////////////////////////////////////////


struct flingue{
  int munitions = 20 ;
  bool gachetteToken;
  bool rechargeToken;
  bool equipe=HIGH;
  
    void rechargeFB() {
        int messTest = 1;
        Mirf.setTADDR((byte *) toIDobjetSlot2);//IDobjet);  // "nrf01"); // Adresse de transmission
        Mirf.send((byte*) &messTest); // On envoie le message (Strings) et strucutre
        while(Mirf.isSending()); // On attend la fin de l'envoi
  }
  void gachetteFB() {
        int messTest = 1;
        Mirf.setTADDR((byte *) toIDobjetSlot2);//IDobjet);  // "nrf01"); // Adresse de transmission
        Mirf.send((byte*) &messTest); // On envoie le message (Strings) et strucutre
        while(Mirf.isSending()); // On attend la fin de l'envoi
  }
  
  void cibleTrueFB() {
        int messTest = 2;
        Mirf.setTADDR((byte *) toIDobjetSlot2);//IDobjet);  // "nrf01"); // Adresse de transmission
        Mirf.send((byte*) &messTest); // On envoie le message (Strings) et strucutre
        while(Mirf.isSending()); // On attend la fin de l'envoi
  }
  
  void cibleFalseFB() {
        int messTest = 3;
        Mirf.setTADDR((byte *) toIDobjetSlot2);//IDobjet);  // "nrf01"); // Adresse de transmission
        Mirf.send((byte*) &messTest); // On envoie le message (Strings) et strucutre
        while(Mirf.isSending()); // On attend la fin de l'envoi
  }
};

//////////////////////////////Objet : WizarBlaster slot 5
/////////////////////////////////////////////


struct WizarBlaster{
  int munitions = 20 ;
  String mode = "plasma" ;  //Blaster, Plasma, mitraillette ?
  bool gachetteToken;
  bool rechargeToken;
  bool equipe=HIGH;

  void rechargeFB() {
        int messTest = 1;
        Mirf.setTADDR((byte *) toIDobjetSlot2);//IDobjet);  // "nrf01"); // Adresse de transmission
        Mirf.send((byte*) &messTest); // On envoie le message (Strings) et strucutre
        while(Mirf.isSending()); // On attend la fin de l'envoi
  }
  void gachetteFB() {
        int messTest = 1;
        Mirf.setTADDR((byte *) toIDobjetSlot2);//IDobjet);  // "nrf01"); // Adresse de transmission
        Mirf.send((byte*) &messTest); // On envoie le message (Strings) et strucutre
        while(Mirf.isSending()); // On attend la fin de l'envoi
  }
  
  void cibleTrueFB() {
        int messTest = 2;
        Mirf.setTADDR((byte *) toIDobjetSlot2);//IDobjet);  // "nrf01"); // Adresse de transmission
        Mirf.send((byte*) &messTest); // On envoie le message (Strings) et strucutre
        while(Mirf.isSending()); // On attend la fin de l'envoi
  }
  
  void cibleFalseFB() {
        int messTest = 3;
        Mirf.setTADDR((byte *) toIDobjetSlot2);//IDobjet);  // "nrf01"); // Adresse de transmission
        Mirf.send((byte*) &messTest); // On envoie le message (Strings) et strucutre
        while(Mirf.isSending()); // On attend la fin de l'envoi
  }
};


char objet ;
char action ;
int valeur ;


bool sendTicket = LOW ;
bool debug_mode = HIGH;
int message_moniteur ;

void brassardFBtest() {}



///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////SETUP///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);

  Mirf.cePin = 9; // Broche CE sur D9
  Mirf.csnPin = 10; // Broche CSN sur D10
  Mirf.spi = &MirfHardwareSpi; // On veut utiliser le port SPI hardware
  Mirf.init(); // Initialise la bibliothèque

  Mirf.channel = 1; // Choix du canal de communication (128 canaux disponibles, de 0 à 127)
  Mirf.payload = sizeof(MaStructure); // Taille d'un message (maximum 32 octets) MaStructure
  Mirf.config(); // Sauvegarde la configuration dans le module radio

  //Mirf.setTADDR((byte *) toIDobjet);//IDobjet);  // "nrf01"); // Adresse de transmission
  Mirf.setRADDR((byte *) IDobjet);//toIDobjet); // "nrf02");Adresse de réception

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  Serial.println("Hub HF 0.31"); 
}






void loop() {
  /*Réception message :
   * 1 char (voire String) objet qui émet
   * 2 char (voire String) : kessiveutnousdire : c cible, g gachette
   * 3 int (voire String) : valeur de ce qu'il dit
   */
///////////////////////////////////Réception messages d'objets (nr24L01)//////////////////////////////
  MaStructure message;
  envoiNeopixel messNeo;
  infosGantStruct messGant;
  WizarBlaster WizarBlaster;
  flingue flingue;
  gantArcanique gantArcanique;

if (Serial.available() > 0) {message_moniteur = Serial.read() ; Serial.println(message_moniteur);}

if (message_moniteur == 49) {debug_mode = HIGH ;} else //if (message_moniteur == 50) 
{debug_mode = HIGH;}
  
  
  if(Mirf.dataReady()){
    Mirf.getData((byte*) &message); // Réception du paquet

      if(debug_mode){
      Serial.print("objet=");
      Serial.print(message.objet);  
      Serial.print(" action="); // Affiche le message
      Serial.print(message.action);
      Serial.print(" valeur=");
      Serial.println(message.valeur);  
      }
    Serial.println(message.objet);  
    sendTicket = HIGH ;
  }



///////////////////////////////////Envoi vers bluetooth///////////////////////////////////////////////
objet  =message.objet;
action =message.action;
valeur =message.valeur;

//à dégager : cheatCible
     if (message.action == 'c' && message.valeur==1) {cibleID = ":123456";}
else if (message.action == 'c' && message.valeur==2) {cibleID = ":986543";}
else if (message.action == 'c' && message.valeur==3) {cibleID = ":184675";}
else if (message.action == 'c' && message.valeur==4) {cibleID = ":111111";}
else if (message.action == 'c' && message.valeur==0) {cibleID = ":vide";}


if (sendTicket) {
  //Serial.println("{");
  //Serial.print("\"fromId\": \""); Serial.print(joueurID); Serial.println("\",");
  //Serial.print("\"toId\": \""); Serial.print(cibleID); Serial.println("\",");
  //if (cibleID != ":vide") {cibleTrueFB();}
  //else {cibleFalseFB();}
  
    switch (objet){
        case 'f' : ///////////////flingue
          switch (action) {
          case 'g' :        //gachette
          Serial.print("\"rawPiercingDamage\": "); Serial.print(100); Serial.println();
          
          flingue.gachetteToken = HIGH;
          break;

          case 'r' :        //recharge
          Serial.print("\"actionReload\": "); Serial.print(100); Serial.println();
          
          flingue.rechargeToken = HIGH;
          break;
          }
        break;

        case 'w' : ///////////////WizarBlaster3000
          switch (action) {
          case 'g' :        //gachette
          Serial.print("\"rawPiercingDamage\": "); Serial.print(100); Serial.println();
          
          WizarBlaster.gachetteToken = HIGH;
          break;

          case 'r' :        //recharge
          Serial.print("\"actionReload\": "); Serial.print(100); Serial.println();
          
          WizarBlaster.rechargeToken = HIGH;
          break;
          }
        break;

        case 'g' : ///////////////gant
          switch (action) {
            case '0' : //accéléromètre x
              gantArcanique.valeursGant[0] = valeur ;
            break;
  
            case '1' : //accéléromètre y
              gantArcanique.valeursGant[1] = valeur ;
            break;
  
            case '2' : //accéléromètre z
              gantArcanique.valeursGant[2] = valeur ;
            break;
  
            case '3' : //pouce
              gantArcanique.valeursGant[3] = valeur ;
            break;
  
            case '4' : //index
              gantArcanique.valeursGant[4] = valeur ;
            break;
  
            case '5' : //majeur
              gantArcanique.valeursGant[5] = valeur ;
            break;
  
            case '6' : //annulaire
              gantArcanique.valeursGant[6] = valeur ;
            break;
  
            case '7' : //aricuaire
              gantArcanique.valeursGant[7] = valeur ;
            break;
          }
        break;
        
        case 'h' : ///////////////grimoire
          switch (action) {
          case 'f' : //feu
          Serial.print("\"rawFireDamage\": "); Serial.print(100); Serial.println();
          
          break;

          case 's' : //soins
          Serial.print("\"rawHeal\": "); Serial.print(100); Serial.println();
          
          break;

          case 'b' : //bouclier
          Serial.print("\"rawBarrier\": "); Serial.print(100); Serial.println();
          
          break;
          }
        break;

        case 'm' : ///////////////Grappemain
          Serial.print("Grappemain");
          switch (action) {
            
          case 's' :  //scanne
          Serial.print(" utilise ");
          Serial.print(valeur);
          break ;
          }
        break;

        case 'p' : ///////////////Piquemord
          switch (action) {
          case 'h' : //touche
          Serial.print("\"swordDamage\": "); Serial.print(valeur); Serial.println();
          
          break;
            
          case 'f' : //feu
          Serial.print("\"fireMode\": "); Serial.print(100); Serial.println();
          
          break;

          case 'p' : //poison
          Serial.print("\"poisonMode\": "); Serial.print(100); Serial.println();
          
          break;

          case 'b' : //berserk
          Serial.print("\"berserkMode\": "); Serial.print(100); Serial.println();
          
          break;
          }
        break;
    
    }
  //Serial.println("<");
    if(debug_mode) {
      for (int i=0; i<8; i++) {Serial.print(gantArcanique.valeursGant[i]);Serial.print(" ");}
      Serial.print(" ");
      }
  sendTicket = LOW ;
}






//////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *                                          TRAITEMENT
 * 
 *////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////Gant

  if (gantArcanique.equipe) {
  int x = gantArcanique.valeursGant[0] ;
  int y = gantArcanique.valeursGant[1] ;
  int z = gantArcanique.valeursGant[2] ;

  int p = gantArcanique.valeursGant[3] ;
  int i = gantArcanique.valeursGant[4] ;
  int m = gantArcanique.valeursGant[5] ;
  int an= gantArcanique.valeursGant[6] ;
  int au= gantArcanique.valeursGant[7] ;
  
  static bool gesteFeu2 ;
  static unsigned long coolDownGestFeu = 2000;
  static unsigned long timeDownGestFeu ;
  
    //feu
    if (p>960 && i>960 && m<1000 && an<1000 && au>960 && y>80 && gantArcanique.flagTraitDeFeu) {
      gesteFeu2 = HIGH; 
      timeDownGestFeu = millis() + coolDownGestFeu;
      //Serial.println("etape1 feu");
      gantArcanique.T2FchargeFB();
      }
    if (gesteFeu2 && z>80) {gantArcanique.traitDeFeuLaunch(); gesteFeu2 = LOW; }
    if (millis() > timeDownGestFeu) {gesteFeu2 = LOW ;}
  }

///////////////////////////////////////////////Flingue
if (flingue.equipe) {
 
  if (flingue.gachetteToken) {WizarBlaster.gachetteFB(); flingue.gachetteToken = LOW;}
  if (flingue.rechargeToken) {flingue.rechargeFB(); flingue.rechargeToken = LOW; flingue.munitions = 20 ;}
}

///////////////////////////////////////////////WizarBlaser3000
if (WizarBlaster.equipe) {
 
  if (WizarBlaster.gachetteToken) {WizarBlaster.gachetteFB(); WizarBlaster.gachetteToken = LOW;}
  if (WizarBlaster.rechargeToken) {WizarBlaster.rechargeFB(); WizarBlaster.rechargeToken = LOW; WizarBlaster.munitions = 100 ;}
}



/////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////Tag infrarouge/////////////////////////////////////////////////////
//AEnvoyer = joueurID;
AEnvoyer = ":123456";
/*
if (digitalRead(4) == LOW) {AEnvoyer = ":123456";}  //Alarik
if (digitalRead(5) == LOW) {AEnvoyer = ":986543";}  //Rhea
if (digitalRead(6) == LOW) {AEnvoyer = ":184675";}  //Dessloch*/
/*
  if (tagGate < millis()) {
    for (int i = 0; i < AEnvoyer.length(); i++){
      irsend.sendRC5(AEnvoyer.charAt(i), 12); 
      delay(15);
    }
    tagGate = millis() + 100 ; //200 à la base
  }*/

  
}
















/*
{
    "fromId": ":111111",
    "toId": ":123456",
    "rawPiercingDamage": 100
}
*/

/*
if (fromPlayer != "0" || toPlayer != "0" || objet != "0" || action != "0") {
  Serial.println("{");
  Serial.print("\"action\": \"");
  Serial.print(action);
  Serial.println("\",");
  Serial.print("\"objet\": [");
  Serial.print(objet);
  Serial.println("],");
  Serial.print("\"from\": \"");
  Serial.print(fromPlayer);
  Serial.println("\",");
  Serial.print("\"toIds\": [");
  Serial.print(toPlayer);
  Serial.println("],");
  Serial.print("\"data\": {\"damage\" : ");
  Serial.print(action);
    if (heure != "0") {
        Serial.print("\"hitbox\": ");
        Serial.println(heure);
        }
  Serial.println("}");
  Serial.println("}");
  zero();
  }*/








  

