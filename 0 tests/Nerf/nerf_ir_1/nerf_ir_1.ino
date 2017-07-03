    #include <IRremote.h>
    IRsend irsend;               // déclaration de l'objet émetteur (pin D3 obligatoire)


float ammo = 25;
float DisplayAmmo ;
int ammoOld = 0;

const int butAmmo = 8 ;
const int IRled = 3 ;
const int IRrei = 2 ;
const int Led = 13 ;
const int Display = 9 ;

bool beam ;
bool beamflag = HIGH;
bool butApress;
bool butApressFlag = HIGH;



void setup() {

pinMode(butAmmo, INPUT);
pinMode(IRrei, INPUT);
pinMode(IRled, OUTPUT);
pinMode(Led, OUTPUT);
pinMode(Display, OUTPUT);

irsend.enableIROut(38);               //enable signal tout le temps

Serial.begin(9600);
}

void loop() {
irsend.mark(0); // envoi du signal pour une durée illimitée

//beam = digitalRead(IRrei);
  boolean mesure1 = digitalRead(IRrei);   // première mesure     pour éviter le rebond
  delay(5);                               // délai
  boolean mesure2 = digitalRead(IRrei);   // seconde mesure
  beam = mesure1 * mesure2;               // comparaison


if (beam == LOW && beamflag == HIGH) {
--ammo ;
Serial.print("Munitions : ");
Serial.println(ammo); 
beamflag = LOW; }

if (beam == HIGH) {
  beamflag = HIGH;
  digitalWrite(Led, HIGH);}

if (beam == LOW) {
  digitalWrite(Led, LOW);}


butApress = digitalRead(butAmmo);
if (butApress == HIGH && butApressFlag == HIGH) {
++ammo ; 
Serial.print("Munitions : ");
Serial.println(ammo); 
butApressFlag = LOW ;}

if (butApress == LOW) {butApressFlag = HIGH;}

DisplayAmmo = ammo/24*255 ;
constrain(DisplayAmmo, 0, 255) ;
analogWrite(Display, DisplayAmmo);



}
