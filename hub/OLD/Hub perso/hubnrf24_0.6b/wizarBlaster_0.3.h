
typedef struct{
  int ammoMax = 100 ;
  int ammo = 100 ;
  int ammoCost = 5 ;
  int oldAmmo ;
  bool canShoot = 1 ;
  bool shot = 0 ;

  int shootRate = 100 ;
  int shootMode = 1 ;

  bool canReload = 1 ;
  bool reloading = 0 ;
  bool tokenReload = 0 ;
  int reloadTime = 3000 ;
  unsigned long reloadTimeTag ;
  unsigned long nextShot ;

  String target = "!vide" ;

  bool sendState =1;
  
  } infosWizBlaStruct ;
infosWizBlaStruct wizbla ;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, ""); process=1;

void wizblaCode(String to, String param, float value){
wizbla.oldAmmo = wizbla.ammo ;


  
if (to == ":wizbla" && justReceive) {
    if (param == "trigger" && value == 1 && wizbla.canShoot && wizbla.nextShot< millis() && wizbla.ammo >= wizbla.ammoCost ) {
    Serial.print("Trigger "); Serial.println(value); 
    wizbla.shot = 1;
    wizbla.ammo = wizbla.ammo - wizbla.ammoCost ;
    wizbla.nextShot = millis() + wizbla.shootRate ;
    wizbla.sendState=1;
    
    if (wizbla.shootMode==1) {strcpy(sendBox.param, "plasmFB");}
    else if (wizbla.shootMode==2) {strcpy(sendBox.param, "fireFB");}
    strcpy(sendBox.to, ":wizbla"); sendBox.value= 0; 
    
    radio.stopListening();
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
    }

  if (param == "trigger" && value && wizbla.ammo < wizbla.ammoCost) {
    //sound : click;
    wizbla.sendState=1;
  }

  /*if (param == "trigger" && value == 0 && !wizbla.canShoot && wizbla.ammo >0) {
    wizbla.canShoot=1;
    Serial.print("Trigger "); Serial.println(value); 
    }*/
  if (param == "nxtMode") {
    wizbla.shootMode++;
    wizbla.sendState=1;
    
    if (wizbla.shootMode>=3) {wizbla.shootMode=1;}
  }

  if (param == "reload" && wizbla.ammo< wizbla.ammoMax) {
    wizbla.tokenReload=1;
    }

  if (param.startsWith("!")) {
      wizbla.target = param ;
      if (param.startsWith("!vide")) {
          radio.stopListening();
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPRedS1"); sendBox.value= 0; 
        radio.write( &sendBox, sizeof(sendBox) );
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPGreS1"); sendBox.value= 0; 
        radio.write( &sendBox, sizeof(sendBox) );
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPBluS1"); sendBox.value= 0; 
        radio.write( &sendBox, sizeof(sendBox) );
        radio.startListening();
      }
      else 
      {
          radio.stopListening();
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPRedS1"); sendBox.value= 70; 
        radio.write( &sendBox, sizeof(sendBox) );
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPGreS1"); sendBox.value= 0; 
        radio.write( &sendBox, sizeof(sendBox) );
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPBluS1"); sendBox.value= 0; 
        radio.write( &sendBox, sizeof(sendBox) );
        radio.startListening();
      }
    }
}

  //if (wizbla.oldAmmo != wizbla.ammo) {wizbla.sendState=1;}

  if (wizbla.sendState) {
    wizbla.sendState=0;
    Serial.print("Ammo : "); Serial.println(wizbla.ammo); 
    
    //Ammo
    int NPRed, NPGreen, NPBlue ; 
    switch(wizbla.shootMode) {
      case 1 :
      NPRed   = 100 ;
      NPGreen = 230 ;
      NPBlue  = 100 ;
      break;

      case 2 :
      NPRed   = 210 ;
      NPGreen = NPRed - 160 ;
      NPBlue  = 0 ;
      break;
    }
    if (wizbla.ammo>75 && wizbla.ammo <= wizbla.ammoMax) {
     radio.stopListening();
      for (int i=0; i<5; i++){
        //delay(100);
      radio.stopListening();
      radio.openWritingPipe(pipes[3]);
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPRedA0"); sendBox.param[6]= i+49 ; sendBox.value= NPRed; 
        radio.write( &sendBox, sizeof(sendBox) );
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPGreA0"); sendBox.param[6]= i+49 ; sendBox.value= NPGreen; 
        radio.write( &sendBox, sizeof(sendBox) );
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPBluA0"); sendBox.param[6]= i+49 ; sendBox.value= NPBlue; 
        radio.write( &sendBox, sizeof(sendBox) );
      radio.startListening();
      }
    }
    if (wizbla.ammo>50 && wizbla.ammo <= 75) {
      for (int i=0; i<4; i++){
        //delay(100);
      radio.stopListening();
      radio.openWritingPipe(pipes[3]);
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPRedA0"); sendBox.param[6]= i+49 ; sendBox.value= NPRed; 
        radio.write( &sendBox, sizeof(sendBox) );
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPGreA0"); sendBox.param[6]= i+49 ; sendBox.value= NPGreen; 
        radio.write( &sendBox, sizeof(sendBox) );
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPBluA0"); sendBox.param[6]= i+49 ; sendBox.value= NPBlue; 
        radio.write( &sendBox, sizeof(sendBox) );
      radio.startListening();
      }
    }
    if (wizbla.ammo>25 && wizbla.ammo <= 50) {
      for (int i=0; i<3; i++){
        //delay(100);
      radio.stopListening();
      radio.openWritingPipe(pipes[3]);
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPRedA0"); sendBox.param[6]= i+49 ; sendBox.value= NPRed; 
        radio.write( &sendBox, sizeof(sendBox) );
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPGreA0"); sendBox.param[6]= i+49 ; sendBox.value= NPGreen; 
        radio.write( &sendBox, sizeof(sendBox) );
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPBluA0"); sendBox.param[6]= i+49 ; sendBox.value= NPBlue; 
        radio.write( &sendBox, sizeof(sendBox) );
      radio.startListening();
      }
    }
    if (wizbla.ammo>=wizbla.ammoCost && wizbla.ammo <= 25) {
      int i=0;
      radio.stopListening();
      radio.openWritingPipe(pipes[3]);
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPRedA0"); sendBox.param[6]= i+49 ; sendBox.value= NPRed; 
        radio.write( &sendBox, sizeof(sendBox) );
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPGreA0"); sendBox.param[6]= i+49 ; sendBox.value= NPGreen; 
        radio.write( &sendBox, sizeof(sendBox) );
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPBluA0"); sendBox.param[6]= i+49 ; sendBox.value= NPBlue; 
        radio.write( &sendBox, sizeof(sendBox) );
      radio.startListening();
      //wizbla.canShoot=0;
    }
    if (wizbla.ammo<wizbla.ammoCost) {
      int i=0;
        //delay(100);
      radio.stopListening();
      radio.openWritingPipe(pipes[3]);
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPRedA0"); sendBox.param[6]= i+49 ; sendBox.value= 0; 
        radio.write( &sendBox, sizeof(sendBox) );
        //strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPGreA0"); sendBox.param[6]= i+49 ; sendBox.value= 0; 
        //radio.write( &sendBox, sizeof(sendBox) );
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPBluA0"); sendBox.param[6]= i+49 ; sendBox.value= 0; 
        radio.write( &sendBox, sizeof(sendBox) );
      radio.startListening();
      //wizbla.canShoot=0;
  }
}


  

 // if (tokenShoot) {shootFb();}

  if (wizbla.tokenReload) {//reloadFb();
    static unsigned long nextReload ;
    wizbla.reloading=1;
    if (wizbla.ammo < wizbla.ammoMax )//&& nextReload < millis() ) 
      {
        wizbla.ammo += 5 ;
        wizbla.sendState=1;
        Serial.print("Reloading ... ");
        Serial.println(nextReload);
        delay(100);
        nextReload = millis() + 100 ;
       }
      if (wizbla.ammo >= wizbla.ammoMax) {
        Serial.print("Reloading Done.");
        wizbla.ammo = wizbla.ammoMax;
        wizbla.sendState=1;
        wizbla.tokenReload=0;
        wizbla.canShoot=1;
        wizbla.reloading=0;
        }
     
    }

  if (wizbla.reloading) {wizbla.canShoot=0;}

    if (wizbla.shootMode==1) 
      {
      wizbla.ammoCost = 5;
      wizbla.shootRate = 100;
      }
    else if (wizbla.shootMode==2) 
      {
      wizbla.ammoCost = 20;
      wizbla.shootRate = 2570;
      }




}
