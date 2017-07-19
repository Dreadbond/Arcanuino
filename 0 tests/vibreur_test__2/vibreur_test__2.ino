/*
Adafruit Arduino - Lesson 13. DC Motor
*/


int motorPin = 3;
int speed ;

bool fireCastToken = LOW ;

void fireCastFb(){
  



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
      fireCastToken=LOW;
      vibreur = 0 ;
      Serial.println(vibreur);
      analogWrite(motorPin, vibreur);

  }
};

void setup() 
{ 
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  while (! Serial);
  Serial.println("Speed 0 to 255");
} 
 
 
void loop() 
{ 
  
  if (Serial.available())
  {
    int erf = Serial.read() ;
Serial.println(erf);
    fireCastToken = true ;
    /*
    speed = Serial.parseInt();
    if (speed >= 0 && speed <= 255)
    {
      analogWrite(motorPin, speed);
    }*/
  }

if (fireCastToken) {fireCastFb();}


} 
