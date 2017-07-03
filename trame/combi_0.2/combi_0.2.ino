int valSens1 ;
int valOldSens1 ;
int valSens2 ;
int valOldSens2 ;
int valSens3 ;
int valOldSens3 ;
int min1 = 40 ;
int max1 = 350 ;
int min2 = 40 ;
int max2 = 350 ;
int min3 = 40 ;
int max3 = 350 ;

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
    static int tab[5] ;                        
    static int index=0;
    int moyenne ;                

    tab[index]=param1;
    index++;
    if (index>=5) index=0;
   
    moyenne = (tab[0]+tab[1]+tab[2]+tab[3]+tab[4]) / 5;   
    return moyenne ;
}

int pipe(int param1){                                              //delay de nombres
    static int tab[10] ;                         
    static int index=0;
    int trueVal ;                    
    tab[index]=param1;
    index++;
    if (index>=10) index=0;

    int ival = index+1;
    if(ival >= 10) ival = ival-10;
    
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


  while (millis() < 2000) {        //ça calibre (fonction int calibreSens() ?)
valSens1 = analogRead(0);
if (valSens1 > max1) { max1 = valSens1 ;}
if (valSens1 < min1) { min1 = valSens1 ;}
Serial.println(valSens1);
  } 

 } 
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////LOOP////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////



void loop() {
  temps=millis();
  valSens1 = analogRead(0);
  
  valSens1 = map(valSens1, min1-20, max1+100, 255, 0);
  valSens1 = moyenne(valSens1);
  valSens1 = constrain(valSens1, 0, 255) ;
  valOldSens1 = pipe(valSens1);
  
 
  analogWrite(ledV1, valSens1);

attaque1=trtAttaque(valSens1, valOldSens1);



if (attaque1 == true && cooldown < temps) {
  int x=valSens1-valOldSens1 ;                   //tester la différece de valeurs
  Serial.print("Attaque 1!");
  Serial.println(x);
  cooldown = temps+200; 
  }
  
if (cooldown > temps)   digitalWrite(led13, HIGH); 
digitalWrite(led13, LOW); 

}






















