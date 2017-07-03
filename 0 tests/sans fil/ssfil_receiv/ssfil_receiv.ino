    // ==== Recepteur 433 MHz ===============================
    //
    // Source : http://skyduino.wordpress.com/2011/12/29/tutoriel-arduino-et-emetteurrecepteur-433mhz-virtualwire/
    //
    //=======================================================

    #include <VirtualWire.h> // inclusion de la librairie VirtualWire

    int vie = 100;
    int message;
    uint8_t buf[VW_MAX_MESSAGE_LEN]; // Tableau qui va contenir le message reçu (de taille maximum VW_MAX_MESSAGE_LEN)
    uint8_t buflen = VW_MAX_MESSAGE_LEN; // Taille maximum de notre tableau
    void setup() // Fonction setup()
    {
        Serial.begin(9600); // Initialisation du port série pour avoir un retour sur le serial monitor
        Serial.println("Tuto VirtualWire recepteur"); // Petit message de bienvenue
        pinMode(13, OUTPUT);
        vw_setup(2000); // initialisation de la librairie VirtualWire à 2000 bauds (note: je n'utilise pas la broche PTT)
        vw_rx_start();  // Activation de la partie réception de la librairie VirtualWire
    }
    
    int actions(int numero){
switch(numero) {
  case 5:
  vie = vie - 10;
  return vie;
  break;
  
  case 6:
  vie = vie - 20;
  return vie;
  break;
  
  case 7:
  vie = vie - 30;
  return vie;
  break;
  
  case 8:
  vie = vie - 40;
  return vie;
  break;
 
}


    }
     
    void loop() // Fonction loop()    
    {
        if (vw_wait_rx_max(200)) // Si un message est reçu dans les 200ms qui viennent
        {
            if (vw_get_message(buf, &buflen)) // On copie le message, qu'il soit corrompu ou non
            {
                Serial.print("RX : ");
                for (byte i = 0; i < buflen; i++) // Si il n'est pas corrompu on l'affiche via Serial
                message = int(buf[i]- '0');
                Serial.print(message);   //Conversion ASCII des chiffres 0-9
                //Serial.print(buf);   //Conversion ASCII
                 {
                 

                 }
                 Serial.println("");
                }
            vie = actions(message);
            Serial.print("Vie : ");
            Serial.println(vie);
            }

        }
    

       
    

        /*digitalWrite(13, HIGH);
        delay(1000); // Et on attend 2s pour pas flooder
        digitalWrite(13, LOW); */
