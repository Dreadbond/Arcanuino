#include <VirtualWire.h>

int vie = 0 ;
int mana = 0 ;
int ennVie = 0 ;
int ennMana = 0;
int rssi ; 

//char messActual[15];
byte message_in_bt ;
char message_out_rf[0] ;
byte message_out_bt ;

bool debug_mode = HIGH;

void setup()
{
    pinMode(A0, INPUT);
    Serial.begin(9600);	// Debugging only
    Serial.println("Hub V0.2");
    vw_set_rx_pin(A5);
    vw_set_tx_pin(12);
    // Initialise the IO and ISR
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec

    vw_rx_start();       // Start the receiver PLL running

    pinMode(A5, INPUT); //digital
    pinMode(A4, INPUT); //RSSI
    pinMode(A3, OUTPUT);//5V

    digitalWrite(A5, LOW);
    digitalWrite(A3, HIGH);

}

void loop()
{

if (Serial.available() > 0) 
    {
    int wat = Serial.read();
    if (wat == 49) {debug_mode = HIGH;} else {debug_mode = LOW; }
    }
    

  

  
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
  	//int i; à dégager ?
    char messActual[buflen] = " ";
    digitalWrite(13, true);
  
          	for (int i = 0; i < buflen; i++) //faisage du message à partir des lettres
              	{
                char lettre = char(buf[i]);
                messActual[i] = lettre ;
              	}


            String qsdqsd = String(messActual);
            int qsdqsdLengh = qsdqsd.length();
            Serial.println(qsdqsd);

            for (int i=0; i < qsdqsdLengh; i++) {
            /////////////////////////////////Pour qui ?/////////////////////////////////
            if (qsdqsd.startsWith("to_pl1", i)) {Serial.print("To : Dreadbond ");}
            if (qsdqsd.startsWith("to_pl2", i)) {Serial.print("To : Vikti  ");}
            if (qsdqsd.startsWith("to_en1", i)) {Serial.print("To : Alarik ");}
            if (qsdqsd.startsWith("to_en2", i)) {Serial.print("To : Rhea ");}
            if (qsdqsd.startsWith("to_blue", i)) {Serial.print("To : Blue team ");}
            if (qsdqsd.startsWith("to_red", i)) {Serial.print("To : Red team ");}
              
            /////////////////////////////////De qui ?///////////////////////////////////
            if (qsdqsd.startsWith("fr_pl1", i)) {Serial.print("From : Dreadbond ");}
            if (qsdqsd.startsWith("fr_pl2", i)) {Serial.print("From : Vikti ");}
            if (qsdqsd.startsWith("fr_en1", i)) {Serial.print("From : Alarik ");}
            if (qsdqsd.startsWith("fr_en2", i)) {Serial.print("From : Rhea ");}

            /////////////////////////////////Objet//////////////////////////////////////
            if (qsdqsd.startsWith("sw_", i)) {Serial.print("Piquemord ");}
            if (qsdqsd.startsWith("gr_", i)) {Serial.print("Grimoire Arcanique ");}
            if (qsdqsd.startsWith("gt_", i)) {Serial.print("Gant Arcanique ");}  
            if (qsdqsd.startsWith("dom1_", i)) {Serial.print("Doominator ");} 
             
            if (qsdqsd.startsWith("amu", i)) {Serial.print("amulette ");}
            if (qsdqsd.startsWith("coff", i)) {Serial.print("coffre ");}
            if (qsdqsd.startsWith("hevheal", i)) {Serial.print("borne de soins ");}
            if (qsdqsd.startsWith("flag", i)) {Serial.print("drapeau ");}
            if (qsdqsd.startsWith("redkey", i)) {Serial.print("clef rouge ");}

            /////////////////////////////////Action/////////////////////////////////////
            if (qsdqsd.startsWith("stk", i)) {Serial.print("frappe ");}
            if (qsdqsd.startsWith("aoe", i)) {Serial.print("atteint ");}
            if (qsdqsd.startsWith("hit", i)) {Serial.print("touche ");}
            
            if (qsdqsd.startsWith("fe", i)) {Serial.print("enflamme ");}
            if (qsdqsd.startsWith("po", i)) {Serial.print("empoisonne ");}
            if (qsdqsd.startsWith("be", i)) {Serial.print("berserk ");}
            
            if (qsdqsd.startsWith("dr", i)) {Serial.print("drain de vie ");}
            if (qsdqsd.startsWith("bf", i)) {Serial.print("boule de feu ");}
            if (qsdqsd.startsWith("pu", i)) {Serial.print("super punch ");}
            //if (qsdqsd.startsWith("bo", i)) {Serial.print("barriere ");}

            if (qsdqsd.startsWith("so", i)) {Serial.print("soigne ");}
            if (qsdqsd.startsWith("bo", i)) {Serial.print("met un bouclier ");}

            if (qsdqsd.startsWith("equ", i)) {Serial.print("equipe ");}
            if (qsdqsd.startsWith("inte", i)) {Serial.print("interaction avec ");}
            
            /////////////////////////////////Valeur/////////////////////////////////////
            if (qsdqsd.startsWith("val_", i)) {Serial.print("inserer valeur");}
            
            /////////////////////////////////Heure//////////////////////////////////////
            if (qsdqsd.startsWith("time_", i)) {Serial.print("inserer temps");}
            
            /////////////////////////////////RSSI///////////////////////////////////////
            if (qsdqsd.startsWith("rssi_", i)) {Serial.print("inserer force signal");}
            }
        digitalWrite(13, false);
        
        Serial.println(rssi);
    } // fin boucle réception HF

vie = 0 ;
mana = 0 ;
ennVie = 0 ;
ennMana = 0;

rssi = analogRead(A4);
//if (debug_mode == HIGH) {Serial.println(rssi);}

if (Serial.available() > 0) {message_in_bt = Serial.read();}

if (message_in_bt == 48) {char message_out_rf[13] = "to:br_ss:none" ; vw_send((uint8_t *)message_out_rf, 13); vw_wait_tx(); }
if (message_in_bt == 49) {char message_out_rf[12] = "to:br_ss:feu" ; vw_send((uint8_t *)message_out_rf, 12); vw_wait_tx(); }
if (message_in_bt == 50) {char message_out_rf[15] = "to:br_ss:poison" ; vw_send((uint8_t *)message_out_rf, 15); vw_wait_tx(); }
if (message_in_bt == 51) {char message_out_rf[17] = "to:br_ss:bouclier" ; vw_send((uint8_t *)message_out_rf, 17); vw_wait_tx(); }
if (message_in_bt == 52) {char message_out_rf[14] = "to:br_ss:soins" ; vw_send((uint8_t *)message_out_rf, 14); vw_wait_tx(); }
if (message_in_bt == 53) {char message_out_rf[14] = "to:br_ss:drain" ; vw_send((uint8_t *)message_out_rf, 14); vw_wait_tx(); }
if (message_in_bt == 54) {char message_out_rf[14] = "to:br_ss:punch" ; vw_send((uint8_t *)message_out_rf, 14); vw_wait_tx();}

if (message_in_bt == 56) {char message_out_rf[11] = "to:br_vie_1" ; vw_send((uint8_t *)message_out_rf, 11); vw_wait_tx();}
if (message_in_bt == 57) {char message_out_rf[12] = "to:br_mana_2" ; vw_send((uint8_t *)message_out_rf, 12); vw_wait_tx();}
if (message_in_bt == 58) {char message_out_rf[14] = "to:br_vieEnn_3" ; vw_send((uint8_t *)message_out_rf, 14); vw_wait_tx();}
if (message_in_bt == 59) {char message_out_rf[15] = "to:br_manaEnn_4" ; vw_send((uint8_t *)message_out_rf, 15); vw_wait_tx();}

if (message_in_bt == 60) {char message_out_rf[13] = "to:sw1_ss:feu" ; vw_send((uint8_t *)message_out_rf, 13); vw_wait_tx(); }
if (message_in_bt == 61) {char message_out_rf[16] = "to:sw1_ss:poison" ; vw_send((uint8_t *)message_out_rf, 16); vw_wait_tx(); }
if (message_in_bt == 62) {char message_out_rf[17] = "to:sw1_ss:berserk" ; vw_send((uint8_t *)message_out_rf, 17); vw_wait_tx(); }
if (message_in_bt == 63) {char message_out_rf[14] = "to:sw1_ss:rien" ; vw_send((uint8_t *)message_out_rf, 14); vw_wait_tx(); }


//if (message_out_rf > 0) {
message_in_bt = 0;
message_out_rf[0] = " ";
message_out_bt = 0 ;




/*
  if(sscontact < millis()) {
    if(rfid.isCard()){  //Serial.print("qdsqsd");
        if(rfid.readCardSerial()){
            Serial.print(rfid.serNum[0]);
            Serial.print(" ");
            Serial.print(rfid.serNum[1]);
            Serial.print(" ");
            Serial.print(rfid.serNum[2]);
            Serial.print(" ");
            Serial.print(rfid.serNum[3]);
            Serial.print(" ");
            Serial.print(rfid.serNum[4]);
            Serial.println("");
            
            for(int x = 0; x < sizeof(cards); x++){
              for(int i = 0; i < sizeof(rfid.serNum); i++ ){
                  if(rfid.serNum[i] != cards[x][i]) {
                      access = false;
                      break;
                  } else {
                      access = true;
                  }
              }
              if(access) break;
            }
        }
       if(access){
          Serial.println("Welcome!");           
      } else {
           Serial.println("Not allowed!"); 
       }
    //rfid.halt();
    }
  sscontact = millis() + 1000 ;
  }*/
}
