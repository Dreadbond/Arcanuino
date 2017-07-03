
typedef struct {
int x ;
int y ;
int z ;

int acc[3];

int sensi = 70 ;

char oldWho ;
char who ;

int state ;
int oldState ;

int posGeste ; //sorte d'index pour currentMovement.
int currentMovement[20];
int movement1[3] = {2, 3, 1} ;
int movement2[2] = {1, 5} ;
int movement2bis[3] = {1, 6, 5} ;

unsigned long coolReset ;

void posReset(){
  for (int i=0; i<20 ; i++) {currentMovement[i] = 0 ;}
  posGeste = 0 ;
  currentMovement[0] = state ;
  //Serial.println("Reset");
  }

void moreTime(){
  coolReset = millis() + 400 ;
  }

void imprMouvement(){
Serial.println("---------------------");
for (int i=0; i<20 ; i++) {Serial.print(currentMovement[i]); sps}
Serial.println();
}


}//fin struct épée
infosEpee ;

infosEpee sword ;




void swordCode(String to, String param, float value){

if (to == ":sword" && justReceive) {
  //faire de ça une fonction
  if(param == "x") { sword.acc[0] = value ; sword.x = value ; }
  if(param == "y") { sword.acc[1] = value ; sword.y = value ;}
  if(param == "z") { sword.acc[2] = value ; sword.z = value ;}
  }


  if (sword.x<0) {sword.x *= -1;}
  if (sword.y<0) {sword.y *= -1;}
  if (sword.z<0) {sword.z *= -1;}
  
int big=0;

if (sword.x > big) {big = sword.x ; sword.who = 'x' ;}
if (sword.y > big) {big = sword.y ; sword.who = 'y' ;}
if (sword.z > big) {big = sword.z ; sword.who = 'z' ;}



  sword.oldState = sword.state;
  switch(sword.who){
    case 'x':                                         //azimuth
    if (sword.acc[0] < -1* sword.sensi) {sword.state = 1;}    //Haut
    else 
    if (sword.acc[0] >  sword.sensi) {sword.state = 2;}   //Bas
    break;
  
    case 'y':
    if (sword.acc[1] < -1* sword.sensi) {sword.state = 3;}    //Gauche
    else 
    if (sword.acc[1] >  sword.sensi) {sword.state = 4;}    //Droite
    break;
  
    case 'z':                                         //estoc
    if (sword.acc[2] < -1* sword.sensi) {sword.state = 5;}   //Dessus
    else 
    if (sword.acc[2] >  sword.sensi) {sword.state = 6;}    //Dessous
    break;
    }//end switch

if (sword.oldState != sword.state) 
    {
    sword.posGeste++;
    //sword.currentMovement[sword.posGeste] = sword.oldState ;
    //sword.currentMovement[sword.posGeste + 1] = sword.state ;
    sword.currentMovement[sword.posGeste] = sword.state ;
    sword.imprMouvement();
    sword.moreTime();
    
    }
  


if ( memcmp( (const void *)sword.currentMovement, (const void *)sword.movement1, sizeof(sword.movement1)) == 0) {Serial.println("Vers le ciel.");}
if ( memcmp( (const void *)sword.currentMovement, (const void *)sword.movement2, sizeof(sword.movement2)) == 0) {Serial.println("En avant !");}
if ( memcmp( (const void *)sword.currentMovement, (const void *)sword.movement2bis, sizeof(sword.movement2bis)) == 0) {Serial.println("En avant !");}

if(sword.coolReset < millis()) {sword.posReset();}

}//fin de boucle swordCode






//faire détecteur de coups : changements violents

//trajectoir + force ? "couronné puissance 10"

//faire détecteur trajectoire : longue lignée, accumulation

//faire déclaration état : position, action, violent
//plusieurs états possibles

