bool fireCastToken = LOW ;
void fireCastFb(){

  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static int red ;
  static int green ;
  static int blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 3000 ;
  static int TC2 = TC1 + 1000 ;
  static int TC3 = TC2 + 1000 ;
  
  static int TC4 ;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;
  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);

if (stopEffectToken) chrono = TC3 ;
  
  if (chrono>TC0 && chrono<TC1) {
    for(int i=0; i< PIXNUMBER ; i++) {
      red  = random(210, 255);
      green= red - 160 ;
      green= green + random(0,100);

      bright = map(chrono, TC0, TC1, 0, 50) ;
      bright /= 100 ;
      
      strip.setPixelColor(i, red*bright, green*bright, 0); 
      strip.show();
    }
  }
  if (chrono>TC1 && chrono<TC2) {
    for(int i=0; i< PIXNUMBER ; i++) {
      red  = random(210, 255);
      green= red - 160 ;
      green= green + random(0,100);

      bright = 0.5 ;
      strip.setPixelColor(i, red*bright, green*bright, 0); 
      strip.show();
    }
  }
  if (chrono>TC2 && chrono<TC3) {
    for(int i=0; i< PIXNUMBER ; i++) {
      red  = random(210, 255);
      green= red - 160 ;
      green= green + random(0,100);

      blue = map(chrono, TC2, TC3, 0, 80);

      bright = map(chrono, TC2, TC3, 50, 0) ;
      bright /= 100 ;

      strip.setPixelColor(i, red*bright, green*bright, blue*bright); 
      strip.show();
    }
  }
  if (chrono>TC3 ) {
    for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
  fireCastToken=LOW;
  }
}


//unsigned long timeCancelT2F ; useless ?

bool fireBallFbToken = LOW ;
void fireBallFb(){

  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static int red ;
  static int green ;
  static int blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 100 ;
  static int TC2 = TC1 + 200 ;
  static int TC3 = TC2 + 1000 ;
  
  static int TC4 ;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;
  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);

if (stopEffectToken) chrono = TC3 ;
  
  if (chrono>TC0 && chrono<TC1) {
    for(int i=0; i< PIXNUMBER ; i++) {
      red  = random(210, 255);
      green= red - 160 ;
      green= green + random(0,100);

      bright = map(chrono, TC0, TC1, 0, 100);
      bright /= 100 ;
      
      strip.setPixelColor(i, red*bright, green*bright, blue*bright); 
      strip.show();
    }
  }
  if (chrono>TC1 && chrono<TC2) {
    for(int i=0; i< PIXNUMBER ; i++) {
      red  = random(230, 255);
      green= red - 160 ;
      green= green + random(70,100);
      blue = 80 ;

      bright = 1 ;
      strip.setPixelColor(i, red*bright, green*bright, blue*bright); 
      strip.show();
    }
  }
  if (chrono>TC2 && chrono<TC3) {
    for(int i=0; i< PIXNUMBER ; i++) {
      red  = random(150, 255);
      green= red - 160 ;
      green= green + random(0,100);
      blue = 0 ;
      //blue = map(chrono, TC2, TC3, 0, 80);

      bright = map(chrono, TC2, TC3, 70, 0) ;
      bright /= 100 ;

      strip.setPixelColor(i, red*bright, green*bright, blue*bright); 
      strip.show();
    }
  }
  if (chrono>TC3 ) {
    for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
  fireBallFbToken=LOW;
  }
}

bool protectionCastToken = LOW ;
void protectionCastFb(){
  //PIXNUMBER
  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static float red ;
  static float green ;
  static float blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 5000 ;
  static float index ;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;
  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);

if (stopEffectToken) chrono = TC1 ;

  red = 200;
  green = 200;
  blue = 200;
  
  if (chrono>TC0 && chrono<TC1) {
    //for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); }
      //for(int i=0; i<PIXNUMBER ; i++) {

      int i = random(0 , PIXNUMBER);
      bright = random(0 , 10);
      bright /= 100 ;
      
      strip.setPixelColor(i, red*bright, green*bright, blue*bright); 
      strip.show();
      //}
  }
  if (chrono>TC1 ) {
    for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); strip.show();}
  protectionCastToken=LOW;
  }
}

bool protectionFbToken = LOW ;
void protectionFb(){
  //PIXNUMBER
  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static float red ;
  static float green ;
  static float blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 200 ;
  static int TC2 = TC1 + 2000 ;
  static int TC3 = TC2 + 500 ;
  static float index ;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;
  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);

if (stopEffectToken) chrono = TC3 ;

  red = 200;
  green = 200;
  blue = 200;
  
  if (chrono>TC0 && chrono<TC1) {
    //for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); }
      for(int i=0; i<PIXNUMBER ; i++) {
        
      bright = map(chrono, TC0, TC1, 0, 100);
      bright /= 100 ;
      
      strip.setPixelColor(i, red*bright, green*bright, blue*bright); 
      strip.show();
      }
  }
  if (chrono>TC1 && chrono<TC2){
    //for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); }
      for(int i=0; i<PIXNUMBER ; i++) {

      //bright = random(85, 100);
      //Serial.println(bright);
      //bright /= 100 ;
      //bright = constrain(bright, 0, 100);
      bright = 100 ;

      strip.setPixelColor(i, red*bright/100, green*bright/100, blue*bright/100); 
      strip.show();
      }
  }
  if (chrono>TC2 && chrono<TC3){
    //for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); }
      for(int i=0; i<PIXNUMBER ; i++) {
        
      bright = map(chrono, TC2, TC3, 100, 0);
      bright /= 100 ;
      
      strip.setPixelColor(i, red*bright, green*bright, blue*bright); 
      strip.show();
      }
  }
  if (chrono>TC3 ) {
    for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); strip.show();}
  protectionFbToken=LOW;
  }
}

