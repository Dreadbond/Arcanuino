// pipe 4 : 0xF0F0F0F042
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
  String finger ;
  
  int posGeste = 1 ; //sorte d'index pour currentMovement.
  int currentMovement[20];
  int handUp[4] = {1, 3, 5, 4} ;
  int throwMove[4] = {1, 4, 6, 4} ;
  String sendSerial = "" ;

  unsigned long coolReset ;
  unsigned long fingNextSend ;

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



void gantCode(String from, String param, float value=1){
  //glDa.handUpfb() ;
  if (from == ":gant" && justReceive) {
        if (param == "x") {glDa.acc[0] = value;}
        if (param == "y") {glDa.acc[1] = value;}
        if (param == "z") {glDa.acc[2] = value;}

        if (param == "p") {glDa.fing[0] = value;}
        if (param == "i") {glDa.fing[1] = value;}
        if (param == "m") {glDa.fing[2] = value;}
        if (param == "an") {glDa.fing[3]= value;}
        if (param == "au") {glDa.fing[4]= value;}  //printGloveData(); 
        
        if (param.startsWith("!") && 1==0 ) {  //Ca bloque !!!!!!
        
          glDa.target = param ;
          if (param.startsWith("!vide")) {

            StaticJsonBuffer<100> jsonBuffer;
            JsonObject& root = jsonBuffer.createObject();
          
            root["to"]    = IDObject ;   //"!111111"
            root["from"]  = ":gant" ;
          
            root["param"] =  "target";
            root["value"] =  "!vide";
           
            root.printTo(Serial);
            Serial.println();

            //Serial.println("Pas de cible.");
          }
          else 
          {
            StaticJsonBuffer<100> jsonBuffer;
            JsonObject& root = jsonBuffer.createObject();
          
            root["to"]    = IDObject ;   //"!111111"
            root["from"]  = ":gant" ;
          
            root["param"] =  "target";
            root["value"] =  param;
           
            root.printTo(Serial);
            Serial.println();
            //Serial.print("Cible : "); Serial.println(glDa.target);
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
    
if (glDa.oldState != glDa.state){//Serial.println(glDa.state);
        StaticJsonBuffer<100> jsonBuffer;
        JsonObject& root = jsonBuffer.createObject();
      
        root["to"]    = IDObject ;   //"!111111"
        root["from"]  = ":gant" ;
      
        root["param"] =  "position";
        root["value"] =  glDa.state;
       
        root.printTo(Serial);
        Serial.println();
}


if (glDa.fingNextSend < millis() && 1==0 ) {

        StaticJsonBuffer<100> jsonBuffer;
        JsonObject& root = jsonBuffer.createObject();

        root["to"]    = IDObject ;   //"!111111"
        root["from"]  = ":gant" ;

        root["param"] = "fingers" ;

        JsonArray& data = root.createNestedArray("value");
        for (int i=0 ; i<5 ; i++) {
          data.add(glDa.fing[i]);
          //root["value"] =  fingerValues ;
        }
        
        root.printTo(Serial);
        Serial.println();

        glDa.fingNextSend = millis() + 150 ;
}

if (glDa.coolReset < millis()) {glDa.posReset();}

}

void gantReceive() {
  
  for (int i=0 ; i< inMessage.length() ; i++) {
    if (inMessage.startsWith(":gant", i) ) {
    for (int j=0 ; j < inMessage.length() ; j++) {
      //{"to":":gant","from":"!111111","param":"fireball","value":5}
      //{"to":":gant","from":"!111111","param":"barrier","value":15}
      //{"to":":gant","from":"!111111","param":"fireCast","value":5}
      //{"to":":gant","from":"!111111","param":"protCast","value":1}
      //{"to":":gant","from":"!111111","param":"vampire","value":1}
      
      if (inMessage.startsWith("barrier", j) ){
          strcpy(sendBox.to, ":gant"); strcpy(sendBox.param, "protec"); sendBox.value= 1; 

          radio.openWritingPipe(pipes[5]);  //0xF0F0F0F042
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
          ////inMessage = "" ; 
      break;
      }

      if (inMessage.startsWith("protCast", j) ){
          strcpy(sendBox.to, ":gant"); strcpy(sendBox.param, "protCast"); sendBox.value= 1; 

          radio.openWritingPipe(pipes[5]);  //0xF0F0F0F042
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
          ////inMessage = "" ; 
      break;
      }

      if (inMessage.startsWith("fireball", j) ){
          strcpy(sendBox.to, ":gant"); strcpy(sendBox.param, "fireball"); sendBox.value= 1; 

          radio.openWritingPipe(pipes[5]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
          ////inMessage = "" ; 
      break;
      }

      if (inMessage.startsWith("fireCast", j) ){
          strcpy(sendBox.to, ":gant"); strcpy(sendBox.param, "fireCast"); sendBox.value= 1; 

          radio.openWritingPipe(pipes[5]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
          ////inMessage = "" ; 
      break;
      }

      if (inMessage.startsWith("vampire", j) ){
          strcpy(sendBox.to, ":gant"); strcpy(sendBox.param, "vampire"); sendBox.value= 1; 

          radio.openWritingPipe(pipes[5]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
          ////inMessage = "" ; 
      break;
      }
  
      if (inMessage.startsWith(":target", j) ){
          strcpy(sendBox.to, ":gant"); strcpy(sendBox.param, "sightFB"); sendBox.value= 1; 

          radio.openWritingPipe(pipes[4]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
          //inMessage = "" ; 
      break;
      }
  
      if (inMessage.startsWith(":!target", j) ){
          strcpy(sendBox.to, ":gant"); strcpy(sendBox.param, "sightFB"); sendBox.value= 0; 

          radio.openWritingPipe(pipes[4]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
          //inMessage = "" ; 
      break;
      }


       }//for actions :gant
       inMessage = "" ;
      }//for :gant
    }//fin inMessage
    //}//Serial.available

}






