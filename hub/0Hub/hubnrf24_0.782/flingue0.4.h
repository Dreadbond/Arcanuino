typedef struct{
  int ammo = 20 ;
  int ammoMax = 20 ;
  int oldAmmo ;
  bool canFire = 1 ;
  bool shot = 0 ;
  int damage = 20 ;

  bool canReload = 1 ;
  bool reloading = 0 ;
  bool reloadToken = 0 ;
  int reloadTime = 3000 ;
  unsigned long reloadTimeTag ;
  unsigned long nextFire;
  String target = "!vide" ;
  String inMessage ;

  bool tokenShoot = 0 ;
  bool tokenReload = 0 ;
void reloadFb(){
  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  bool process;

  static float red ;
  static float green ;
  static float blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 2000 ;
  static int pixAmmo = 0;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;

  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);  

  if (chrono>=TC0 && chrono<TC1) {
    red   = 150*chrono/TC1 ;
    green = 150*chrono/TC1 ;
    blue  = 0 ;
    }

  if (chrono>=TC1) {

  red=0;
  green=200;
  blue=0;

    tokenReload=LOW;
    //pistol.canFire = 1;
    canFire = 1;
    //pistol.
    ammo=ammoMax;
    }

//if (canSend){
    radio.stopListening();
    radio.openWritingPipe(pipes[2]);
      strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPRed_0"); sendBox.value= red; 
      radio.write( &sendBox, sizeof(sendBox) );
      strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPGre_0"); sendBox.value= green; 
      radio.write( &sendBox, sizeof(sendBox) );
      strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPBlu_0"); sendBox.value= blue; 
      radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
    canSend=0;
  //}
  }
} infosFlingueStruct ;
infosFlingueStruct pistol ;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, ""); process=1;

void flingueCode(String from, String param, float value=1){

pistol.oldAmmo = pistol.ammo ;

if (from == ":pistol" && justReceive) {
  /*
  if (param.startsWith("!")) {
    param = "target";
    valueStr = param;
  }*/
  
  StaticJsonBuffer<100> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["to"]    = "!111111";
  root["from"]  = ":pistol";

  if (param.startsWith("!")) {
  root["param"] =  "target";
  root["value"] =  param;
  }
  else
  {
  root["param"] = param    ;
  root["value"] = value    ;
  }

  //JsonArray& data = root.createNestedArray("to");

  root.printTo(Serial);
Serial.println();


  if (pistol.oldAmmo != pistol.ammo) {
    Serial.print("Ammo : "); Serial.println(pistol.ammo); 
    if (pistol.ammo==pistol.ammoMax) {
      radio.stopListening();
      radio.openWritingPipe(pipes[2]);
    strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPRed_0"); sendBox.value= 0; 
    radio.write( &sendBox, sizeof(sendBox) );
    strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPGre_0"); sendBox.value= 200; 
    radio.write( &sendBox, sizeof(sendBox) );
    strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPBlu_0"); sendBox.value= 0; 
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
    }

    else if (pistol.ammo<pistol.ammoMax && pistol.ammo>1) {
      radio.stopListening();
      radio.openWritingPipe(pipes[2]);
    strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPRed_0"); sendBox.value= 50*pistol.ammo/pistol.ammoMax + 150; 
    radio.write( &sendBox, sizeof(sendBox) );
    strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPGre_0"); sendBox.value= 200*pistol.ammo/pistol.ammoMax ; 
    radio.write( &sendBox, sizeof(sendBox) );
    strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPBlu_0"); sendBox.value= 0; 
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
    }
    
    else if (pistol.ammo==1) {
      radio.stopListening();
      radio.openWritingPipe(pipes[2]);
    strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPRed_0"); sendBox.value= 200; 
    radio.write( &sendBox, sizeof(sendBox) );
    strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPGre_0"); sendBox.value= 0; 
    radio.write( &sendBox, sizeof(sendBox) );
    strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPBlu_0"); sendBox.value= 0; 
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
    }
    else if (pistol.ammo<1) {
      radio.stopListening();
      radio.openWritingPipe(pipes[2]);
    strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPRed_0"); sendBox.value= 0; 
    radio.write( &sendBox, sizeof(sendBox) );
    strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPGre_0"); sendBox.value= 0; 
    radio.write( &sendBox, sizeof(sendBox) );
    strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPBlu_0"); sendBox.value= 0; 
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
    pistol.canFire=0;
    }
  }
}
} //fin boucle JustReceive

void pistolReceive() {
  
  
  if (Serial.available()) {
  pistol.inMessage = Serial.readStringUntil('}');   //voir ptetre à remettre le }
  //{"to":":pistol","from":"!111111","param":":shootFb","value":1}
  //Serial.println(pistol.inMessage);
  }

  
  for (int i=0 ; i< pistol.inMessage.length() ; i++) {
    
  if (pistol.inMessage.startsWith(":pistol", i) ) {
      strip.setPixelColor(3, random(0, 255), random(0, 255), random(0, 255)); 
      strip.show();


    for (int j=0 ; j < pistol.inMessage.length() ; j++) {
      if (pistol.inMessage.startsWith("shootFb", j) ){
          strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "shootFB"); sendBox.value= 1; 

          radio.openWritingPipe(pipes[2]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
          ////pistol.inMessage = "" ; 
      break;
      }
  
      if (pistol.inMessage.startsWith("reloadFb", j) ){
      //pistol.inMessage = "" ; 
      break;
      }
  
      if (pistol.inMessage.startsWith(":target", j) ){
          strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "sightFB"); sendBox.value= 1; 

          radio.openWritingPipe(pipes[2]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
          //pistol.inMessage = "" ; 
      break;
      }
  
      if (pistol.inMessage.startsWith(":!target", j) ){
          strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "sightFB"); sendBox.value= 0; 

          radio.openWritingPipe(pipes[2]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
          //pistol.inMessage = "" ; 
      break;
      }
       }//for actions :pistol
      }//for :pistol

    }//fin inMessage
    pistol.inMessage = "" ;
  //}//Serial.available

}


void pistolCode(){
  if (pistol.reloading) {pistol.canFire=0;}

  if (pistol.tokenShoot) {//pistol.shootFb();
          strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "shootFB"); sendBox.value= 1; 

          radio.openWritingPipe(pipes[2]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();



        pistol.tokenShoot=0;
    }

  if (pistol.tokenReload) {Serial.println("reload");}

}