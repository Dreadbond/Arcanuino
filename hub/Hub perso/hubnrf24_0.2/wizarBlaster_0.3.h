/*
if (String(receiveBox.to).equals(IDObject) && process) {
  //contenuReceive();
    
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
