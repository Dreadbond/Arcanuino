#include <IRremote.h>

char messActual[10] = " ";
String cible ;
String oldCible ;
int tempsBuffer ;
int posChar ;

unsigned long gateReceive ;   //uniquement pour réception char
unsigned long gateCible ;         //pour la cible en elle-même

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}


void loop() {
//  oldCible = cible ;

//if (gateReceive > millis()) {
      
      
if (irrecv.decode(&results)) {        
  messActual[posChar] = char(results.value) ;
  //Serial.println(results.value, HEX);
  //cible = results.value ;
  //Serial.print(char(results.value));
  cible = String(messActual);
  irrecv.resume(); // Receive the next value
  gateReceive = millis() + 50 ;
  posChar++ ;
  }


if (gateReceive < millis() ) {
    if (cible != " " ) {Serial.print(cible);}
  cible = " ";
//  messActual[] = " ";
  posChar = 0 ;
}




  //if (cible != oldCible) {}
 
}
