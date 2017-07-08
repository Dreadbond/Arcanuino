
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
  String inMessage ;
  
  unsigned long nextRespawn ;

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
    //thisHub.hit=0 ;
    tokenImpact=LOW;
    lifeDisplay=1;
    }
  }
  
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



void hubReceiveSP() {
  /*
  if (Serial.available() ) {
    thisHub.inMessage = Serial.readStringUntil('}');
    Serial.println(thisHub.inMessage);
    }*/
  //{"to":":hub","from":"!111111","param":"beenShot","value":1}
  //{"to":":hub","from":"!111111","param":"health","value":40}

  for (int i=0 ; i< inMessage.length() ; i++) {
    if (inMessage.startsWith(":hub", i) ) {
      for (int j=0 ; j < inMessage.length() ; j++) {
        
          if (inMessage.startsWith("beenShot", j) ){
          thisHub.tokenImpact = 1 ;
          break;
          }

          if (inMessage.startsWith("health", j) ){
            String arf = "" ;
            int k = j + sizeof("health") ;
              for ( k ; k < inMessage.length() ; k++){
                arf += inMessage.charAt(k + sizeof("\"value\":"));
                }
          thisHub.life = arf.toInt() ;
          thisHub.lifeDisplay=1;
          break;
          }
        }
      inMessage = "" ;
      }//fin inMessage
    

  }
}



void hubLoop() {

  if (thisHub.tokenImpact) {thisHub.impactFB();}

  if (thisHub.lifeDisplay) 
    {
      
    //int ledToShow ;
    float ledToShow = map(thisHub.life, 0, 100, 0, 8 * 10);
    ledToShow /= 10 ;

    int intLed = ledToShow ;
    float remainingDim = ledToShow - intLed ;
    
    for(int i = 0; i<Pix; i++) {strip.setPixelColor(i, 0, 0, 0);}
    
    for(int i=0; i<ledToShow ; i++) {
      strip.setPixelColor(i, 100*bright, 0, 0); 
      }
      strip.setPixelColor(ledToShow + 1, 100*remainingDim*bright, 0, 0);
      
    strip.show();
    thisHub.lifeDisplay=0;
  }
  
}











