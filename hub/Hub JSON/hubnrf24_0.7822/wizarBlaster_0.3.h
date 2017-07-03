
typedef struct{
  int ammoMax = 200 ;
  int ammo = 200 ;
  int ammoCost = 5 ;
  int oldAmmo ;
  bool canShoot = 1 ;
  bool shot = 0 ;
  int damage = 5 ;

  int shootRate = 100 ;
  int shootMode = 1 ;
  bool updateAmmo ;

  bool canReload = 1 ;
  bool reloading = 0 ;
  bool tokenReload = 0 ;
  bool tokenShoot = 0 ;
  int reloadTime = 3000 ;
  unsigned long reloadTimeTag ;
  unsigned long nextShot ;
  unsigned long delayedFire ;

  String target = "!vide" ;

  bool sendState =1;
  
  } infosWizBlaStruct ;
infosWizBlaStruct wizbla ;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void wizblaCode(String from, String param, float value=1){

//wizbla.oldAmmo = wizbla.ammo ;

if (from == ":wizbla" && justReceive) {
  /*
  if (param.startsWith("!")) {
    param = "target";
    valueStr = param;
  }*/
  
  StaticJsonBuffer<100> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["to"]    = "!111111";
  root["from"]  = ":wizbla";

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



}
} //fin flingueCode

void wizblaReceive() {
  
  /*
  if (Serial.available()) {
  inMessage = Serial.readStringUntil('}');   //voir ptetre à remettre le }
  //{"to":":wizbla","from":"!111111","param":":shootFb","value":1}
  //Serial.println(inMessage);
  } à été déplacé
*/
  
  for (int i=0 ; i< inMessage.length() ; i++) {
    
  if (inMessage.startsWith(":wizbla", i) ) {
//      strip.setPixelColor(3, random(0, 255), random(0, 255), random(0, 255)); 
//      strip.show();


    for (int j=0 ; j < inMessage.length() ; j++) {
      if (inMessage.startsWith("plasmFb", j) ){
          strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "plasmFb"); sendBox.value= 1; 

          radio.openWritingPipe(pipes[3]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
      break;
      }

      if (inMessage.startsWith("fireFb", j) ){
          strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "fireFb"); sendBox.value= 1; 

          radio.openWritingPipe(pipes[3]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
      break;
      }
  
      if (inMessage.startsWith("reloadFb", j) ){
          strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "rldFb"); sendBox.value= 1; 

          radio.openWritingPipe(pipes[3]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
      break;
      }
  
      if (inMessage.startsWith("target", j) ){
          strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "sightFB"); sendBox.value= 1; 

          radio.openWritingPipe(pipes[3]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
          //inMessage = "" ; 
      break;
      }
  
      if (inMessage.startsWith("!target", j) ){
          strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "sightFB"); sendBox.value= 0; 

          radio.openWritingPipe(pipes[3]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
          //inMessage = "" ; 
      break;
      }

//{"to":":wizbla","from":"!111111","param" :"ammo","value":15}
      if (inMessage.startsWith("ammo", j) ){
        String arf = "" ;
          for ( j + 10 ; j < inMessage.length() ; j++){
            arf += inMessage.charAt(j+14);
            }
        wizbla.ammo = arf.toInt() ; //
        wizbla.updateAmmo = 1 ;
      break;
      }
       }//for actions :wizbla
       inMessage = "" ;
      }//for :wizbla
    }//fin inMessage
    //}//Serial.available

}


void wizblaCode(){
  if (wizbla.reloading) {wizbla.canShoot=0;}

  if (wizbla.tokenShoot) {//wizbla.shootFb();
          strcpy(sendBox.to, ":wizbla"); strcpy(sendBox.param, "shootFB"); sendBox.value= 1; 

          radio.openWritingPipe(pipes[3]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();

        wizbla.tokenShoot=0;
    }

  if (wizbla.tokenReload) {Serial.println("reload");}

  if (wizbla.updateAmmo) {   
    
  }

}
