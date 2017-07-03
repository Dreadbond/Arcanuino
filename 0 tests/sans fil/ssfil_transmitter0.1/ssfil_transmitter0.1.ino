    // ==== Emetteur 433 MHz ===============================
    // Programme d'émission de données

    // Source : http://skyduino.wordpress.com/2011/12/29/tutoriel-arduino-et-emetteurrecepteur-433mhz-virtualwire/
    //
    //=====================================================
    #include <VirtualWire.h> // inclusion de la librairie VirtualWire
     
    const int bouton1=2;
    const int bouton2=3;
    const int bouton3=4;
    const int bouton4=5;

    bool butState1;
    bool butState2;
    bool butState3;
    bool butState4;

    int attente = 100 ;
    
    const char *msg1 = "5"; // Tableau qui contient notre message
     //Chiffres de 0-9 (les caractères ABC... sont transmis en code A=65,...)
    const char *msg2 = "6";
    const char *msg3 = "7";
    const char *msg4 = "8";

    void action1(){
        Serial.print("TX ... "); // On signale le début de l'envoi
        vw_send((uint8_t *)msg1, strlen(msg1)); // On envoie le message
        vw_wait_tx(); // On attend la fin de l'envoi
        Serial.println("Done !"); // On signal la fin de l'envoi
        digitalWrite(13, HIGH);
        delay(attente); // Et on attend 2s pour pas flooder
        digitalWrite(13, LOW);
    }
      void action2(){
        Serial.print("TX ... "); // On signale le début de l'envoi
        vw_send((uint8_t *)msg2, strlen(msg2)); // On envoie le message
        vw_wait_tx(); // On attend la fin de l'envoi
        Serial.println("Done !"); // On signal la fin de l'envoi
        digitalWrite(13, HIGH);
        delay(attente); // Et on attend 2s pour pas flooder
        digitalWrite(13, LOW);
    }
        void action3(){
        Serial.print("TX ... "); // On signale le début de l'envoi
        vw_send((uint8_t *)msg3, strlen(msg3)); // On envoie le message
        vw_wait_tx(); // On attend la fin de l'envoi
        Serial.println("Done !"); // On signal la fin de l'envoi
        digitalWrite(13, HIGH);
        delay(attente); // Et on attend 2s pour pas flooder
        digitalWrite(13, LOW);
    }
        void action4(){
        Serial.print("TX ... "); // On signale le début de l'envoi
        vw_send((uint8_t *)msg4, strlen(msg4)); // On envoie le message
        vw_wait_tx(); // On attend la fin de l'envoi
        Serial.println("Done !"); // On signal la fin de l'envoi
        digitalWrite(13, HIGH);
        delay(attente); // Et on attend 2s pour pas flooder
        digitalWrite(13, LOW);
    }
    
    void setup() // Fonction setup()
    {
        pinMode(bouton1, INPUT);
        pinMode(bouton2, INPUT);
        pinMode(bouton3, INPUT);
        pinMode(bouton4, INPUT);
        pinMode(13, OUTPUT);
        
        Serial.begin(9600); // Initialisation du port série pour avoir un retour sur le serial monitor
        Serial.println("Tuto VirtualWire emetteur"); // Petit message de bienvenue
     
        vw_setup(2000);     // initialisation de la librairie VirtualWire à 2000 bauds (note: je n'utilise pas la broche PTT)
    }
     
    void loop() // Fonction loop()
    {
butState1=digitalRead(bouton1);
butState2=digitalRead(bouton2);
butState3=digitalRead(bouton3);
butState4=digitalRead(bouton4);
    
if (butState1 == HIGH){action1();}
if (butState2 == HIGH){action2();}
if (butState3 == HIGH){action3();}
if (butState4 == HIGH){action4();}



      

    }

