/**
 * Exemple de code pour la bibliothèque Mirf – Serveur d'envoi de structure
 */
#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI
/*
typedef struct {
  char commande;
  int valeur;
} MaStructure;
*/
typedef struct {
  char commande;
  int valeur;
  String cibleStru ;
  String proprio ;
  String objectStru ;
} MaStructure;

void setup() {
  Serial.begin(9600);

  Mirf.cePin = 9; // Broche CE sur D9
  Mirf.csnPin = 10; // Broche CSN sur D10
  Mirf.spi = &MirfHardwareSpi; // On veut utiliser le port SPI hardware
  Mirf.init(); // Initialise la bibliothèque

  Mirf.channel = 1; // Choix du canal de communication (128 canaux disponibles, de 0 à 127)
  Mirf.payload = sizeof(MaStructure); // Taille d'un message (maximum 32 octets)
  Mirf.config(); // Sauvegarde la configuration dans le module radio

  Mirf.setTADDR((byte *) "nrf02"); // Adresse de transmission
  Mirf.setRADDR((byte *) "nrf01"); // Adresse de réception

  Serial.println("Go ! (serveur)"); 
}

void loop() {
  MaStructure message;

  if(Mirf.dataReady()){
    Mirf.getData((byte*) &message); // Réception du paquet

/*
  Serial.print(message.commande); Serial.print(" ");
  Serial.print(message.valeur); Serial.print(" ");
  Serial.print(message.cibleStru); Serial.print(" ");
  Serial.print(message.proprio); Serial.print(" ");
  Serial.print(message.objectStru); Serial.println(" ");*/
    /*
    Serial.print("commande="); // Affiche le message
    Serial.print(message.commande);
    Serial.print(" valeur=");
    Serial.println(message.valeur);
    */
  }
}
