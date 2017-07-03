
bool tokenProtec;


bool tokenEnAvant;
void enAvantFB(){
  //PIXNUMBER
  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static int red ;
  static int green ;
  static int blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 1500 ;
  static int TC2 = 2000 ;
  static int TC3 = 3000 ;
  static int index ;

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;
  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);


  
  if (chrono>TC0 && chrono<TC1) {
    for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0);}  //  strip.show();  <--- show() utile ?
    
    index = (TC1/chrono)*PIXNUMBER ;
      Serial.println(index);
    strip.setPixelColor(index, 150, 150, 0); 
    strip.show();
    strip.setPixelColor(index-1, 100, 100, 0); 
    strip.show();
    strip.setPixelColor(index-2, 50, 50, 0); 
    strip.show();
  }
  if (chrono>TC1 && chrono<TC2){
    for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); }
      for(int i=3; i<PIXNUMBER ; i++) {
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
    for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0);  strip.show();}
  tokenEnAvant=LOW;
  effetStopFlag=HIGH;
  }
}


/*
bool tokenClock;
void teinteFeu(int intens, int posI) {
    //strip.setBrightness(100);

    bright = intens * random(1, 5);
    bright = bright + 10;
    bright = constrain(bright, 20, 255);

    red  = random(160,200);
    //float red = float(red);
    red  = red + diffy*2;
    red  = red * bright;
    red  = red / 255;
    
    //green= red - 100 ;
    //float green = float(green);
    green = red * 0.9;
    green= green - random(0, 10);
    //green= green - diffy*2;
    green= green * bright;
    green = green/255;
    //green= green / 255;

    //float blue = float(blue);
    blue = random(0,10);
    blue = blue * bright;
    blue = blue / 255;

    red = constrain(red, 0, 255);
    green = constrain(green, 2, 245);
    blue = constrain(blue, 0, 255);

    strip.setPixelColor(posI, red, green, blue);
    nextRefresh = millis() + 10 ;
    strip.show();
}

bool tokenAntiClock;
void teintePoison(int intens, int posI) {
    //strip.setBrightness(100);
  
    bright = intens;
    bright += random(-1, 1);
    bright = bright + 10;
    bright = constrain(bright, 10, 255);
    
    red = random(1, 10);
    red = red + PIXNUMBER - posI*5;
    
    red  = red * bright;
    red  = red / 255;

    green= random(170, 200);
    green= green + diffy;
    
    green= green * bright;
    green= green / 255;
    
    blue = green - 100;
    blue = blue - random(10, 30);
    blue = blue + PIXNUMBER - posI*5;
    
    blue = blue * bright;
    blue = blue / 255;
    
    red = constrain(red, 0, 255);
    green = constrain(green, 0, 255);
    blue = constrain(blue, 0, 245);

    strip.setPixelColor(posI, red, green, blue);
    nextRefresh = millis() + 20 ;
    strip.show();
}

bool tokenMoulinet;
void teinteBerserk(int intens, int posI) {
    //red  = random(1,160);
    red = 10;
    red  = red + intens*2;
    red  += posI*3;
    
    green= 0;
    
    blue = 0;
    
    red = constrain(red, 0, 255);
    green = constrain(green, 0, 255);
    blue = constrain(blue, 0, 255);

    strip.setPixelColor(posI, red, green, blue);
    nextRefresh = millis() + 10 ;
    strip.show();
/*
    bright = diffy * random(1, 5);
    bright = bright + 10;
    bright = constrain(bright, 20, 255);
    }

    */

