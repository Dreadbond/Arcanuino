    /*
      Barrière infrarouge avec Arduino
      LED IR sur D3 (géré par librairie IRremote) + TSOP32138 -> D2
      La LED13 de l'Arduino s'allume en cas de coupure du faisceau lumineux
    */

    #include <IRremote.h>

    #define CAPTEUR 2 // récepteur IR -> D2
    #define LED_STATUT 13 // LED -> D13

    IRsend irsend; // déclaration de l'objet émetteur (pin D3 obligatoire)

    void setup()
    {
      pinMode(CAPTEUR, INPUT);
      pinMode(LED_STATUT, OUTPUT);
     
      irsend.enableIROut(38); // crée une sortie modulée à 38KHz
      Serial.begin(9600);
    }

    void loop()
    {
      irsend.mark(0); // envoi du signal pour une durée illimitée
     
      boolean mesure1 = digitalRead(CAPTEUR); // première mesure
      delay(5);                               // délai
      boolean mesure2 = digitalRead(CAPTEUR); // seconde mesure
      boolean etat = mesure1 * mesure2;       // comparaison
     
      if (etat == HIGH) // si les deux lectures voient une coupure
      {
        digitalWrite(LED_STATUT, HIGH);
        Serial.println("Coupure !");
      }
      else              // sinon
      {
        digitalWrite(LED_STATUT, LOW);
        Serial.println("----------OK----------");
      }
      delay(5);
    }
