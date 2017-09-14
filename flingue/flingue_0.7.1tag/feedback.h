bool tokenSight;
bool tokenReload;
bool tokenShoot = 0 ;
void shootFb(int cmd = 1){

  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static int red ;
  static int green ;
  static int blue ;
  static float bright ;
  static int TC0 = 0 ;
  static int TC1 = 10 ;
  static int TC2 = 40 ;
  static int TC3 = 200 ;
  static int pixCanon = 3;


if (!cmd) {
  effetStopFlag=0;   //OSEF
  timeTag= 0;
}

  if (millis()-100>chrono+timeTag) {timeTag=millis();}
  chrono=millis() - timeTag;

  //Serial.print(chrono); Serial.print(" "); Serial.print(millis()); Serial.print(" "); Serial.println(timeTag);
  
  if (chrono>TC0 && chrono<TC1) {
    red=0;
    green=0;
    blue=0;
    
    stripCanon.setPixelColor(2, red, green, blue); 
    stripCanon.show();
    }

  if (chrono>TC1 && chrono<TC2){
    red=255;
    green=245;
    blue=0;

    stripCanon.setPixelColor(2, red, green, blue); 
    stripCanon.show();
    }
  
  if (chrono>TC2 && chrono<TC3) {
  bright = (TC3-chrono)/5;

  red=190*bright/100;
  green=40*bright/100;
  blue=5*bright/100;
  
  red=constrain(red, 0, 255);
  green=constrain(green, 0, 255);
  blue=constrain(blue, 0, 255);

  stripCanon.setPixelColor(2, red, green, blue); 
  stripCanon.show();
  }
  if (chrono>TC3) {
    red=0;
    green=0;
    blue=0;

    stripCanon.setPixelColor(2, red, green, blue); 
    stripCanon.show();
    
    tokenShoot=LOW;
    }

}
