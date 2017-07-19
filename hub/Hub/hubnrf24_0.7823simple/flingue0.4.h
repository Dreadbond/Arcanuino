typedef struct{
  int ammo = 20 ;
  int ammoMax = 20 ;

  bool updateAmmo = 0 ;
  String target = "!vide" ;
  ////String inMessage ;

} infosFlingueStruct ;
infosFlingueStruct pistol ;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pistolReceive(String from, String param, float value=1){

if (from == ":pistol" && justReceive) {
  
  StaticJsonBuffer<100> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["to"]    = IDObject ;   //"!111111"
  root["from"]  = ":pistol" ;

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


void pistolSend() {

  for (int i=0 ; i< inMessage.length() ; i++) {
     if (inMessage.startsWith(":pistol", i) ) {

    for (int j=0 ; j < inMessage.length() ; j++) {
      //{"to":":pistol","from":"!11","param" :"shootFb","value":15}
      if (inMessage.startsWith("shootFb", j) ){
        
           strcpy(sendBox.param, "shootFB"); sendBox.value= 1; 

          radio.openWritingPipe(addresses[flingue]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
          
          ////inMessage = "" ; 
      break;
      }
  
      if (inMessage.startsWith("reloadFb", j) ){
      //inMessage = "" ; 
      break;
      }
  
      if (inMessage.startsWith(":target", j) ){
           strcpy(sendBox.param, "sightFB"); sendBox.value= 1; 

          radio.openWritingPipe(addresses[flingue]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
          //inMessage = "" ; 
      break;
      }
  
      if (inMessage.startsWith(":!target", j) ){
           strcpy(sendBox.param, "sightFB"); sendBox.value= 0; 

          radio.openWritingPipe(addresses[flingue]);
          radio.stopListening();
          radio.write(&sendBox, sizeof(sendBox));
          radio.startListening();
          //inMessage = "" ; 
      break;
      }

//{"to":":pistol","from":"!11","param" :"ammo","value":15}
      if (inMessage.startsWith("ammo", j) ){
        String arf = "" ;
          for ( j + 10 ; j < inMessage.length() ; j++){
            arf += inMessage.charAt(j+14);
            }
        pistol.ammo = arf.toInt() ; //
        pistol.updateAmmo = 1 ;
      break;
      }
       }//for actions :pistol
       inMessage = "" ;
      }//for :pistol
    }//fin inMessage
    //}//Serial.available
}


void pistolCode(){

  if (pistol.updateAmmo) {
    //Serial.print("Ammo : "); Serial.println(pistol.ammo); 
    if (pistol.ammo==pistol.ammoMax) {
      radio.stopListening();
      radio.openWritingPipe(addresses[flingue]);
     strcpy(sendBox.param, "NPRed_0"); sendBox.value= 0; 
    radio.write( &sendBox, sizeof(sendBox) );
     strcpy(sendBox.param, "NPGre_0"); sendBox.value= 200; 
    radio.write( &sendBox, sizeof(sendBox) );
     strcpy(sendBox.param, "NPBlu_0"); sendBox.value= 0; 
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
    }

    else if (pistol.ammo<pistol.ammoMax && pistol.ammo>1) {
      radio.stopListening();
      radio.openWritingPipe(addresses[flingue]);
    strcpy(sendBox.param, "NPRed_0"); sendBox.value= 50*pistol.ammo/pistol.ammoMax + 150; 
    radio.write( &sendBox, sizeof(sendBox) );
    strcpy(sendBox.param, "NPGre_0"); sendBox.value= 200*pistol.ammo/pistol.ammoMax ; 
    radio.write( &sendBox, sizeof(sendBox) );
    strcpy(sendBox.param, "NPBlu_0"); sendBox.value= 0; 
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
    }
    
    else if (pistol.ammo==1) {
      radio.stopListening();
      radio.openWritingPipe(addresses[flingue]);
    strcpy(sendBox.param, "NPRed_0"); sendBox.value= 200; 
    radio.write( &sendBox, sizeof(sendBox) );
    strcpy(sendBox.param, "NPGre_0"); sendBox.value= 0; 
    radio.write( &sendBox, sizeof(sendBox) );
    strcpy(sendBox.param, "NPBlu_0"); sendBox.value= 0; 
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
    }
    else if (pistol.ammo<1) {
      radio.stopListening();
      radio.openWritingPipe(addresses[flingue]);
    strcpy(sendBox.param, "NPRed_0"); sendBox.value= 0; 
    radio.write( &sendBox, sizeof(sendBox) );
    strcpy(sendBox.param, "NPGre_0"); sendBox.value= 0; 
    radio.write( &sendBox, sizeof(sendBox) );
    strcpy(sendBox.param, "NPBlu_0"); sendBox.value= 0; 
    radio.write( &sendBox, sizeof(sendBox) );
    radio.startListening();
    }
  pistol.updateAmmo = 0 ;
  }

}
