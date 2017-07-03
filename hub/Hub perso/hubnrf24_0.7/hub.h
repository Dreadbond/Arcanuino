
typedef struct{
  String Name ;
  String tag = IDObject ;
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
  if (!thisHub.dead){
    if (thisHub.damage != 0) {
      thisHub.life -= thisHub.damage ;
      Serial.print("You have been hit : "); 
      Serial.print(thisHub.life); 
      Serial.print(" HP left."); 
      thisHub.damage=0;
      }
  
    if (thisHub.life<=0) {
      thisHub.life=0;
      Serial.println("You died.");
      thisHub.dead = 1;
    }
  }
}
