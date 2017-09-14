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

  bool tokenShoot = 0 ;
  bool tokenReload = 0 ;
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
  
  StaticJsonBuffer<100> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

root["to"] = sendBox.from      ;
root["from"] = to    ;
root["param"] = param  ;
root["value"] = value   ;
  
  //JsonArray& data = root.createNestedArray("to");
 
  root.printTo(Serial);
  Serial.println();

  
/*
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

root["to"] = "!111111"      ;
root["from"] = ":pistol"    ;
  root["param"] = "trigger"    ;
  root["value"] = 1   ;

  root.printTo(Serial);

  //root.prettyPrintTo(Serial);
  Serial.println();
      */
 }//fin boucle JustReceive

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

  if (pistol.tokenReload) {Serial.println("reload");}

}
