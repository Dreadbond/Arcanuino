
typedef struct{
  String Name ;
  String tag = IDObject ;
  int oldLife = 50;
  int life = 100 ;
  int armor = 0 ;
  bool hit ;
  bool dead ;
  int damage ;
}
selfHub;

selfHub thisHub;

void hubReceive(String to, String param, float value){
  if (to == thisHub.tag && justReceive) {
    if (param=="hit") {
      thisHub.damage=value;
      thisHub.hit=1;
    }
  }
}




void hubLoop() {
  thisHub.oldLife=thisHub.life;
  if (!thisHub.dead){
    if (thisHub.damage != 0) {
      thisHub.life -= thisHub.damage ;
      Serial.print("You have been hit : "); 
      Serial.print(thisHub.life); 
      Serial.println(" HP left."); 
      thisHub.damage=0;
    }

    if (thisHub.life<=0) {
      thisHub.life=0;
      Serial.println("You died.");
      thisHub.dead = 1;
    }
  }




  if (thisHub.oldLife != thisHub.life) {
    float qsd = thisHub.life/10 ;
    for(int i = 0; i<Pix; i++) {strip.setPixelColor(i, 0, 0, 0);}
    for(int i=0; i<qsd; i++) {

      refreshLifeNP=1;
      NPled=i;
      redNP=100*bright;
      greNP=100*bright;
      bluNP=100*bright;
    }
  }
}





