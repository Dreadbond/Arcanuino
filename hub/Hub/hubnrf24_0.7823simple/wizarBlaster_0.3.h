
typedef struct{
  int ammoMax = 200 ;
  int ammo = 200 ;

  bool updateAmmo ;

  bool tokenReload = 0 ;
  bool tokenShoot = 0 ;

  String target = "!vide" ;

} infosWizBlaStruct ;
infosWizBlaStruct wizbla ;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void wizblaReceive(String from, String param, float value=1){

if (from == ":wizbla" && justReceive) {
  
  StaticJsonBuffer<100> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["to"]    = IDObject;
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

void wizblaSend() {

  for (int i=0 ; i< inMessage.length() ; i++) {

  if (inMessage.startsWith(":wizbla", i) ) {

    for (int j=0 ; j < inMessage.length() ; j++) {
      if (inMessage.startsWith("plasmFb", j) ){
           strcpy(sendBox.param, "plasmFb"); sendBox.value= 1; 

          radio.openWritingPipe(addresses[wizblaAddress]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
      break;
      }

      if (inMessage.startsWith("fireFb", j) ){
           strcpy(sendBox.param, "fireFb"); sendBox.value= 1; 

          radio.openWritingPipe(addresses[wizblaAddress]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
      break;
      }
  
      if (inMessage.startsWith("reloadFb", j) ){
           strcpy(sendBox.param, "rldFb"); sendBox.value= 1; 

          radio.openWritingPipe(addresses[wizblaAddress]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
      break;
      }
  
      if (inMessage.startsWith("target", j) ){
           strcpy(sendBox.param, "sightFB"); sendBox.value= 1; 

          radio.openWritingPipe(addresses[wizblaAddress]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
          //inMessage = "" ; 
      break;
      }
  
      if (inMessage.startsWith("!target", j) ){
           strcpy(sendBox.param, "sightFB"); sendBox.value= 0; 

          radio.openWritingPipe(addresses[wizblaAddress]);
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
  /*
  if (wizbla.tokenShoot) {//wizbla.shootFb();
           strcpy(sendBox.param, "shootFB"); sendBox.value= 1; 

          radio.openWritingPipe(addresses[wizblaAddress]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();

        wizbla.tokenShoot=0;
    }*/

  if (wizbla.updateAmmo) {   
    
  }

}
