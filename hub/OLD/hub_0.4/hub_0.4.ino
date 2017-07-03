#include <VirtualWire.h>
#include <stdlib.h>

int oldVie = 0 ;
int oldMana = 0 ;
int oldEnnVie = 0 ;
int oldEnnMana = 0;
int oldSortCast = 0 ;
int oldEpeeCast = 0 ;

int vie = 0 ;
int mana = 0 ;
int ennVie = 0 ;
int ennMana = 0;
int sortCast = 0 ;
int epeeCast = 0 ;

unsigned long tourChange = 0;
int tourEcoute = 1 ;

//char messActual[15];
byte message_in_bt ;
String message_in_rf ; //ptetre une connerie
char message_out_rf[0] ;
byte message_out_bt ;
char qsdmessage_in_bt ;

bool debug_mode = HIGH;

String fromPlayer = "0";
String toPlayer = "0";
String object = "0";
String action = "0";
int valeur = 0 ;
long heure = 0 ;
int rssi = 0 ; 

byte commande;
byte param;





void zero() {
 fromPlayer = "0" ;
 toPlayer = "0" ;
 object = "0" ;
 action = "0" ;
}

void setup()
{
    pinMode(A0, INPUT);
    Serial.begin(9600);	// Debugging only
    Serial.println("Hub V0.4");
    vw_set_rx_pin(11);
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
  /*
if (tourChange < millis()) {tourEcoute = -tourEcoute ; tourChange = millis() + 2000 ; }

if (tourEcoute == 1) {Serial.println("tour Bluetooth");}
if (tourEcoute == -1) {Serial.println("tour recepteur RF");}*/

oldVie = vie ;
oldMana = mana ;
oldEnnVie = ennVie ;
oldEnnMana = ennMana;
oldSortCast = sortCast ;
oldEpeeCast = epeeCast ;


//////////////////////////////////////////////////////////////////////////RF IN/////////////////////////////////////////////////////////////////////////////


    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen) ) // Non-blocking&& tourEcoute == 1
    {
    //int i; à dégager ?
    char messActual[buflen] = " ";
    digitalWrite(13, true);
  
            for (int i = 0; i < buflen; i++) //faisage du message à partir des lettres
                {
                char lettre = char(buf[i]);
                messActual[i] = lettre ;
                }


            message_in_rf = String(messActual);
            int qsdqsdLengh = message_in_rf.length();
            //Serial.println(message_in_rf);

            for (int i=0; i < qsdqsdLengh; i++) {
            /////////////////////////////////Pour qui ?/////////////////////////////////
            if (message_in_rf.startsWith("to_pl1", i)) {toPlayer = "Dreadbond";}
            if (message_in_rf.startsWith("to_pl2", i)) {toPlayer = "Vikti";}
            if (message_in_rf.startsWith("to_en1", i)) {toPlayer = "Alarik";}
            if (message_in_rf.startsWith("to_en2", i)) {toPlayer = "Rhea";}
            if (message_in_rf.startsWith("to_blue", i)) {toPlayer = "Blue team";}
            if (message_in_rf.startsWith("to_red", i)) {toPlayer = "Red team";}
              
            /////////////////////////////////De qui ?///////////////////////////////////
            if (message_in_rf.startsWith("fr_pl1", i)) {fromPlayer = "Dreadbond ";}
            if (message_in_rf.startsWith("fr_pl2", i)) {fromPlayer = "Vikti ";}
            if (message_in_rf.startsWith("fr_en1", i)) {fromPlayer = "Alarik ";}
            if (message_in_rf.startsWith("fr_en2", i)) {fromPlayer = "Rhea ";}

            /////////////////////////////////Objet//////////////////////////////////////
            if (message_in_rf.startsWith("sw_", i)) {object = "Piquemord";}
            if (message_in_rf.startsWith("gr_", i)) {object = "Grimoire Arcanique";}
            if (message_in_rf.startsWith("gt_", i)) {object = "Gant Arcanique";}  
            if (message_in_rf.startsWith("dom1_", i)) {object = "Doominator";} 
            
            if (message_in_rf.startsWith("amu", i)) {object = "amulette";}
            if (message_in_rf.startsWith("coff", i)) {object = "coffre";}
            if (message_in_rf.startsWith("hevheal", i)) {object = "borne de soins";}
            if (message_in_rf.startsWith("flag", i)) {object = "drapeau";}
            if (message_in_rf.startsWith("redkey", i)) {object = "clef rouge";}

            /////////////////////////////////Action/////////////////////////////////////
            if (message_in_rf.startsWith("stk", i)) {action = "frappe ";}
            if (message_in_rf.startsWith("aoe", i)) {action = "atteint";}
            if (message_in_rf.startsWith("hit", i)) {action = "touche";}
            
            if (message_in_rf.startsWith("fe", i)) {action = "enflamme";}
            if (message_in_rf.startsWith("po", i)) {action = "empoisonne";}
            if (message_in_rf.startsWith("be", i)) {action = "berserk";}
            
            if (message_in_rf.startsWith("dr", i)) {action = "drain de vie";}
            if (message_in_rf.startsWith("bf", i)) {action = "boule de feu";}
            if (message_in_rf.startsWith("pu", i)) {action = "super punch";}
            //if (message_in_rf.startsWith("bo", i)) {action = "barriere";}

            if (message_in_rf.startsWith("so", i)) {action = "soigne";}
            if (message_in_rf.startsWith("bo", i)) {action = "met un bouclier";}

            if (message_in_rf.startsWith("equ", i)) {action = "equipe";}
            if (message_in_rf.startsWith("inte", i)) {action = "interaction avec";}
            
            /////////////////////////////////Valeur/////////////////////////////////////
            if (message_in_rf.startsWith("val_", i)) {valeur = "inserer valeur";}
            
            /////////////////////////////////Heure//////////////////////////////////////
            if (message_in_rf.startsWith("time_", i)) {heure = "inserer temps";}
            
            /////////////////////////////////RSSI///////////////////////////////////////
            if (message_in_rf.startsWith("rssi_", i)) {rssi = "inserer force signal";}
            }
        digitalWrite(13, false);
        
        //Serial.println(rssi);
    } // fin boucle réception HF

/////////////////////////////////////////////////////////////////////BLUETOOTH IN/////////////////////////////////////////////////////////////////////////////
if (Serial.available() >= 2 ) //si 2 dans la file&& tourEcoute == -1
{
    commande = Serial.read() ; //- '0';
    param = Serial.read() ; //- '0';

    //char paramChar = char(param);
  
    //Serial.print(commande); Serial.print(" <cmd ");   // à voir : le fait dans le bon ordre, mais param = 255 ???
    //Serial.print(param); Serial.println(" <param"); //Serial.println(paramChar);
  
  switch (commande){
  case 1:
  vie = param;
  break;

  case 2:
  mana = param;
  break;

  case 3:
  ennVie = param;
  break;

  case 4:
  ennMana = param;
  break;

  case 5:
  sortCast = param;
  break;

  case 6:
  epeeCast = param;
  break;
  }
 }




vie = constrain(vie, 0, 8) ;
mana = constrain(mana, 0, 8) ;
ennVie = constrain(ennVie, 0, 8) ;
ennMana = constrain(ennMana, 0, 8) ;
sortCast = constrain(sortCast, 0, 8) ;
epeeCast = constrain(epeeCast, 0, 8) ;

rssi = analogRead(A4);
//if (debug_mode == HIGH) {Serial.println(rssi);}
/*
if (Serial.available() > 0) {
    message_in_bt = Serial.read(); 
    qsdmessage_in_bt = char(message_in_bt);
    Serial.println(message_in_bt); 
    Serial.println(qsdmessage_in_bt); 
    }*/

/////////////////////////////////////////////////////////////////////RF OUT et BLUETOOTH IN (à séparer)/////////////////////////////////////////////////////////////////////////////////

// à dégager, remplacer par json
if (message_in_bt == 48) {delay(50);char message_out_rf[13] = "to:br_ss:none" ; vw_send((uint8_t *)message_out_rf, 13); vw_wait_tx(); }
if (message_in_bt == 49) {delay(50);char message_out_rf[12] = "to:br_ss:feu" ; vw_send((uint8_t *)message_out_rf, 12); vw_wait_tx(); }
if (message_in_bt == 50) {delay(50);char message_out_rf[15] = "to:br_ss:poison" ; vw_send((uint8_t *)message_out_rf, 15); vw_wait_tx(); }
if (message_in_bt == 51) {delay(50);char message_out_rf[17] = "to:br_ss:bouclier" ; vw_send((uint8_t *)message_out_rf, 17); vw_wait_tx(); }
if (message_in_bt == 52) {delay(50);char message_out_rf[14] = "to:br_ss:soins" ; vw_send((uint8_t *)message_out_rf, 14); vw_wait_tx(); }
if (message_in_bt == 53) {delay(50);char message_out_rf[14] = "to:br_ss:drain" ; vw_send((uint8_t *)message_out_rf, 14); vw_wait_tx(); }
if (message_in_bt == 54) {delay(50);char message_out_rf[14] = "to:br_ss:punch" ; vw_send((uint8_t *)message_out_rf, 14); vw_wait_tx();}
//itoa(buf, integer, 10);

if (vie != oldVie) {delay(50);char message_out_rf[15] = "to:br_vie_" ; char qsdvie = vie + '0' ; message_out_rf[10] = qsdvie ; vw_send((uint8_t *)message_out_rf, 12); vw_wait_tx(); }
if (mana != oldMana) {delay(50);char message_out_rf[15] = "to:br_mana_" ; char qsdmana = mana + '0' ; message_out_rf[11] = qsdmana ; vw_send((uint8_t *)message_out_rf, 13); vw_wait_tx(); }
if (ennVie != oldEnnVie) {delay(50);char message_out_rf[15] = "to:br_ennVie_" ; char qsdennVie = ennVie + '0'; message_out_rf[13] = qsdennVie ; vw_send((uint8_t *)message_out_rf, 15); vw_wait_tx(); }
if (ennMana != oldEnnMana) {delay(50); char message_out_rf[16] = "to:br_ennMana_" ; char qsdennMana = ennMana + '0' ; message_out_rf[14] = qsdennMana ; vw_send((uint8_t *)message_out_rf, 16); vw_wait_tx(); }
if (ennMana != oldEnnMana) {delay(50);char message_out_rf[16] = "to:br_ennMana_" ; char qsdennMana = ennMana + '0' ; message_out_rf[14] = qsdennMana ; vw_send((uint8_t *)message_out_rf, 16); vw_wait_tx(); }

if (sortCast == 0) {delay(50);char message_out_rf[13] = "to:br_ss:none" ; vw_send((uint8_t *)message_out_rf, 13); vw_wait_tx(); sortCast = 10 ; }
if (sortCast == 1) {delay(50);char message_out_rf[14] = "to:br_ss:rouge" ; vw_send((uint8_t *)message_out_rf, 14); vw_wait_tx(); sortCast = 10 ; }
if (sortCast == 2) {delay(50);char message_out_rf[15] = "to:br_ss:poison" ; vw_send((uint8_t *)message_out_rf, 15); vw_wait_tx(); sortCast = 10 ; }
if (sortCast == 3) {delay(50);char message_out_rf[14] = "to:br_ss:soins" ; vw_send((uint8_t *)message_out_rf, 14); vw_wait_tx(); sortCast = 10 ; }
if (sortCast == 4) {delay(50);char message_out_rf[17] = "to:br_ss:bouclier" ; vw_send((uint8_t *)message_out_rf, 17); vw_wait_tx(); sortCast = 10 ; }
if (sortCast == 5) {delay(50);char message_out_rf[12] = "to:br_ss:feu" ; vw_send((uint8_t *)message_out_rf, 12); vw_wait_tx(); sortCast = 10 ; }


/*
if (message_in_bt == 56) {char message_out_rf[11] = "to:br_vie_1" ; vw_send((uint8_t *)message_out_rf, 11); vw_wait_tx();}
if (message_in_bt == 57) {char message_out_rf[12] = "to:br_mana_2" ; vw_send((uint8_t *)message_out_rf, 12); vw_wait_tx();}
if (message_in_bt == 58) {char message_out_rf[14] = "to:br_vieEnn_3" ; vw_send((uint8_t *)message_out_rf, 14); vw_wait_tx();}
if (message_in_bt == 59) {char message_out_rf[15] = "to:br_manaEnn_4" ; vw_send((uint8_t *)message_out_rf, 15); vw_wait_tx();}
*/

if (message_in_bt == 60) {delay(50);char message_out_rf[13] = "to:sw1_ss:feu" ; vw_send((uint8_t *)message_out_rf, 13); vw_wait_tx(); }
if (message_in_bt == 61) {delay(50);char message_out_rf[16] = "to:sw1_ss:poison" ; vw_send((uint8_t *)message_out_rf, 16); vw_wait_tx(); }
if (message_in_bt == 62) {delay(50);char message_out_rf[17] = "to:sw1_ss:berserk" ; vw_send((uint8_t *)message_out_rf, 17); vw_wait_tx(); }
if (message_in_bt == 63) {delay(50);char message_out_rf[14] = "to:sw1_ss:rien" ; vw_send((uint8_t *)message_out_rf, 14); vw_wait_tx(); }

if (qsdmessage_in_bt == 100) {delay(50);char message_out_rf[] = "to:sw1_ss:feu" ; vw_send((uint8_t *)message_out_rf, 13); vw_wait_tx(); }
if (qsdmessage_in_bt == 101) {delay(50);char message_out_rf[] = "to:br_vie_6" ; vw_send((uint8_t *)message_out_rf, 13); vw_wait_tx(); }
if (qsdmessage_in_bt == 102) {delay(50);char message_out_rf[] = "to:br_ss:bouclier" ; vw_send((uint8_t *)message_out_rf, 17); vw_wait_tx(); }
if (qsdmessage_in_bt == 103) {delay(50);char message_out_rf[] = "to:br_ss:ptrouge" ; vw_send((uint8_t *)message_out_rf, 16); vw_wait_tx(); }
if (qsdmessage_in_bt == 104) {delay(50);char message_out_rf[] = "to:br_ss:ptvert" ; vw_send((uint8_t *)message_out_rf, 15); vw_wait_tx(); } //161
if (qsdmessage_in_bt == 105) {delay(50);char message_out_rf[10] = "to:br_vie_" ; message_out_rf[10] = char(vie); vw_send((uint8_t *)message_out_rf, 13); vw_wait_tx(); }
                                 //  message_out_rf[] = "to:br_mana_" ; message_out_rf[11] = char(mana); vw_send((uint8_t *)message_out_rf, 12); vw_wait_tx(); }
if (qsdmessage_in_bt == 106) {delay(50);char message_out_rf[14] = "to:br_ss:soins" ; vw_send((uint8_t *)message_out_rf, 13); vw_wait_tx(); }
if (qsdmessage_in_bt == 107) {delay(50);char message_out_rf[15] = "to:br_vieEnn_" ; char qsdvie = '4' ; message_out_rf[13] = qsdvie ; vw_send((uint8_t *)message_out_rf, 15); vw_wait_tx(); }


/////////////////////////////////////////////////////////////////////BLUETOOTH OUT : remplacer valeurs par json/////////////////////////////////////////////////////////////////////////////////

if (object == "Piquemord") {byte messageConv = byte('a'); Serial.write(messageConv);}         //149
if (object == "Grimoire Arcanique" && action == "equipe" ) {byte messageConv = byte('b'); Serial.write(messageConv);}//150
if (object == "coffre") {byte messageConv = byte('c'); Serial.write(messageConv);}            //160
if (object == "borne de soins") {byte messageConv = byte('d'); Serial.write(messageConv);}   //170
if (object == "clef rouge" ) {byte messageConv = byte('e'); Serial.write(messageConv);}                      //180
if (object == "amulette") {byte messageConv = byte('f'); Serial.write(messageConv);}  //190
if (action == "enflamme") {byte messageConv = byte('g'); Serial.write(messageConv);}     //200
if (action == "drain de vie") {byte messageConv = byte('h'); Serial.write(messageConv); } //201
if (action == "boule de feu") {byte messageConv = byte('i'); Serial.write(messageConv);}  //
if (object == "Doominator") {byte messageConv = byte('j'); Serial.write(messageConv);}    //
//Serial.println();





/*
if (fromPlayer != "0" || toPlayer != "0" || object != "0" || action != "0") {
  Serial.println("{");
  Serial.print("\"action\": \"");
  Serial.print(action);
  Serial.println("\",");
  Serial.print("\"object\": [");
  Serial.print(object);
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





//if (message_out_rf > 0) {
message_in_bt = 0;
message_out_rf[0] = " ";
message_out_bt = 0 ;
object = "0" ;
action = "0" ;


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
