/*
void loop() {
if (String(receiveBox.to).equals(IDObject) && process) {
  //contenuReceive();
    
    String RecToString = String(receiveBox.from) ;
    String RecParamString=String(receiveBox.param);

    if (RecToString == ":gant"){
        if (RecParamString == "x") {donneesGant.x = receiveBox.value;}
        if (RecParamString == "y") {donneesGant.y = receiveBox.value;}
        if (RecParamString == "z") {donneesGant.z = receiveBox.value;}

        if (RecParamString == "p") {donneesGant.p = receiveBox.value;}
        if (RecParamString == "i") {donneesGant.i = receiveBox.value;}
        if (RecParamString == "m") {donneesGant.m = receiveBox.value;}
        if (RecParamString == "an") {donneesGant.an= receiveBox.value;}
        if (RecParamString == "au") {donneesGant.au= receiveBox.value; printGloveData();}
        if (RecParamString == "cible")  {Serial.println("Cible demandee");      strcpy( sendBox.to, ":gant" ); strcpy( sendBox.param, "targetFB" ); sendBox.value=1; Send();}
        }

  process=0;
  }
}*/

typedef struct{
  char from[8];
  char to[8];
  int x, y, z, p, i, m, an, au;
} infosGantStruct ;

infosGantStruct donneesGant;

void printGloveData(){
     Serial.print(donneesGant.x);   Serial.print(" ");
     Serial.print(donneesGant.y);   Serial.print(" ");
     Serial.print(donneesGant.z);   Serial.print(" ");
     
     Serial.print(donneesGant.p);   
     Serial.print(" ");
     Serial.print(donneesGant.i);   
     Serial.print(" ");
     Serial.print(donneesGant.m);   
     Serial.print(" ");
     Serial.print(donneesGant.an);   
     Serial.print(" ");
     Serial.println(donneesGant.au);  
}

