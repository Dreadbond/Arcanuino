
typedef struct{
  String Name ;
  String tag = IDObject ;
  int oldLife ;
  int maxLife = 100 ;
  int life = 100 ;
  int armor = 0 ;
  bool hit ;
  bool lifeDisplay ;
  bool dead ;
  int damage ;

  unsigned long nextRespawn ;
}
selfHub;

selfHub thisHub;

///////////////////////////////////////////////////////////////////Impact
bool tokenImpact ;
void impactFB(){
  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static float red ;
  static float green ;
  static float blue ;
  static float bright ;

  static int TC0 = 0 ;
  static int TC1 = 50 ;
  static int TC2 = 100 ;
  static int TC3 = 150 ;
  static int TC4 = 200 ;
  static int TC5 = 250 ;
  static int TC6 = 300 ;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;
  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);
  
  if (chrono>TC0 && chrono<TC1) {
   //for(int i=0 ; i<Pix ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
    for(int i=0; i<Pix ; i++) {

      bright= map(chrono, TC0, TC1, 0, 80);
      strip.setPixelColor(i, 255*bright/100, 0, 0); 
      strip.show();
    }
  }
  if (chrono>TC1 && chrono<TC2){
    //for(int i=0 ; i<Pix ; i++) {strip.setPixelColor(i, 255, 0, 0);  strip.show();}
     for(int i=0; i<Pix ; i++) {
      
      bright= map(chrono, TC1, TC2, 100, 0);
      strip.setPixelColor(i, 255*bright/100, 0, 0); 
      strip.show();
     }
  }
  if (chrono>TC2 && chrono<TC3) {
   //for(int i=0 ; i<Pix ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
    for(int i=0; i<Pix ; i++) {

      bright= map(chrono, TC2, TC3, 0, 80);
      strip.setPixelColor(i, 255*bright/100, 0, 0); 
      strip.show();
    }
  }
  if (chrono>TC3 && chrono<TC4){
    //for(int i=0 ; i<Pix ; i++) {strip.setPixelColor(i, 255, 0, 0);  strip.show();}
     for(int i=0; i<Pix ; i++) {
      
      bright= map(chrono, TC3, TC4, 100, 0);
      strip.setPixelColor(i, 255*bright/100, 0, 0); 
      strip.show();
     }
  }
  if (chrono>TC4 && chrono<TC5) {
   //for(int i=0 ; i<Pix ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
    for(int i=0; i<Pix ; i++) {

      bright= map(chrono, TC4, TC5, 0, 80);
      strip.setPixelColor(i, 255*bright/100, 0, 0); 
      strip.show();
    }
  }
  if (chrono>TC5 && chrono<TC6){
    //for(int i=0 ; i<Pix ; i++) {strip.setPixelColor(i, 255, 0, 0);  strip.show();}
     for(int i=0; i<Pix ; i++) {
      
      bright= map(chrono, TC5, TC6, 100, 0);
      strip.setPixelColor(i, 255*bright/100, 0, 0); 
      strip.show();
     }
  }
  if (chrono>TC6) {
    for(int i=0 ; i<Pix ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
  thisHub.hit=0 ;
  tokenImpact=LOW;
  thisHub.lifeDisplay=1;
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
      thisHub.lifeDisplay=1;

      thisHub.nextRespawn = millis() + 5000 ;
    }
  
  if (thisHub.oldLife != thisHub.life) {thisHub.lifeDisplay=1;}
} //ifdead loop

  if (thisHub.nextRespawn < millis() && thisHub.dead) {
   thisHub.life = thisHub.maxLife ;
   thisHub.lifeDisplay = 1 ;
   thisHub.dead = 0 ;
  }

  if (thisHub.hit) {impactFB();}

  if (thisHub.lifeDisplay) 
    {
    
    //float qsd = thisHub.life/10 ;
    float ledToShow = map(thisHub.life, 0, thisHub.maxLife, 0, 80);
    ledToShow /= 2 ;
    int intLed = ledToShow ;
    float remainingLed = ledToShow - intLed ;
    
    for(int i = 0; i<Pix; i++) {strip.setPixelColor(i, 0, 0, 0);}
    for(int i=0; i<intLed ; i++) {
      strip.setPixelColor(i, 100*bright, 0, 0); 
      //strip.show();    //besoin ici ?
      thisHub.lifeDisplay=0; //après show(), non ?
    }

    strip.setPixelColor(intLed, 100*bright*remainingLed, 0,0); //last Led, with the RemainingLed brightness
    strip.show();
  }
  
}











