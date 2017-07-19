
typedef struct{
  String tag = IDObject ;
  int oldhealth ;
  int maxhealth = 100 ;
  int health = 100 ;
  int armor = 0 ;
  bool hit ;
  bool healthDisplay ;
  int damage ;
  
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
    static int TC6 = 150 ;
    static int TC4 = 200 ;
    static int TC5 = 250 ;
    static int TC3 = 300 ;
  
    if (millis()-100>chrono+timeTag) {timeTag=millis();}
    chrono=millis() - timeTag;
    
    if (chrono>TC0 && chrono<TC1) {
      for(int i=0; i<Pix ; i++) {
  
        bright= map(chrono, TC0, TC1, 0, 80);
        strip.setPixelColor(i, 255*bright/100, 0, 0); 
        strip.show();
      }
    }
    if (chrono>TC1 && chrono<TC2){
       for(int i=0; i<Pix ; i++) {
        
        bright= map(chrono, TC1, TC2, 100, 0);
        strip.setPixelColor(i, 255*bright/100, 0, 0); 
        strip.show();
       }
    }
    if (chrono>TC2 && chrono<TC3) {
      for(int i=0; i<Pix ; i++) {
  
        bright= map(chrono, TC2, TC3, 0, 80);
        strip.setPixelColor(i, 255*bright/100, 0, 0); 
        strip.show();
      }
    }
    if (chrono>TC3 && chrono<TC4){
       for(int i=0; i<Pix ; i++) {
        
        bright= map(chrono, TC3, TC4, 100, 0);
        strip.setPixelColor(i, 255*bright/100, 0, 0); 
        strip.show();
       }
    }
    if (chrono>TC4 && chrono<TC5) {
      for(int i=0; i<Pix ; i++) {
  
        bright= map(chrono, TC4, TC5, 0, 80);
        strip.setPixelColor(i, 255*bright/100, 0, 0); 
        strip.show();
      }
    }
    if (chrono>TC5 && chrono<TC6){
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
    healthDisplay=1;
    }
  }

  ////////////////////////////////////////////////////////////////////On fire
  bool tokenOnFire ;
  void onFireFB(String cmd = ""){
    static bool effetStopFlag ;
    static unsigned long chrono ;
    static unsigned long timeTag ;
    static float red ;
    static float green ;
    static float blue ;
    static float bright ;
  
    static int TC0 = 0 ;
    static int TC1 = TC0 + 250 ;
    static int TC2 = TC1 + 500 ;
    static int TC3 = TC2 + 250 ;
    long more = 2000 ;

  
    if (millis()-100>chrono+timeTag) {timeTag=millis();}
    chrono=millis() - timeTag;

    if (cmd == "stop") chrono = TC3 ;
    if (cmd == "more" ) {
      TC3 = chrono + more ;
      TC2 = TC3 - 250 ;
      bright = 100 ;
      }
    if (!cmd) chrono = TC3 ;
    
    if (chrono>TC0 && chrono<TC1) {
      for(int i=0; i<Pix ; i++) {

      red  = random(210, 255);
      green= red - 160 ;
      green= green + random(0,100);

      bright = map(chrono, TC0, TC1, 0, 100) ;
      bright /= 100 ;
  
        stripFB.setPixelColor(i, red*bright, green*bright, 0); 
        stripFB.show();
      }
    }

    if (chrono>TC1 && chrono<TC2) {
      for(int i=0; i<Pix ; i++) {

      red  = random(210, 255);
      green= red - 160 ;
      green= green + random(0,100);

      bright = 100 ;
      bright /= 100 ;
  
        stripFB.setPixelColor(i, red*bright, green*bright, 0); 
        stripFB.show();
      }
    }

  if (chrono>TC2 && chrono<TC3) {
    for(int i=0; i< Pix ; i++) {
      red  = random(210, 255);
      green= red - 160 ;
      green= green + random(0,100);

      blue = map(chrono, TC2, TC3, 0, 80);

      bright = map(chrono, TC2, TC3, 50, 0) ;
      bright /= 100 ;

      stripFB.setPixelColor(i, red*bright, green*bright, blue*bright); 
      stripFB.show();
    }
  }

    if (chrono>TC3) {
      for(int i=0 ; i<Pix ; i++) {stripFB.setPixelColor(i, 0, 0, 0);  stripFB.show();}
    tokenOnFire = LOW;
    }
  cmd = "" ;
  }

  ////////////////////////////////////////////////////////////////////Poisoned
  bool tokenPoisoned ;
  void poisonedFB(String cmd = ""){
    static bool effetStopFlag ;
    static unsigned long chrono ;
    static unsigned long timeTag ;
    static float red ;
    static float green ;
    static float blue ;
    static float bright ;
  
    static int TC0 = 0 ;
    static int TC1 = TC0 + 250 ;
    static int TC2 = TC1 + 500 ;
    static int TC3 = TC2 + 500 ;
    long more = 2000 ;

  
    if (millis()-100>chrono+timeTag) {timeTag=millis();}
    chrono=millis() - timeTag;

    if (cmd == "stop") chrono = TC3 ;
    if (cmd == "more" ) {
      TC3 = chrono + more ;
      TC2 = TC3 - 500 ;
      bright = 100 ;
      }
      
    //if (!cmd) chrono = TC3 ;
    
    if (chrono>TC0 && chrono<TC1) {


      green = 100 ;
      //blue = 50 ;

      bright = map(chrono, TC0, TC1, 0, 100) ;
      bright /= 100 ;

        for(int i=0; i<Pix ; i++) {
        stripFB.setPixelColor(i, red*bright, green*bright, blue*bright); 
        stripFB.show();
      }
    }

    if (chrono>TC1 && chrono<TC2) {
      green += random(0,21);
      green -= 10 ;
      green = constrain(green, 0, 255) ;

      //blue = green - 100 ;
      //blue = constrain(blue, 0, 255) ;

      bright = 100 ;
      bright /= 100 ;
    
      for(int i=0; i<Pix ; i++) {
        stripFB.setPixelColor(i, red*bright, green*bright, blue*bright); 
        stripFB.show();
      }
    }

  if (chrono>TC2 && chrono<TC3) {
      green += random(1,10);
      green -= 5 ;
      green = constrain(green, 0, 255) ;

      //blue = green - 100 ;
      //blue = constrain(blue, 0, 255) ;

      bright = map(chrono, TC2, TC3, 100, 0) ;
      bright /= 100 ;
      
    for(int i=0; i< Pix ; i++) {
      stripFB.setPixelColor(i, red*bright, green*bright, blue*bright); 
      stripFB.show();
    }
  }

    if (chrono>TC3) {
      for(int i=0 ; i<Pix ; i++) {stripFB.setPixelColor(i, 0, 0, 0);  stripFB.show();}
    tokenPoisoned = LOW;
    }
  cmd = "" ;
  }

  ////////////////////////////////////////////////////////////////////Shield
  bool tokenShield ;
  void shieldFB(String cmd = ""){
    static bool effetStopFlag ;
    static unsigned long chrono ;
    static unsigned long timeTag ;
    static float red ;
    static float green ;
    static float blue ;
    static float bright ;
  
    static int TC0 = 0 ;
    static int TC1 = TC0 + 500 ;
    static int TC2 = TC1 + 500 ;
    static int TC3 = TC2 + 250 ;
    long more = 2000 ;

  
    if (millis()-100>chrono+timeTag) {timeTag=millis();}
    chrono=millis() - timeTag;

    if (cmd == "stop") chrono = TC3 ;
    if (cmd == "more" ) {
      TC3 = chrono + more ;
      TC2 = TC3 - 250 ;
      bright = 100 ;
      }
      
    
    if (chrono>TC0 && chrono<TC1) {

      red = 255 ;
      green = 255 ;
      blue = 255 ;

      bright = map(chrono, TC0, TC1, 0, 100) ;
      bright /= 100 ;

        for(int i=0; i<Pix ; i++) {
        stripFB.setPixelColor(i, red*bright, green*bright, blue*bright); 
        stripFB.show();
      }
    }

    if (chrono>TC1 && chrono<TC2) {

      red = 255 ;
      green = 255 ;
      blue = 255 ;

      bright *= 100 ;

      bright += random(0,6);
      bright -= 3 ;
      bright = constrain(bright, 0, 100) ;

      bright /= 100 ;

      for(int i=0; i<Pix ; i++) {
        stripFB.setPixelColor(i, red*bright, green*bright, blue*bright); 
        stripFB.show();
      }
    }

  if (chrono>TC2 && chrono<TC3) {
    
      red = 255 ;
      green = 255 ;
      blue = 255 ;

      bright = map(chrono, TC2, TC3, 100, 0) ;
      bright /= 100 ;
      
    for(int i=0; i< Pix ; i++) {
      stripFB.setPixelColor(i, red*bright, green*bright, blue*bright); 
      stripFB.show();
    }
  }

    if (chrono>TC3) {
      for(int i=0 ; i<Pix ; i++) {stripFB.setPixelColor(i, 0, 0, 0);  stripFB.show();}
    tokenShield = LOW;
    }
  cmd = "" ;
  }

  ////////////////////////////////////////////////////////////////////Healed
  bool tokenHealed ;
  void healedFB(String cmd = ""){
    static bool effetStopFlag ;
    static unsigned long chrono ;
    static unsigned long timeTag ;
    static float red ;
    static float green ;
    static float blue ;
    static float bright ;
  
    static int TC0 = 0 ;
    static int TC1 = TC0 + 500 ;
    static int TC2 = TC1 + 500 ;
    static int TC3 = TC2 + 250 ;
    long more = 2000 ;

      red = 255 ;
      green = 255 ;
      blue = 0 ;
  
    if (millis()-100>chrono+timeTag) {timeTag=millis();}
    chrono=millis() - timeTag;

    if (cmd == "stop") chrono = TC3 ;
    if (cmd == "more" ) {
      TC3 = chrono + more ;
      TC2 = TC3 - 250 ;
      bright = 100 ;
      }


    if (chrono>TC0 && chrono<TC1) {

      bright = map(chrono, TC0, TC1, 0, 100) ;
      bright /= 100 ;

        for(int i=0; i<Pix ; i++) {
        stripFB.setPixelColor(i, red*bright, green*bright, blue*bright); 
        stripFB.show();
      }
    }

    if (chrono>TC1 && chrono<TC2) {

      bright = 1 ;

      for(int i=0; i<Pix ; i++) {
        stripFB.setPixelColor(i, red*bright, green*bright, blue*bright); 
        stripFB.show();
      }
    }

  if (chrono>TC2 && chrono<TC3) {

      bright = map(chrono, TC2, TC3, 100, 0) ;
      bright /= 100 ;
      
    for(int i=0; i< Pix ; i++) {
      stripFB.setPixelColor(i, red*bright, green*bright, blue*bright); 
      stripFB.show();
    }
  }

    if (chrono>TC3) {
      for(int i=0 ; i<Pix ; i++) {stripFB.setPixelColor(i, 0, 0, 0);  stripFB.show();}
    tokenHealed = LOW;
    }
  cmd = "" ;
  }

}
selfHub;

selfHub thisHub;




void hubReceive(String to, String param, float value){
  //Sert pour jeu avec les routeurs
  if (to == thisHub.tag && justReceive) {
    if (param=="hit") {
      thisHub.damage=value;
      thisHub.hit=1;
    }
  }
}



void hubFeedback() {

  //{"to":":hub","from":"!111111","param":"beenShot","value":1}
  //{"to":":hub","from":"!111111","param":"health","value":40}
  //{"to":":hub","from":"!111111","param":"onFire","value":1}
  //{"to":":hub","from":"!111111","param":"poisoned","value":1}
  //{"to":":hub","from":"!111111","param":"shield","value":1}
  //{"to":":hub","from":"!111111","param":"healed","value":1}


  for (int i=0 ; i< inMessage.length() ; i++) {
    if (inMessage.startsWith(":hub", i) ) {
      for (int j=0 ; j < inMessage.length() ; j++) {
        
          if (inMessage.startsWith("beenShot", j) ){
          thisHub.tokenImpact = 1 ;
          break;
          }

          if (inMessage.startsWith("healed", j) ){
          thisHub.tokenHealed = 1 ;
          thisHub.healedFB("more") ;
          break;
          }

          if (inMessage.startsWith("shield", j) ){
          thisHub.tokenShield = 1 ;
          thisHub.shieldFB("more") ;
          break;
          }

          if (inMessage.startsWith("poisoned", j) ){
          thisHub.tokenPoisoned = 1 ;
          thisHub.poisonedFB("more") ;
          break;
          }

          if (inMessage.startsWith("onFire", j) ){
          thisHub.tokenOnFire = 1 ;
          thisHub.onFireFB("more") ;
          break;
          }

          if (inMessage.startsWith("health", j) ){
            String arf = "" ;
            int k = j + sizeof("health") ;
              for ( k ; k < inMessage.length() ; k++){
                arf += inMessage.charAt(k + sizeof("\"value\":"));
                }
          thisHub.health = arf.toInt() ;
          thisHub.healthDisplay=1;
          break;
          }
        }
      inMessage = "" ;
      }//fin inMessage
  }
}



void hubCode() {

  if (thisHub.tokenImpact) {thisHub.impactFB();}

  if (thisHub.tokenShield) {
    thisHub.shieldFB() ;
    }

  if (thisHub.tokenHealed) {
    thisHub.healedFB() ;
    }
  
  if (thisHub.tokenOnFire) {
    thisHub.onFireFB() ;
    }
    
  if (thisHub.tokenPoisoned) {
    thisHub.poisonedFB() ;
    }
    
  if (thisHub.healthDisplay) 
    {
      
    //int ledToShow ;
    float ledToShow = map(thisHub.health, 0, 100, 0, 8 * 10);
    ledToShow /= 10 ;

    int intLed = ledToShow ;
    float remainingDim = ledToShow - intLed ;
    
    for(int i = 0; i<Pix; i++) {strip.setPixelColor(i, 0, 0, 0);}
    
    for(int i=0; i<ledToShow ; i++) {
      strip.setPixelColor(i, 100*bright, 0, 0); 
      }
      strip.setPixelColor(ledToShow + 1, 100*remainingDim*bright, 0, 0);
      
    strip.show();
    thisHub.healthDisplay=0;
  }
  
}

