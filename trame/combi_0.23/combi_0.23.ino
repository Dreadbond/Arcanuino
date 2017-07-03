int valSens1 ;
int valOldSens1 ;
int valSens2 ;
int valOldSens2 ;
int valSens3 ;
int valOldSens3 ;
int min1 = 50;
int max1 = 300 ;
int min2 = 10;
int max2 = 210;
int min3 = 10;
int max3 = 720;

int palier1 = 200 ;            //faire rapport division
int palier2 = 55 ;
int palier3 = 10 ;
//int vit = 5 ;            //vitesse, temps entre les 2 comparaisons de valeurs
boolean attaque1 = false;
boolean attaque2 = false;
boolean attaque3 = false;

const int boutonCal = 2 ;
const int led13 = 13 ;
unsigned long cooldown1 = 1000 ;
unsigned long cooldown2 = 1000 ;
unsigned long cooldown3 = 1000 ;
unsigned long temps = 0 ;
const int ledV1 = 9 ;
const int ledV2 = 10 ;
const int ledV3 = 11 ;

//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////FONCTIONS////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

int moyenne1(int param1) {                                           //faisage de moyenne
    static int tab[5];                        
    static int index=0;
    int moyenne ;                

    tab[index]=param1;
    index++;
    if (index >= 5) index=0;
   
    moyenne = (tab[0]+tab[1]+tab[2]+tab[3]+tab[4]) / 5;   
    return moyenne ;
}

int pipe1(int param1){                                  //delay de nombres. 10 au début
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

  int moyenne2(int param1) {                                           //faisage de moyenne2
    static int tab[5];                        
    static int index=0;
    int moyenne ;                

    tab[index]=param1;
    index++;
    if (index >= 5) index=0;
   
    moyenne = (tab[0]+tab[1]+tab[2]+tab[3]+tab[4]) / 5;   
    return moyenne ;
}

int pipe2(int param1){                                  //delay de nombres. 10 au début
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

  int moyenne3(int param1) {                                           //faisage de moyenne3
    static int tab[5];                        
    static int index=0;
    int moyenne ;                

    tab[index]=param1;
    index++;
    if (index >= 5) index=0;
   
    moyenne = (tab[0]+tab[1]+tab[2]+tab[3]+tab[4]) / 5;   
    return moyenne ;
}

int pipe3(int param1){                                  //delay de nombres. 10 au début
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

  
bool trtAttaque1(int sensNow, int sensAvant) {                      //attaque 1
bool coup = false ;
  if(sensNow - sensAvant <= -palier1 || sensNow - sensAvant >= palier1) {
    return coup = true ;}
return coup = false  ;
  }

  bool trtAttaque2(int sensNow, int sensAvant) {                      //attaque 2
bool coup = false ;
  if(sensNow - sensAvant <= -palier2 || sensNow - sensAvant >= palier2) {
    return coup = true ;}
return coup = false  ;
  }

  bool trtAttaque3(int sensNow, int sensAvant) {                      //attaque 3
bool coup = false ;
  if(sensNow - sensAvant <= -palier3 || sensNow - sensAvant >= palier3) {
    return coup = true ;}
return coup = false  ;
  }

void calibrage() {
    while (millis() < 6000) {        
valSens1 = analogRead(0);
if (valSens1 < max1) { max1 = valSens1 ;}
if (valSens1 > min1) { min1 = valSens1 ;}
valSens2 = analogRead(1);
if (valSens2 > max2) { max2 = valSens2 ;}
if (valSens2 < min2) { min2 = valSens2 ;}
valSens3 = analogRead(2);
if (valSens3 > max3) { max3 = valSens3 ;}
if (valSens3 < min3) { min3 = valSens3 ;}
  Serial.print(valSens1);
  Serial.print(" ");
  Serial.print(valSens2);
  Serial.print(" ");
  Serial.println(valSens3);
  }
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
pinMode(boutonCal, INPUT);


/*  while (millis() < 4000) {        
valSens1 = analogRead(0);
if (valSens1 < max1) { max1 = valSens1 ;}
if (valSens1 > min1) { min1 = valSens1 ;}
valSens2 = analogRead(1);
if (valSens2 > max2) { max2 = valSens2 ;}
if (valSens2 < min2) { min2 = valSens2 ;}
valSens3 = analogRead(2);
if (valSens3 > max3) { max3 = valSens3 ;}
if (valSens3 < min3) { min3 = valSens3 ;}
  Serial.print(valSens1);
  Serial.print(" ");
  Serial.print(valSens2);
  Serial.print(" ");
  Serial.println(valSens3);
  } 
*/
 } 
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////LOOP////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void loop() {
  temps=millis();
  
  
  valSens1 = analogRead(2);
  valSens1 = moyenne1(valSens1);
  valOldSens1 = pipe1(valSens1);

  valSens2 = analogRead(1);
  valSens2 = moyenne2(valSens2);
  valOldSens2 = pipe2(valSens2);
  
  valSens3 = analogRead(0);
  valSens3 = moyenne3(valSens3);
  valOldSens3 = pipe3(valSens3);

  Serial.print(valSens1);
  Serial.print(" ");
  Serial.print(valSens2);
  Serial.print(" ");
  Serial.print(valSens3);
  Serial.println(" ");
 

attaque1=trtAttaque1(valSens1, valOldSens1);
attaque2=trtAttaque2(valSens2, valOldSens2);
attaque3=trtAttaque3(valSens3, valOldSens3);



if (digitalRead(boutonCal) == HIGH) {
  calibrage() ;
  }
if (attaque1 == true && cooldown1 < temps) {
  int x=valSens1-valOldSens1 ;                   //tester la différence de valeurs
  Serial.print("Attaque 1! ");
  Serial.println(x);
  Serial.print(valSens1);
  Serial.print(" ");
  Serial.println(valOldSens1);
  cooldown1 = temps+200; 
  }
  
if (attaque2 == true && cooldown2 < temps) {
  int x=valSens2-valOldSens2 ;                   //tester la différence de valeurs
  Serial.print("Attaque 2! ");
  Serial.println(x);
  Serial.print(valSens2);
  Serial.print(" ");
  Serial.println(valOldSens2);
  cooldown2 = temps+200; 
  }
  
if (attaque3 == true && cooldown3 < temps) {
  int x=valSens3-valOldSens3 ;                   //tester la différence de valeurs
  Serial.print("Attaque 3! ");
  Serial.println(x);
  Serial.print(valSens3);
  Serial.print(" ");
  Serial.println(valOldSens3);
  cooldown3 = temps+200; 
  }







  valSens1 = map(valSens1, max1, min1, 0, 255);
  valSens1 = constrain(valSens1, 0, 255) ;
  valSens2 = map(valSens2, max1, min1, 0, 255);
  valSens2 = constrain(valSens2, 0, 255) ;
  valSens3 = map(valSens3, max1, min1, 0, 255);
  valSens3 = constrain(valSens3, 0, 255) ;
  analogWrite(ledV1, valSens1);
  analogWrite(ledV2, valSens2);
  analogWrite(ledV3, valSens3);






}






















