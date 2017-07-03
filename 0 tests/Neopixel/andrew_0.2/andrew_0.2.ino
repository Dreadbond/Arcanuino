
#include <math.h> //can't remember if needed, but anyway.

#include <Adafruit_NeoPixel.h>  //I use this lib because ... no reason. I always used this one, and maybe I'll switch to another one one day :). But for now it fits me.
#define PIN 6                   //pin number that you have connected your data pin to
#define PIXNUMBER 30            //number of neopixels you have connected

#define sps Serial.print(" ");   //Just a trick i use for shortening my serial monitor display commands.
#define spr Serial.println();    //

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXNUMBER, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options


/* So down here are my Neopixel (NP) feedback functions. 
 * It is not very optimised, but it works !
 * The principle is to have a "token" (just a boolean value) injected in the system.
 * As long the token is in the system (token = 1, or HIGH), the function displays the NP animation based on a timeline (that your create).
 * There are Timecodes (TC) and an chronometer (chrono). When the chrono value is between two timecodes, a certain NP behaviour is executed.
 * Quite simple : between 0ms and 1000ms, do something, between 1000 and 5000, do something else etc.
 * When it reaches the final TC, the token is "flushed down" (returns to 0 or LOW, same thing), and it waits for the next token to redisplay the pattern.
 * 
 * This system is interesting in my project, because i don't need to permanently display NPs, and I sometimes need a different NP pattern.
 * But in yours, it could be used to test several pattern, keep your loop() code clean, and other things (I guess).
 */


bool playToken;                     //the token to activate this pattern
void playPatternOne(int param = 1){              //a pattern function. I added the "param" function to have more control over it.

  if (param == 0) {  playToken = LOW ;  }           //Simple, if you call "playPatternOne(0);", this stops the pattern. Brutally.

  static unsigned long chrono ;                   //the chronometer, used as a reference to know when to trigger stuffs.
  static unsigned long timeTag ;                  //the timetag : moment when the token was injected. It keeps the chrono open as long as the function is executed.
  static unsigned long fileDuration = 6000 ;      //the time in milliseconds of your audio file. Needed to see the progression. For now let's imagine a 6 seconds long file.
                                                  //static means that all these datas only exists in this function. 
                                                  //So if you want another NP pattern, you just can copy/past a function and don't care about inner variables names ! Just change the function name and token.
    
  static float red ;                //color values. float is better when you have to manipulate datas (divide, etc. But can't be negative !).
  static float green ;              
  static float blue ;               
  static float bright ;             //A value to control brightness. Never use strip.setBrightness(), this is slow and may cause some bugs.

  
  static int TC0 = 0 ;              //The timecode values. I begin with 0, but we can imagine a delayed feedback that starts at 500ms for instance. 
  static int TC1 = fileDuration ;
  static int TC2 = TC1 + 1000 ; //As you told me, all pixels stays lit for 1 sec
  static int TC3 = TC2 + 2000 ; //And fades out for 2 secs.
  static float index ;              //a value i use for selecting a specific NP led.


  if (millis() - 100 > chrono + timeTag) { timeTag = millis(); }    //Ok, the tricky part... I don't really remember how I wrote this, but it works ! But it needs to be rewritten for understanding purpose. Later !
                                                                    //This is the function's time engine. It creates a timeTag at the very moment the function is triggered FOR THE FIRST TIME ! And keeps the chrono updated compared to the timetag.
                                                                    //It's for the convenient part, so we just have to worry about designing a pretty timeline-based effect.
            chrono = millis() - timeTag;                              //Part of the time engine ...

//////////////////////////////////////////////////////////////////////And from this part, you can design whatever you want !
  //Serial.println(chrono);
  red = 100 ;                             //For now, the strip will only go blue. We'll change this later
  green = 50 ;
  blue = 255 ;

  //First step "NP to ramp up in a single color, one pixel at a time, until all pixels are lit."
  if (chrono>TC0 && chrono<TC1) {                                          //"if" function to trigger events, just put the right timecodes. Here, it begins at 0, the first function's triggering, to TC1, the end of your soundfile
    for(int i=0 ; i < index ; i++) {strip.setPixelColor(i, 0, 0, 0);}    //set all leds to 0, but don't show() ! It prevents for lights to stay lit when not desired.

    bright = 100 ; //in percentage
                                                    
    index = map(chrono, TC0, TC1, 1 , PIXNUMBER * 10 );     //map() function. So the index goes from 0 to your number of NP leds (PIXNUMBER) proportionally with your soundfile
    index /= 10 ;                                            //I put "PIXNUMBER * 10" and just after: "/= 10" to have a real float number. So the next led could have a diming effect

    int intLed = index ;                                 //This is a trick to separate integers from floats numbers
    float remainingDim = index - intLed ;                //in remainingDim, we have a number between 0 (included) and 1. The intensity of the last led, to smooth all this
    
    //Here, i use my index variable so know wich NP to lit.
    for (int j=-1  ; j < index ; j++) {       //select NP from 0 to index, where j is the pixel number
      red   *= bright/100 ;
      green *= bright/100 ;           //"green *= ..."is the same thing as "green = green * ..."
      blue  *= bright/100 ;
      strip.setPixelColor(j, red, green, blue);     //set them blue
    }

                                       //If the light begins at 0, it creates a hard effect.
    int smoothingValue = 10 ;          //So this value is here to tell at wich value it shall begins the dimming of the Led (in percent). 
                                       //10 is quite good
                                       

    remainingDim *= 100 ;
    remainingDim = map(remainingDim, 0, 100, smoothingValue, 100);      //So "remainingDim" will output a number between "smoothingValue" and "100"
    remainingDim /= 100 ;                                               // *100 and /100 because map() doesn't seem to work with 0. numbers
    
    red   *= remainingDim * bright / 100 ;   //The calculation to dim the last Led, * the general brightness
    green *= remainingDim * bright / 100 ;
    blue  *= remainingDim * bright / 100 ;
    
    strip.setPixelColor(index + 1, red, green, blue);

    
    strip.show();      //display the NP. The less it is polled, the less to have a bug chances are. So let's keep it out of for () function
  }

  //Next step, just lit all pixels "All pixels should stay lit for about 1000ms"
  if (chrono>TC1 && chrono<TC2){          

      for(int i=0; i<PIXNUMBER ; i++) {   //"for" used to tell wich pixels to lit. 0, then 0 and 1, then 0 and 1 and 2 etc ...
        bright = 100 ;    //stays at 100
        strip.setPixelColor(i, red*bright/100, green*bright/100, blue*bright/100); 
      }
      strip.show();
  }

  //"then fade out for 2000ms." So be it.
  if (chrono>TC2 && chrono<TC3){          
      bright = map(chrono, TC2, TC3, 100, 0);      //map function to ramp down. From TC2 to TC3, bright goes from 100 (percent) to 0. 

      for(int i=0; i<PIXNUMBER ; i++) {
        strip.setPixelColor(i, red*bright/100, green*bright/100, blue*bright/100); 
      }
      strip.show();
  }
  if (chrono>TC3 ) {
    for(int i=0 ; i<PIXNUMBER ; i++) {strip.setPixelColor(i, 0, 0, 0); strip.show();} //everybody shut down !
  playToken=LOW;   //flush the token down
  delay(3000);     //and delete this, it was just for the demo mode !
  }


}



////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// SETUP /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() 
{
  strip.begin();
  strip.show();//sets all pixels to off state
  strip.setBrightness(255);     //only poll setBrightness once, in setup. Or not.

  Serial.begin(9600); 
  Serial.println("Andrew' project V0.2");

} 

////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// LOOP //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////


void loop() {
  
  if (digitalRead(2)) {         //If button is pressed, the "token" (just a boolean) is created (so the button doesn't needs to stay pressed to see the effect ...). Add your soundfile play function here too (or a token for it :) ).
    playToken=1 ;
  }

  //For the demo mode only ! Delete this to work with your button
  playToken=1 ;   
  
  if (playToken)   { playPatternOne();}     //If there's a token in the system, we call a function to begin the Neopixel animation.
                                            //At the end of the function, playToken goes to 0, so it stops.
                                            //For the stop function, call "playPatternOne(0)". I have added a thing to the beggining of the function
}








