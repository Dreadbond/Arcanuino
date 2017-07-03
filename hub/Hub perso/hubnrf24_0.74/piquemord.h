
typedef struct {
int x ;
int y ;
int z ;

int acc[3];
long capa ;
bool capaFlag;
unsigned long nextHit ;

int sensi = 50 ;

char oldWho ;
char who ;

int state ;
int oldState ;

int posGeste = 1 ; //sorte d'index pour currentMovement.
int currentMovement[20];
int moulinet[5] = {1, 5, 2, 4, 1} ;
int movement2[4] = {1, 2, 3, 1} ;
int movement2bis[4] = {1, 2, 5, 1} ;
int clockWise[6] = {1, 5, 4, 6, 3, 5} ;
int antiClockWise[6] = {1, 5, 3, 6, 4, 5} ;

/*
int combos[3][4]={
{0, 1, 6, 5},
{0, 2, 3, 1},
{0, 2, 5, 1}
};*/

unsigned long coolReset ;

void posReset(){
  for (int i=0; i<20 ; i++) {currentMovement[i] = 0 ;}
  posGeste = 1 ;
  currentMovement[0] = state ;

  moulinet[0] = 1 ;
  movement2[0] = 1 ;
  movement2bis[0] = 1 ;
  clockWise[0] = 1 ;
  antiClockWise[0] = 1 ;

  //Serial.println("Reset");
  }

void moreTime(int val=700){
  coolReset = millis() + val ;
  }

void imprMouvement(){
Serial.println("---------------------");
for (int i=0; i<20 ; i++) {Serial.print(currentMovement[i]); sps}
Serial.println();
}

void movement2fb(int val = 1000) {
  Serial.println("Protection !"); 
  radio.stopListening();
    radio.openWritingPipe(pipes[4]);
    strcpy(sendBox.to, ":sword"); strcpy(sendBox.param, "protec"); sendBox.value= 1; 
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
  posReset();
}

void movement2bisFb(int val = 1000) {
  Serial.println("En avant !"); 
  radio.stopListening();
    radio.openWritingPipe(pipes[4]);
    strcpy(sendBox.to, ":sword"); strcpy(sendBox.param, "enavant"); sendBox.value= 10; 
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
  posReset();
}

void clockWiseFb(int val = 1000) {
  Serial.println("clockWise !"); 
  radio.stopListening();
    radio.openWritingPipe(pipes[4]);
    strcpy(sendBox.to, ":sword"); strcpy(sendBox.param, "clock"); sendBox.value= 1; 
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
  posReset();
}

void antiClockWiseFb(int val = 1000) {
  Serial.println("antiClockWise !");
  radio.stopListening();
    radio.openWritingPipe(pipes[4]); 
    strcpy(sendBox.to, ":sword"); strcpy(sendBox.param, "antclck"); sendBox.value= 1; 
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
  posReset();
}

void moulinetFb(int val = 1000) {
  Serial.println("Moulinet !"); 
  radio.stopListening();
    radio.openWritingPipe(pipes[4]);
    strcpy(sendBox.to, ":sword"); strcpy(sendBox.param, "moulin"); sendBox.value= 1; 
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
  posReset();
}

}//fin struct épée
infosEpee ;

infosEpee sword ;




void swordCode(String to, String param, float value){

if (to == ":sword" && justReceive) {
  //faire de ça une fonction
  if(param == "x") { sword.acc[0] = value ; }
  if(param == "y") { sword.acc[1] = value ; }
  if(param == "z") { sword.acc[2] = value ; }

  if(param == "capa") {sword.capa = value ; }
  }

//fonction state
sword.x = sword.acc[0] ; 
sword.y = sword.acc[1] ;
sword.z = sword.acc[2] ;

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
    if (sword.acc[0] < -1* sword.sensi) {sword.state = 1;}  //Haut
    else 
    if (sword.acc[0] >  sword.sensi) {sword.state = 2;}     //Bas
    break;
  
    case 'y':
    if (sword.acc[1] < -1* sword.sensi) {sword.state = 3;}    //Gauche
    else 
    if (sword.acc[1] >  sword.sensi) {sword.state = 4;}       //Droite
    break;
  
    case 'z':                                         //estoc
    if (sword.acc[2] < -1* sword.sensi) {sword.state = 5;}   //Dessus
    else 
    if (sword.acc[2] >  sword.sensi) {sword.state = 6;}      //Dessous
    break;
    }//end switch
    
if (sword.oldState != sword.state){Serial.println(sword.state);}

/*
if (sword.oldState != sword.state){
    sword.posGeste++;

    sword.currentMovement[sword.posGeste] = sword.state ;
    sword.imprMouvement();
    sword.moreTime();
    }
  //fin fonction state
  */

  if (sword.state == sword.movement2[sword.movement2[0] ]) {
    sword.posGeste++;
    sword.movement2[0]++;
    //Serial.print("movement2 "); Serial.println(sword.movement2[0]);
    sword.moreTime();
  }

  if (sword.state == sword.movement2bis[sword.movement2bis[0] ]) {
    sword.posGeste++;
    sword.movement2bis[0]++;
    //Serial.print("movement2bis "); Serial.println(sword.movement2bis[0]);
    sword.moreTime();
  }

  if (sword.state == sword.clockWise[sword.clockWise[0] ]) {
    sword.posGeste++;
    sword.clockWise[0]++;
    //Serial.print("clockWise "); Serial.println(sword.clockWise[0]);
    sword.moreTime();
  }

  if (sword.state == sword.antiClockWise[sword.antiClockWise[0] ]) {
    sword.posGeste++;
    sword.antiClockWise[0]++;
    //Serial.print("antiClockWise "); Serial.println(sword.antiClockWise[0]);
    sword.moreTime();
  }

  if (sword.state == sword.moulinet[sword.moulinet[0] ]) {
    sword.posGeste++;
    sword.moulinet[0]++;
    //Serial.print("moulinet "); Serial.println(sword.moulinet[0]);
    sword.moreTime();
  }


  if (sword.clockWise[0] == sizeof(sword.clockWise)/2 ) {sword.clockWiseFb() ;}
  if (sword.antiClockWise[0] == sizeof(sword.antiClockWise)/2 ) {sword.antiClockWiseFb() ;}
  if (sword.movement2[0] == sizeof(sword.movement2)/2 ) {sword.movement2fb() ;}
  if (sword.movement2bis[0] == sizeof(sword.movement2bis)/2 ) {sword.movement2bisFb() ;}
  if (sword.moulinet[0] == sizeof(sword.moulinet)/2 ) {sword.moulinetFb() ;}

//sword.movement2bisFb() ;

if (sword.capa) {
    if (sword.capaFlag && sword.nextHit){
      Serial.println("Hit !");
      sword.capaFlag = LOW ;
    }
    sword.nextHit = millis() + 200 ;
}

if (millis() > sword.nextHit) {sword.capaFlag = HIGH ;}

if (sword.coolReset < millis()) {sword.posReset();}

sword.capa = 0 ; 

}//fin de boucle swordCode






//faire détecteur de coups : changements violents

//trajectoir + force ? "couronné puissance 10"

//faire détecteur trajectoire : longue lignée, accumulation

//faire déclaration état : position, action, violent
//plusieurs états possibles

