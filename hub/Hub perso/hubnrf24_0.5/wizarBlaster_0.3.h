
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
  bool reloadToken = 0 ;
  int reloadTime = 3000 ;
  unsigned long reloadTimeTag ;
  unsigned long nextShot ;

  String target = "!vide" ;
  
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
  if (param == "trigger" && value == 1 && wizbla.canShoot && wizbla.nextShot< millis() && wizbla.ammo > 0) {
    Serial.print("Trigger "); Serial.println(value); 
    wizbla.shot = 1;
    wizbla.ammo = wizbla.ammo - wizbla.ammoCost ;
    //wizbla.canShoot=0;
    wizbla.nextShot = millis() + wizbla.shootRate ;
    }

  /*if (param == "trigger" && value == 0 && !wizbla.canShoot && wizbla.ammo >0) {
    wizbla.canShoot=1;
    Serial.print("Trigger "); Serial.println(value); 
    }*/

  if (param == "reload" && value == 1 && wizbla.ammo< wizbla.ammoMax) {
    tokenReload=1;
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

  if (wizbla.oldAmmo != wizbla.ammo && justReceive) {
    Serial.print("Ammo : "); Serial.println(wizbla.ammo); 
    if (wizbla.ammo>75 && wizbla.ammo <= wizbla.ammoMax) {
     radio.stopListening();
      for (int i=0; i<4; i++){
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPRedA0"); sendBox.param[6]= i+48 ; sendBox.value= 150; 
        radio.write( &sendBox, sizeof(sendBox) );
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPGreA0"); sendBox.param[6]= i+48 ; sendBox.value= 150; 
        radio.write( &sendBox, sizeof(sendBox) );
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPBluA0"); sendBox.param[6]= i+48 ; sendBox.value= 0; 
        radio.write( &sendBox, sizeof(sendBox) );
        delay(100);
      }
     radio.startListening();
    }
    if (wizbla.ammo>50 && wizbla.ammo <= 75) {
      for (int i=0; i<3; i++){
       radio.stopListening();
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPRedA0"); sendBox.param[6]= i+48 ; sendBox.value= 150; 
        radio.write( &sendBox, sizeof(sendBox) );
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPGreA0"); sendBox.param[6]= i+48 ; sendBox.value= 150; 
        radio.write( &sendBox, sizeof(sendBox) );
        strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPBluA0"); sendBox.param[6]= i+48 ; sendBox.value= 0; 
        radio.write( &sendBox, sizeof(sendBox) );
        radio.startListening();
      }
    }
    if (wizbla.ammo>25 && wizbla.ammo <= 50) {
      for (int i=0; i<2; i++){
      radio.stopListening();
      strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPRedA0"); sendBox.param[6]= i+48 ; sendBox.value= 150; 
      radio.write( &sendBox, sizeof(sendBox) );
      strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPGreA0"); sendBox.param[6]= i+48 ; sendBox.value= 150; 
      radio.write( &sendBox, sizeof(sendBox) );
      strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPBluA0"); sendBox.param[6]= i+48 ; sendBox.value= 0; 
      radio.write( &sendBox, sizeof(sendBox) );
      radio.startListening();
      }
    }
    if (wizbla.ammo>0 && wizbla.ammo <= 25) {
      for (int i=0; i<1; i++){
      radio.stopListening();
      strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPRedA0"); sendBox.param[6]= i+48 ; sendBox.value= 150; 
      radio.write( &sendBox, sizeof(sendBox) );
      strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPGreA0"); sendBox.param[6]= i+48 ; sendBox.value= 150; 
      radio.write( &sendBox, sizeof(sendBox) );
      strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "NPBluA0"); sendBox.param[6]= i+48 ; sendBox.value= 0; 
      radio.write( &sendBox, sizeof(sendBox) );
      radio.startListening();
      //wizbla.canShoot=0;
      }
    }
  }


  if (wizbla.reloading) {wizbla.canShoot=0;}

  if (tokenShoot) {shootFb();}

  if (tokenReload) {reloadFb();}






}
