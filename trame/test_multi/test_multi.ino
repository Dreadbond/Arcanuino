    /*
      Utilisation d'un convertisseur analogique-numérique MCP3008 avec Arduino
      Lecture d'un potentiomètre sur pin digitale
      Arduino IDE 1.0.3
    */

    #include <SPI.h>

    #define slaveSelect 10

    void setup()
    {
      pinMode(slaveSelect, OUTPUT);
     
      // Initialisation du bus SPI
      SPI.begin();
      // Configuration du mode d'envoi des données :
      SPI.setBitOrder(MSBFIRST);  // bit le plus à gauche en premier
      SPI.setDataMode(SPI_MODE0); // Mode 0 : données capturées sur front montant d'horloge et transmises sur front descendant
     
      // Initialisation de la liaison série
      Serial.begin(9600);
    }

    void loop()
    {
      // Commande à envoyer au MCP3008 (sélection du canal)
      byte channel1 = 0b01000000;
     
      digitalWrite(slaveSelect, LOW);
      // Envoi de la commande de lecture
      SPI.transfer(channel1);

      // Envoi de deux bytes nuls pour réception des données
      byte high = SPI.transfer(0);
      byte low = SPI.transfer(0);

      // Fin de la communication
      digitalWrite(slaveSelect, HIGH);

      // Conversion en un seul "mot" de 16 bits
      unsigned int data1 = word(high, low);
      // Décalage à droite pour conserver les 10 bits qui nous intéressent
      data1 = (data1 >> 6);

      byte channel2 = 0b01001000;
      digitalWrite(slaveSelect, LOW);
      SPI.transfer(channel2);
      byte high2 = SPI.transfer(0);
      byte low2 = SPI.transfer(0);
      digitalWrite(slaveSelect, HIGH);
      unsigned int data2 = word(high2, low2);
      data2 = (data2 >> 6);

      byte channel3 = 0b01010000;
      digitalWrite(slaveSelect, LOW);
      SPI.transfer(channel3);
      high = SPI.transfer(0);
      low = SPI.transfer(0);
      digitalWrite(slaveSelect, HIGH);
      unsigned int data3 = word(high, low);
      data3 = (data3 >> 6);

      // Envoi sur liaison série
      Serial.print(data1);
      Serial.print(" ");
      Serial.print(data2);
      Serial.print(" ");
      Serial.println(data3);
      delay(10);
    }
