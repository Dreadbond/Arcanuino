int valSens1 ;
int valOldSens1 ;
int valSens2 ;
int valOldSens2 ;
int valSens3 ;
int valOldSens3 ;
int min1 = 100;
int max1 = 100 ;
int min2 ;
int max2 ;
int min3 ;
int max3 ;

int palier = 40 ;            //faire rapport division
//int vit = 5 ;            //vitesse, temps entre les 2 comparaisons de valeurs
boolean attaque1 = false;
boolean attaque2 = false;
boolean attaque3 = false;

const int bouton = 2 ;
const int led13 = 13 ;
unsigned long cooldown = 1000 ;
unsigned long temps = 0 ;
const int ledV1 = 9 ;
const int ledV2 = 10 ;
const int ledV3 = 11 ;

//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////FONCTIONS////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

int moyenne(int param1) {                                           //faisage de moyenne
    static int tab[5];                        
    static int index=0;
    int moyenne ;                

    tab[index]=param1;
    index++;
    if (index >= 5) index=0;
   
    moyenne = (tab[0]+tab[1]+tab[2]+tab[3]+tab[4]) / 5;   
    return moyenne ;
}

int pipe(int param1){                                  //delay de nombres. 10 au début
    static int tab[4] ;                         
    static int index=0;
    int trueVal ;                    
    tab[index]=param1;
    index++;
    if (index>=4) index=0;

    int ival = index+1;
    if(ival >= 4) ival = ival-4;
    
    trueVal = tab[ival];
  return trueVal;  }

  
bool trtAttaque (int sensNow, int sensAvant) {                      //attaque
bool coup = false ;
   
  if(sensNow - sensAvant <= -palier || sensNow - sensAvant >= palier) {
    return coup = true ;}
 

return coup = false  ;
  }
//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////SETUP//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


void setup() {
Serial.begin(9600);
pinMode(led13, OUTPUT);
pinMode(ledV1, OUTPUT) ;
pinMode(ledV2, OUTPUT) ;
pinMode(ledV3, OUTPUT) ;


  while (millis() < 2000) {        
valSens1 = analogRead(0);
if (valSens1 < max1) { max1 = valSens1 ;}
if (valSens1 > min1) { min1 = valSens1 ;}/*
valSens2 = analogRead(1);
if (valSens2 > max2) { max2 = valSens2 ;}
if (valSens2 < min2) { min2 = valSens2 ;}
valSens3 = analogRead(2);
if (valSens3 > max3) { max3 = valSens3 ;}
if (valSens3 < min3) { min3 = valSens3 ;}*/
  Serial.print(valSens1);
  Serial.print(" ");
  Serial.print(min1);
  Serial.print(" ");
  Serial.println(max1);
  } 

 } 
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////LOOP////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////



void loop() {
  temps=millis();
  valSens1 = analogRead(0);
  valSens1 = map(valSens1, max1, min1, 0, 255);
  valSens1 = moyenne(valSens1);
  valSens1 = constrain(valSens1, 0, 255) ;
  valOldSens1 = pipe(valSens1);
   // Serial.print(valSens1);
   // Serial.print(" ");
   // Serial.println(valOldSens1);
  
   /*
  Serial.print(valSens1);
  Serial.println(" ");
 
    valSens2 = analogRead(1);
  valSens2 = map(valSens2, min2, max2, 255, 0);
  valSens2 = moyenne(valSens2);
  valSens2 = constrain(valSens2, 0, 255) ;
  valOldSens2 = pipe(valSens2);
  
    valSens3 = analogRead(2);
  valSens3 = map(valSens3, min3, max3, 255, 0);
  valSens3 = moyenne(valSens3);
  valSens3 = constrain(valSens3, 0, 255) ;
  valOldSens3 = pipe(valSens3);
  */
 
  analogWrite(ledV1, valSens1);
  analogWrite(ledV2, valSens2);
  analogWrite(ledV3, valSens3);

attaque1=trtAttaque(valSens1, valOldSens1);
attaque2=trtAttaque(valSens2, valOldSens2);
attaque3=trtAttaque(valSens3, valOldSens3);
  


if (attaque1 == true && cooldown < temps) {
  int x=valSens1-valOldSens1 ;                   //tester la différence de valeurs
  Serial.print("Attaque 1!");
  Serial.println(x);
  cooldown = temps+200; 
  }
  
if (cooldown > temps)   digitalWrite(led13, HIGH); 
digitalWrite(led13, LOW); 

}






















