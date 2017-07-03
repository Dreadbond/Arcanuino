#include <VirtualWire.h>
#include <SPI.h>
#include <RFID.h>
#include <VirtualWire.h>


#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN,RST_PIN);
int serNum[5];
int cards[5] =   {136,4,91,233,62}  ;

int wifi[6] =   {136,4,91,233,62, 0}  ;
int telephone[6] =   {136,4,46,233,75, 0}  ;
int maison[6] =   {136,4,56,233,93, 0}  ;
int chevron[6] =   {136,4,81,233,52, 0}  ;
int reveil[6] =   {136,4,86,233,51, 0} ;
int sms[6] =   {136,4,51,233,86, 0}  ;
int bluetooth[6] =   {136,4,61,233,88, 0}  ;
int navigation[6] =   {136,4,76,233,41, 0}  ;
int power[6] =   {136,4,66,233,39, 0}  ;
int airplane[6] =   {136,4,71,233,34, 0}  ;

bool access = false;
unsigned long sscontact = 0 ;
/*
* Read a card using a mfrc522 reader on your SPI interface
* Pin layout should be as follows (on Arduino Uno):
* MOSI: Pin 11 / ICSP-4
* MISO: Pin 12 / ICSP-1
* SCK: Pin 13 / ISCP-3
* SS/SDA: Pin 10
* RST: Pin 9
*/

int vie = 0 ;
int mana = 0 ;
int ennVie = 0 ;
int ennMana = 0;
int rssi ; 

//char messActual[15];
byte message_in_com ;
char message_out_rf[0] ;

bool debug_mode = HIGH;



void setup() {
    pinMode(A0, INPUT);
    Serial.begin(9600);  // Debugging only
    Serial.println("Gant chopeur V0.1");
    vw_set_rx_pin(7);
    vw_set_tx_pin(6);
    // Initialise the IO and ISR
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);  // Bits per sec

    //vw_rx_start();       // Start the receiver PLL running

    pinMode(A5, INPUT); //digital
    pinMode(A4, INPUT); //RSSI
    pinMode(A3, OUTPUT);//5V

    digitalWrite(A5, LOW);
    digitalWrite(A3, HIGH);

    SPI.begin();
    rfid.init();



}

void loop() {

  if(sscontact < millis()) {
    if(rfid.isCard()){  //Serial.print("qdsqsd");
        if(rfid.readCardSerial()){
            /*
            Serial.print(rfid.serNum[0]);
            Serial.print(" ");
            Serial.print(rfid.serNum[1]);
            Serial.print(" ");
            Serial.print(rfid.serNum[2]);
            Serial.print(" ");
            Serial.print(rfid.serNum[3]);
            Serial.print(" ");
            Serial.print(rfid.serNum[4]);
            Serial.println("");*/
            
            //for(int x = 0; x < sizeof(cards); x++){

              for(int i = 0; i < 5; i++ ){
                  if(rfid.serNum[i] == wifi[i]) { wifi[5]++ ;} 
                  if(rfid.serNum[i] == telephone[i]) {telephone[5]++ ;} 
                  if(rfid.serNum[i] == maison[i]) { maison[5]++ ;}
                  if(rfid.serNum[i] == chevron[i]) { chevron[5]++ ;} 
                  if(rfid.serNum[i] == reveil[i]) { reveil[5]++ ;} 
                  
                  if(rfid.serNum[i] == sms[i]) { sms[5]++ ;} 
                  if(rfid.serNum[i] == bluetooth[i]) { bluetooth[5]++ ;} 
                  if(rfid.serNum[i] == navigation[i]) { navigation[5]++ ;} 
                  if(rfid.serNum[i] == power[i]) { power[5]++ ;} 
                  if(rfid.serNum[i] == airplane[i]) { airplane[5]++ ;} 

                  /*
                  Serial.print(i);
                  Serial.print(" ");
                  Serial.print(rfid.serNum[i]);
                  Serial.print(" ");
                  Serial.println(wifi[i]);*/
              }
              String messCarte = "?";
              
              if (wifi[5] >= 5) {messCarte = "wifi";  char message_out_rf[14] = "to_pl1_hevheal" ; vw_send((uint8_t *)message_out_rf, 14); vw_wait_tx();   }        //Borne de soins
              if (telephone[5] >= 5) {messCarte = "telephone "; char message_out_rf[14] = "to_pl1_amu_equ" ; vw_send((uint8_t *)message_out_rf, 14); vw_wait_tx(); }//Amulette
              if (maison[5] >= 5) {messCarte = "maison "; char message_out_rf[13] = "to_pl1_redkey" ; vw_send((uint8_t *)message_out_rf, 13); vw_wait_tx(); }       //Red key
              if (chevron[5] >= 5) {messCarte = "chevron "; char message_out_rf[15] = "to_pl1_dom1_equ" ; vw_send((uint8_t *)message_out_rf, 15); vw_wait_tx();  }  //Doominator
              if (reveil[5] >= 5) {messCarte = "reveil "; char message_out_rf[11] = "to_pl1_coff" ; vw_send((uint8_t *)message_out_rf, 11); vw_wait_tx(); }         //Coffre

              if (sms[5] >= 5) {messCarte = "sms ";  }
              if (bluetooth[5] >= 5) {messCarte = "bluetooth ";  }
              if (navigation[5] >= 5) {messCarte = "navigation ";  }
              if (power[5] >= 5) {messCarte = "power "; char message_out_rf[14] = "to_pl1_gr_equ" ; vw_send((uint8_t *)message_out_rf, 14); vw_wait_tx(); }         //Grimoire
              if (airplane[5] >= 5) {messCarte = "airplane "; char message_out_rf[13] = "to_pl1_sw_equ" ; vw_send((uint8_t *)message_out_rf, 13); vw_wait_tx(); }   //Epée
            //}

              Serial.println(messCarte) ;
        }
    wifi[5] = 0 ;
    telephone[5] = 0 ;
    maison[5] = 0 ;
    chevron[5] = 0 ;
    sms[5] = 0 ;
    
    reveil[5] = 0 ;
    bluetooth[5] = 0 ;
    navigation[5] = 0 ;
    power[5] = 0 ;
    airplane[5] = 0 ;
    //rfid.halt();
    }
  sscontact = millis() + 200 ;
  
  }

}


/*
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
  sscontact = millis() + 500 ;
  }

}*/
