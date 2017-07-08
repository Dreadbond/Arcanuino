/*
void triFlingue() {
if (String(receiveBox.to).equals(IDObject) && process) {
    
    String RecToString = String(receiveBox.from) ;
    String RecParamString=String(receiveBox.param);

    if (RecToString == ":wizbla"){
        if (RecParamString == "trigger"){Serial.println("Trigger demande");     strcpy( sendBox.to, ":wizbla" ); strcpy( sendBox.param, "fireFB" ); sendBox.value=1; Send();}
        if (RecParamString == "reload") {Serial.println("Rechargement demande");strcpy( sendBox.to, ":wizbla" ); strcpy( sendBox.param, "rldFB" ); sendBox.value=1; Send();}
        if (RecParamString == "nxtMode"){Serial.println("Next mode demande");   strcpy( sendBox.to, ":wizbla" ); strcpy( sendBox.param, "modeFB" ); sendBox.value=1; Send();}
        if (RecParamString == "cible")  {Serial.println("Cible demandee");      strcpy( sendBox.to, ":wizbla" ); strcpy( sendBox.param, "targetFB" ); sendBox.value=1; Send();}
        }
  process=0;
  }
*/
typedef struct{
  int ammo = 6 ;
  bool canFire = 1 ;

  bool canReload = 1 ;
  bool reloading = 0 ;
  bool reloadToken = 0 ;
  int reloadTime = 3000 ;
  unsigned long reloadTimeTag ;
  } infosFlingueStruct ;
infosFlingueStruct statePistol ;

bool tokenShoot ;
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

  Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);
  
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
  if (chrono>TC3) {tokenShoot=LOW;}

  radio.stopListening();
    strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPRed_2"); sendBox.value= red; 
    radio.write( &sendBox, sizeof(sendBox) );
    strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPGreen_2"); sendBox.value= green; 
    radio.write( &sendBox, sizeof(sendBox) );
    strcpy(sendBox.to, ":pistol"); strcpy(sendBox.param, "NPBlue_2"); sendBox.value= blue; 
    radio.write( &sendBox, sizeof(sendBox) );
  radio.startListening();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void flingueCode(String param, float value){
      
  if (param == "trigger" && value == 1 && statePistol.canFire) {
    
    strcpy(sendBox.to, ":pistol"); 
    strcpy(sendBox.param, "shootFB"); 
    
    process=1; 
    Serial.print("Trigger demande "); Serial.println(value); 
    tokenShoot=1;
    //statePistol.canFire=0;
    }

  if (param == "trigger" && value == 0 && !statePistol.canFire) {
    statePistol.canFire=1;
    Serial.print("Trigger demande "); Serial.println(value); 
    }

  if (tokenShoot) {}//{shootFb();}

  //if (statePistol.reloading) {statePistol.canFire=0;}

  
  /*
  if (param == "reload" && statePistol.ammo < 6) {Serial.print("Reloading ..."); reloadToken=1;}

  if (reloadToken && canReload) {reloadTime = millis(); }
    if(reloadTime>*/

   
}
