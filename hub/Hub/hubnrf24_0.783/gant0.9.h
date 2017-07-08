
typedef struct{
  char from[8];
  char to[8];
  int x, y, z, p, i, m, an, au;
  int fing[5];

  int sensi = 50 ;

  int acc[3];
  char oldWho ;
  char who ;

  int state ;
  int oldState ;
  
  int posGeste = 1 ; //sorte d'index pour currentMovement.
  int currentMovement[20];
  int handUp[4] = {1, 3, 5, 4} ;
  int throwMove[4] = {1, 4, 6, 4} ;

  unsigned long coolReset ;

  String target = "!vide" ;

  void posReset(){
    for (int i=0; i<20 ; i++) {currentMovement[i] = 0 ;}
    posGeste = 1 ;
    currentMovement[0] = state ;
  
    handUp[0] = 1 ;
    throwMove[0] = 1 ;


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

////////////////////////////////////////////////////////////////////////////Feedbacks


  void fireBallCastFb() {
      radio.stopListening();
      radio.openWritingPipe(pipes[5]);
      strcpy(sendBox.to, ":gant"); strcpy(sendBox.param, "fireCast"); sendBox.value= 1; 
      radio.write( &sendBox, sizeof(sendBox) );
      radio.startListening();
  }



  void throwMoveFb() {
      //for (int i=0 ; i< 3 ; i++) {
    Serial.println("Boule de feu !"); 
    radio.stopListening();
      radio.openWritingPipe(pipes[5]);
      strcpy(sendBox.to, ":gant"); strcpy(sendBox.param, "fireball"); sendBox.value= 1; 
      radio.write( &sendBox, sizeof(sendBox) );
      radio.startListening();
    //}
      
    posReset();
        fireBallBool = 0;
    protectionBool = 0 ;
  }
  

  void ProtectionSpellCastFb() {
      radio.stopListening();
      radio.openWritingPipe(pipes[5]);
      strcpy(sendBox.to, ":gant"); strcpy(sendBox.param, "protCast"); sendBox.value= 1; 
      radio.write( &sendBox, sizeof(sendBox) );
      radio.startListening();
  }

  void handUpfb() {
  //for (int i=0 ; i< 5 ; i++) {
      Serial.println("Protection !"); 

  radio.stopListening();
    radio.openWritingPipe(pipes[5]);
    strcpy(sendBox.to, ":gant"); strcpy(sendBox.param, "protec"); sendBox.value= 1; 
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
  //}
  posReset();
      fireBallBool = 0;
    protectionBool = 0 ;
}

bool pBool, iBool, mBool, anBool, auBool ;
bool fireBallBool, protectionBool ;

  
} infosGantStruct ;

infosGantStruct glDa;


void printGloveData(){
     Serial.print(glDa.x);   Serial.print(" ");
     Serial.print(glDa.y);   Serial.print(" ");
     Serial.print(glDa.z);   Serial.print(" ");
     
     Serial.print(glDa.p);   
     Serial.print(" ");
     Serial.print(glDa.i);   
     Serial.print(" ");
     Serial.print(glDa.m);   
     Serial.print(" ");
     Serial.print(glDa.an);   
     Serial.print(" ");
     Serial.println(glDa.au);  
}



void gantCode(String to, String param, float value){
  //glDa.handUpfb() ;
  if (to == ":gant" && justReceive) {
        if (param == "x") {glDa.acc[0] = value;}
        if (param == "y") {glDa.acc[1] = value;}
        if (param == "z") {glDa.acc[2] = value;}

        if (param == "p") {glDa.fing[0] = value;}
        if (param == "i") {glDa.fing[1] = value;}
        if (param == "m") {glDa.fing[2] = value;}
        if (param == "an") {glDa.fing[3]= value;}
        if (param == "au") {glDa.fing[4]= value;}  //printGloveData(); 
        if (param.startsWith("!")) {
      glDa.target = param ;
      if (param.startsWith("!vide")) {
        Serial.println("Pas de cible.");
      }
      else 
      {
        Serial.print("Cible : "); Serial.println(glDa.target);
      }
    }
 }


 
//fonction state
glDa.x = glDa.acc[0] ; 
glDa.y = glDa.acc[1] ;
glDa.z = glDa.acc[2] ;

  if (glDa.x<0) {glDa.x *= -1;}
  if (glDa.y<0) {glDa.y *= -1;}
  if (glDa.z<0) {glDa.z *= -1;}
  
int big=0;

if (glDa.x > big) {big = glDa.x ; glDa.who = 'x' ;}
if (glDa.y > big) {big = glDa.y ; glDa.who = 'y' ;}
if (glDa.z > big) {big = glDa.z ; glDa.who = 'z' ;}

  glDa.oldState = glDa.state;
  switch(glDa.who){
    case 'x':                                         //azimuth
    if (glDa.acc[0] < -1* glDa.sensi) {glDa.state = 1;}  //Haut
    else 
    if (glDa.acc[0] >  glDa.sensi) {glDa.state = 2;}     //Bas
    break;
  
    case 'y':
    if (glDa.acc[1] < -1* glDa.sensi) {glDa.state = 3;}    //Gauche
    else 
    if (glDa.acc[1] >  glDa.sensi) {glDa.state = 4;}       //Droite
    break;
  
    case 'z':                                         //estoc
    if (glDa.acc[2] < -1* glDa.sensi) {glDa.state = 5;}   //Dessus
    else 
    if (glDa.acc[2] >  glDa.sensi) {glDa.state = 6;}      //Dessous
    break;
    }//end switch
    
if (glDa.oldState != glDa.state){Serial.println(glDa.state);}

long total ;
for (int i=0 ; i <5 ; i++) {
  total += glDa.fing[i] ;
}
total /= 5 ;
//Serial.print(total); Serial.print(" ") ; 
//for (int i=0 ; i <5 ; i++) {Serial.print(glDa.fing[i]) sps }spr




//if (glDa.fing[0]   //pas assez sensible
if (glDa.fing[1] < 1000) {glDa.iBool = 1; } else {glDa.iBool=0;} //Serial.println("index");
if (glDa.fing[2] < 950) {glDa.mBool = 1; } else {glDa.mBool=0;} //Serial.println("majeur");
if (glDa.fing[3] < 1000) {glDa.anBool = 1; } else {glDa.anBool=0;} //Serial.println("annulaire");
if (glDa.fing[4] < 950) {glDa.auBool = 1; } else {glDa.auBool=0;} //Serial.println("auri");



  if (!glDa.iBool && glDa.mBool && glDa.anBool && !glDa.auBool) {glDa.fireBallBool = 1; glDa.fireBallCastFb();} //Serial.println("Fireball en préparation ...");
  if (glDa.state == glDa.throwMove[glDa.throwMove[0] ] ) { //&& glDa.fireBallBool
    glDa.posGeste++;
    glDa.throwMove[0]++;
    //Serial.print("handUp "); Serial.println(glDa.handUp[0]);
    glDa.moreTime();
  }

  if (glDa.iBool && !glDa.mBool && !glDa.anBool && !glDa.auBool) {glDa.protectionBool = 1; glDa.ProtectionSpellCastFb();} // Serial.println("Protection ...");
  if (glDa.state == glDa.handUp[glDa.handUp[0] ]) {  //&& glDa.protectionBool
    glDa.posGeste++;
    glDa.handUp[0]++;
    //Serial.print("handUp "); Serial.println(glDa.handUp[0]);
    glDa.moreTime();
  }
  
  if (glDa.throwMove[0] == sizeof(glDa.throwMove)/2 && glDa.fireBallBool ) {glDa.throwMoveFb();}

  if (glDa.handUp[0] == sizeof(glDa.handUp)/2 && glDa.protectionBool) {glDa.handUpfb() ;}

if (glDa.coolReset < millis()) {glDa.posReset();}



 
}








