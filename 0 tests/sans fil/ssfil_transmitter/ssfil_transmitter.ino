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
    
    const char *msg = "50"; // Tableau qui contient notre message
     //Chiffres de 0-9 (les caractères ABC... sont transmis en code A=65,...)

    void action1(){
        Serial.print("TX ... "); // On signale le début de l'envoi
        vw_send((uint8_t *)msg, strlen(msg)); // On envoie le message
        vw_wait_tx(); // On attend la fin de l'envoi
        Serial.println("Done !"); // On signal la fin de l'envoi
        delay(2000); // Et on attend 2s pour pas flooder
    }
  
    
    void setup() // Fonction setup()
    {
        pinMode(bouton1, INPUT);
        pinMode(bouton2, INPUT);
        pinMode(bouton3, INPUT);
        pinMode(bouton4, INPUT);
        
        Serial.begin(9600); // Initialisation du port série pour avoir un retour sur le serial monitor
        Serial.println("Tuto VirtualWire"); // Petit message de bienvenue
     
        vw_setup(2000);     // initialisation de la librairie VirtualWire à 2000 bauds (note: je n'utilise pas la broche PTT)
    }
     
    void loop() // Fonction loop()
    {
if (digitalRead(bouton1) ==HIGH){action1();)
if (digitalRead(bouton2) ==HIGH){action2();)
if (digitalRead(bouton3) ==HIGH){action3();)
if (digitalRead(bouton4) ==HIGH){action4();)



      

    }

