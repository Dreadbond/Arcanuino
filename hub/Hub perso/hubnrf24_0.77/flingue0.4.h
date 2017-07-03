
typedef struct{
  int ammo = 13 ;
  int ammoMax=12;
  int oldAmmo ;
  bool canFire = 1 ;
  bool shot = 0 ;
  int damage = 15 ;

  bool canReload = 1 ;
  bool reloading = 0 ;
  bool reloadToken = 0 ;
  int reloadTime = 3000 ;
  unsigned long reloadTimeTag ;
  unsigned long nextFire;
  String target = "!vide" ;
  


bool tokenShoot ;
/*
void shootFb(){
  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static int red ;
  static int green ;
  static int blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 10 ;
  static int TC2 = 40 ;
  static int TC3 = 200 ;
  static int pixCanon = 3;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;

  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);
  
  if (chrono>TC0 && chrono<TC1) {
    red=0;
    green=0;
    blue=0;
    }

  if (chrono>TC1 && chrono<TC2){
    red=255;
    green=245;
    blue=0;
    }
  
  if (chrono>TC2 && chrono<TC3) {
  bright = (TC3-chrono)/5;

  red=190*bright/100;
  green=40*bright/100;
  blue=5*bright/100;
  
  red=constrain(red, 0, 255);
  green=constrain(green, 0, 255);
  blue=constrain(blue, 0, 255);
  
  }
  if (chrono>TC3) {
    red=0;
    green=0;
    blue=0;
    tokenShoot=LOW;
    }

    radio.stopListening();
      radio.openWritingPipe(pipes[2]);
      strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPRed_2"); sendBox.value= red; 
      radio.write( &sendBox, sizeof(sendBox) );
      strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPGre_2"); sendBox.value= green; 
      radio.write( &sendBox, sizeof(sendBox) );
      strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPBlu_2"); sendBox.value= blue; 
      radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
}*/

bool tokenReload ;
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

void flingueCode(String to, String param, float value){
pistol.oldAmmo = pistol.ammo ;
  
if (to == ":pistol" && justReceive) {

  
  if (param == "trigger" && value == 1 && pistol.canFire && pistol.nextFire < millis() ) {
    //Serial.print("Trigger "); Serial.println(value); 
    pistol.shot = 1;
    pistol.ammo--;
    pistol.canFire=0;
    pistol.nextFire = millis()+50;
    pistol.tokenShoot=1;
       if (pistol.target !="!vide" && pistol.target != IDObject) {
          String mess = "hit"; Serial.println( pistol.target);

          pistol.target.toCharArray(sendBox.to, 8); mess.toCharArray(sendBox.param, 8); sendBox.value= pistol.damage;     //Serial.println( pistol.target); 
            radio.setChannel(chan);  //a dégager : remplacer par serveur etc
          radio.openWritingPipe(pipes[1]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
            radio.setChannel(chan);
       }
       if (pistol.target==IDObject) {
          thisHub.hit = 1;
          thisHub.damage = pistol.damage;
       }
    }

  if (param == "trigger" && value == 0 && !pistol.canFire && pistol.ammo >0) { pistol.canFire=1; }

  if (param == "reload" && value == 1 && pistol.ammo < pistol.ammoMax) {pistol.tokenReload=1;}

  if (param.startsWith("!")) {
      pistol.target = param ;
      if (param.startsWith("!vide")) {
          radio.stopListening();
          radio.openWritingPipe(pipes[2]);
        strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPRed_1"); sendBox.value= 0; 
        radio.write( &sendBox, sizeof(sendBox) );
        strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPGre_1"); sendBox.value= 0; 
        radio.write( &sendBox, sizeof(sendBox) );
        strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPBlu_1"); sendBox.value= 0; 
        radio.write( &sendBox, sizeof(sendBox) );
        radio.startListening();
      }
      else 
      {
          radio.stopListening();
          radio.openWritingPipe(pipes[2]);
        strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPRed_1"); sendBox.value= 70; 
        radio.write( &sendBox, sizeof(sendBox) );
        strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPGre_1"); sendBox.value= 0; 
        radio.write( &sendBox, sizeof(sendBox) );
        strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPBlu_1"); sendBox.value= 0; 
        radio.write( &sendBox, sizeof(sendBox) );
        radio.startListening();
      }
    }

Serial.println("prout");

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["object"] = to ;
  root["param"] = param ;
  root["value"]= value ;

  root.printTo(Serial);

  //root.prettyPrintTo(Serial);
  Serial.println();
    
  }

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

  if (pistol.tokenReload) {pistol.reloadFb();}

}
