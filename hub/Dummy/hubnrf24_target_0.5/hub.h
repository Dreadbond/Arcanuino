
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

///////////////////////////////////////////////////////////////////Impact
bool tokenImpact ;
void impactFB(){
  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static int red ;
  static int green ;
  static int blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 2500 ;
  static int TC2 = 2550 ;
  static int TC3 = 2570 ;
  static int TC4 ;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;
  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);
  
  if (chrono>TC0 && chrono<TC1) {
    for(int i=0; i<3 ; i++) {
      red  = random(210, 255);
      green= red - 160 ;
      green= green + random(0,100);

      bright = float(chrono)/TC1;
      strip.setPixelColor(i, red*bright, green*bright, 0); 
      strip.show();
    }
  }
  if (chrono>TC1 && chrono<TC2){
    for(int i=0 ; i<PixCanon ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
      for(int i=3; i<PixCanon ; i++) {
      red  = 70 + (i*9) ;
      green= i*3 ;
      blue = 0;
  
      red=constrain(red, 0, 255);
      strip.setPixelColor(i, red, green, blue); 
      strip.show();
      }
  }
  if (chrono>TC2 && chrono<TC3){
    strip.setPixelColor(9, 200, 200, 200); 
    strip.show();
  }
  if (chrono>TC3 ) {
    for(int i=0 ; i<PixCanon ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
  tokenImpact=0;
  thisHub.hit=1;
  }
}


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


  if (thisHub.hit || tokenImpact){
    impactFB();
  }
  else if (thisHub.oldLife != thisHub.life) {
    float qsd = thisHub.life/10 ;
    for(int i = 0; i<Pix; i++) {strip.setPixelColor(i, 0, 0, 0);}
    for(int i=0; i<qsd; i++) {
      Serial.println(i);
      strip.setPixelColor(i, 100*bright, 100*bright, 100*bright); 
      strip.show();
    }
  }

  
}
