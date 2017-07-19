bool shootVibToken = LOW ;

void shootVibFb(){
  
  static bool effetStopFlag ;
  static unsigned long chrono ;
  static unsigned long timeTag ;
  static int red ;
  static int green ;
  static int blue ;
  static float vibreur ;
  static int TC0 = 0 ;
  static int TC1 = 70 ;
  static int TC2 = TC1 + 20 ;
  static int TC3 = TC2 + 500 ;
  static bool refresh ;
  static unsigned long nextRefresh ;
  
  static int TC4 ;

  if (chrono > nextRefresh ) {refresh = true;}
  
  if (millis()-100>chrono+timeTag) {timeTag=millis(); refresh = true ;}
  chrono=millis() - timeTag;

  
  if (chrono>TC0 && chrono<TC1 ) {


      vibreur = 255 ;//map(chrono, TC0, TC1, 40, 255) ;
      Serial.println(vibreur);
      
      analogWrite(motorPin, vibreur);

      refresh = false;
      nextRefresh = chrono + 100 ;
      
  }
  if (chrono>TC1 && chrono<TC2 ) {


      //vibreur = random(40, 255) ;
      vibreur = 255 ;
      Serial.println(vibreur);

      analogWrite(motorPin, vibreur);

      refresh = false;
      nextRefresh = chrono + 200 ;
  }
  if (chrono>TC2 && chrono<TC3 ) {  //&& refresh


      vibreur = map(chrono, TC2, TC3, 150, 40) ;
      Serial.println(vibreur);
      analogWrite(motorPin, vibreur);

      refresh = false;
      nextRefresh = chrono + 100 ;
  }
  if (chrono>TC3 ) {
      shootVibToken=LOW;
      vibreur = 0 ;
      Serial.println(vibreur);
      analogWrite(motorPin, vibreur);

  }
};
