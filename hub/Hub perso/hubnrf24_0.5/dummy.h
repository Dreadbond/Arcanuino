
typedef struct{
  String Name ;
  int life = 100 ;
  int armor = 0 ;
  String tag ;
  bool hit ;
  bool dead ;
  } dummy ;
dummy Dessloch ;

void dummyInit() {
Dessloch.tag = "!184675";
Dessloch.Name = "Dessloch";
Dessloch.life = 100 ;
}


void dummyLoop() {
  if (!Dessloch.dead){
    if (Dessloch.hit) {
      Dessloch.life -= 20 ;
      Serial.print("Dessloch hit : "); 
      Serial.print(Dessloch.life); 
      Serial.print(" HP left."); 
      Dessloch.hit = 0 ;
      }
  
    if (Dessloch.life<=0) {
      Serial.println("Dessloch died.");
      Dessloch.dead = 1;
    }
  }
}
