#include <Adafruit_NeoPixel.h>
#include <VirtualWire.h> 


#define PIN 6 //pin number that you have connected your data pin to
#define PIXNUMBER 8 //number of neopixels you have connected

float bright = 10 ;
int coul;
int red;
int green;
int blue;

unsigned long tagTemps1 = 2000;
unsigned long offCast;

bool ledUpdate = LOW;


byte commande;
byte param;
byte mess3;
byte mess4;


Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXNUMBER, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options
uint32_t noir = strip.Color(0, 0, 0);
uint32_t orange1 = strip.Color(100, 20, 0);
uint32_t rouge = strip.Color(50, 0, 0);
uint32_t rose = strip.Color(50, 3, 3);
uint32_t bleu = strip.Color(10, 0, 50);
uint32_t vert = strip.Color(0, 100, 0);



void setup()
{
  delay(1000);
  Serial.begin(9600);
  Serial.println("hud-hub 0.7b, barre de vie renversee");

  pinMode(13, OUTPUT);
  
  strip.begin(); 
  strip.setBrightness(100);
  strip.show();//sets all pixels to off state
  
  vw_set_tx_pin(12);  //besoin ?
  vw_set_rx_pin(11);
  vw_set_ptt_pin(3);  //besoin ?
  vw_set_ptt_inverted(true); // Required for DR3100 //besoin ?
  vw_setup(2000); // initialisation de la librairie VirtualWire à 2000 bauds (note: je n'utilise pas la broche PTT)
  vw_rx_start();  // Activation de la partie réception de la librairie VirtualWire


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////LOOP//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // doit recevoir les messages bluetooth (leds de vie, enchantements d'armes)
  // doit envoyer les messages bluetooth (json ?) tel joueur touché par tel sort
  // doit recevoir les messages radio (AoE ennemi, tel joueur visé, telle arme activée [et ne pas faire le mix dans l'arme !])
  // doit envoyer les messages radio (AoE, quand touché [filaments, Velostat ...])
  // doit envoyer tag IR
}

void loop(){



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////Ondes radio///////////////////////////////////////////////////////////
  uint8_t buf[VW_MAX_MESSAGE_LEN]; // Tableau qui va contenir le message reçu (de taille maximum VW_MAX_MESSAGE_LEN)
  uint8_t buflen = VW_MAX_MESSAGE_LEN; // Taille maximum de notre tableau
  char destinataire[buflen] ;  //équipe ou perso                                                    to: dreadbond from: dreadbond objet: epee action: taille valeur: 31 heure: 1800486
  char objet[buflen] ;         //tag d'un objet : uniquement pour objets self                       to: dreadbond from: dreadbond objet:epee frappe_feu valeur: 86
  char joueur[buflen] ;        //reconnaitre l'AoE d'un joueur                                      to: blueteam from: dreabond objet:frappe_feu valeur: 86
  char actObjet[buflen] ;      //action de l'objet : soin, dégâts, mutisme etc ...                  to: aristide from: aristide objet:grimoire_soins valeur: 52
  char valObjet[buflen] ;      //puissance de l'action : besoin ?                                   to: blueteam from: aristide objet:soins valeur: 52
  char heure[buflen] ;         //heure pour ne faire qu'une action                                  to: redteam from: aristide objet:mutisme valeur: 0 heure: 186151
  char cible[buflen] ;         //
  

  

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
    digitalWrite(13, HIGH); // Flash a light to show received good message
    int i;
    bool modeInt = LOW;

                int message = buf[i];  // traitement pour le Bluetooth. A dégager quans il y aura les vraies phrases
                byte messageConv = byte(message);
                Serial.write(messageConv);
            for (i = 0; i < buflen; i++)
            {
                
                int  recuInt  = buf[i];
                char recuChar = buf[i];

                if (modeInt == HIGH) {Serial.print(recuInt);}
            //    if (modeInt == LOW) {Serial.print(recuChar);}

                if (recuInt == 58) {modeInt = HIGH;}
                //Serial.print(buf[i], HEX);
                //Serial.print(' ');
            }
    Serial.println();
    digitalWrite(13, LOW);
    }
/*
 * if (buf == objet) {valArme = valeur1; arme == HIGH; }  //dans Bluetoot, envoyer cmd 10 avec param valArme
 * if (buf == cible)
 * 
 * 
 * 
 * 
 * 
 */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////Bluetooth///////////////////////////////////////////////////////////////

byte commande;   //??
byte param;   //??

if (Serial.available() >= 2) //si 2 dans la file
{
    commande = Serial.read() ;
    param |= Serial.read();

    Serial.print(commande); Serial.print(" <cmd ");
    Serial.print(param); Serial.println(" <param");
   }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////Tag infrarouge///////////////////////////////////////////////////////



}
