 ////////////////////////////////////////////////////////////////////On fire
  bool tokenFireCast ;
  void fireCast(String cmd = ""){
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
      chrono = TC2 ;
      //TC3 = millis() + more ;
      //TC2 = TC3 - 250 ;
      bright = 100 ;
      }
    if (!cmd) chrono = TC3 ;
    
    if (chrono>TC0 && chrono<TC1) {
      for(int i=0; i<PIX ; i++) {

      red  = random(210, 255);
      green= red - 160 ;
      green= green + random(0,100);

      bright = map(chrono, TC0, TC1, 0, 100) ;
      bright /= 100 ;
  
        page.setPixelColor(i, red*bright, green*bright, 0); 
        page.show();
      }
    }

    if (chrono>TC1 && chrono<TC2) {
      for(int i=0; i<PIX ; i++) {

      red  = random(210, 255);
      green= red - 160 ;
      green= green + random(0,100);

      bright = 100 ;
      bright /= 100 ;
  
        page.setPixelColor(i, red*bright, green*bright, 0); 
        page.show();
      }
    }

  if (chrono>TC2 && chrono<TC3) {
    for(int i=0; i< PIX ; i++) {
      red  = random(210, 255);
      green= red - 160 ;
      green= green + random(0,100);

      blue = map(chrono, TC2, TC3, 0, 80);

      bright = map(chrono, TC2, TC3, 50, 0) ;
      bright /= 100 ;

      page.setPixelColor(i, red*bright, green*bright, blue*bright); 
      page.show();
    }
  }

    if (chrono>TC3) {
      for(int i=0 ; i<PIX ; i++) {page.setPixelColor(i, 0, 0, 0);  
      page.show();}
    tokenFireCast = LOW;
    }
  cmd = "" ;
  }
