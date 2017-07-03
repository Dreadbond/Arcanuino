/*______________________________________________________________________________
 |                                                                              |
 |                            UKULELE TUNER                                     |
 |                                                                              |
 |                  AN ARDUINO PROJECT FOR YOUR UKULELE                         |
 |                                                                              |
 |  With Arduino Uno and Adafruit 2.8" TFT touch shield                         |
 |  http://www.adafruit.com/products/1651                                       |
 |  and a piezo buzzer (leads connected to Arduino A0 and ground).              |
 |                                                                              |
 | Touch screen calibration is from Adafruit on - off switch program            |
 | See Adafruit TFT shield tutorial                                             |
 | https://learn.adafruit.com/adafruit-2-8-tft-touch-shield-v2/overview         |
 |                                                                              |
 | // by William Buzz Wendt with thanks to Andrew Wendt for code help! //       |
 |______________________________________________________________________________|*/

/*
#include <Adafruit_GFX.h> // Adafruit graphics library
#include <SPI.h> // see https://www.arduino.cc/en/reference/SPI
#include <Wire.h> // see https://www.arduino.cc/en/reference/wire
#include <Adafruit_ILI9341.h> // ILI display driver
#include <Adafruit_STMPE610.h> // this line is for the CAPACITIVE TOUCH SCREEN
// note - if you have the RESISTIVE TOUCH SCREEN change the above line to #include <Adafruit_FT6206.h>

// Adafruit's calibration numbers for the TFT screen
#define TS_MINX 150 
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

// pin definitions for touch screen
#define STMPE_CS 8 
#define TFT_CS 10
#define TFT_DC 9

Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
*/
const int keyCount = 4;

// definition of struct Key (re struct see http://playground.arduino.cc/Code/Struct )
// Key object with frequency, x screen coordinate, and name (i.e. G, C, E, and A - the notes used for this ukulele tuning)
struct Key 
{
  int freq; 
  int x;
  char name;
};

// array of structures holding data about each key
// (frequency, x- screen coordinate, note name)
Key keys[] =
{
  { 392, 20, 'G'  },
  { 261, 90, 'C'  },
  { 329, 160, 'E'  },
  { 440, 230, 'A'  }
};

#define note_Y 50 // the y coordinate for drawing notes on screen
#define note_W 60 // note width on screen
#define note_H 100 // note height on screen

// piezo buzzer is connected to Arduino A0 and to ground
int buzzerPin= A0;

// duration that note plays and delay between notes
int duration = 500;
int del = 100;

void setup(void)
{
  Serial.begin(9600);
/*  tft.begin();
  if (!ts.begin()) 
  { 
    Serial.println("Unable to start touchscreen.");
  } 
  else 
  { 
    Serial.println("Touchscreen started."); 
  }
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(3);
  tft.setRotation(1); // 'landscape' screen rotation
  tft.fillScreen(ILI9341_BLACK);

  // Outline the keys
  for (int i = 0; i < keyCount; i++)
  {
    tft.drawRoundRect(keys[i].x + 5, note_Y+ 5, note_W - 10, note_H - 10, 10, ILI9341_BLUE);
    tft.drawRoundRect(keys[i].x, note_Y, note_W, note_H, 10,ILI9341_GREEN);
  }

  // Print note names on keys
  for (int i = 0; i < keyCount; i++)
  {
    tft.setCursor(keys[i].x + 22, note_Y + 10);
    tft.print(keys[i].name);
  }

  // print title 
  tft.drawRoundRect (70, 170, 180, 60, 10, ILI9341_WHITE);
  tft.drawRoundRect (75, 175, 170, 50, 10, ILI9341_WHITE);
  tft.setCursor(90, 190);
  tft.setTextColor(ILI9341_BLUE);
  tft.println("UKE TUNE");
*/
}

void loop()
{
  // See if there are touch data
  if (!ts.bufferEmpty())
  {   
    // Retrieve a point  
    TS_Point p = ts.getPoint(); 
    // Scale using the calibration #'s
    // and rotate coordinate system
    p.x = map(p.x, TS_MINY, TS_MAXY, 0, tft.height());
    p.y = map(p.y, TS_MINX, TS_MAXX, 0, tft.width());
    int y = tft.height() - p.x;
    int x = p.y;


    // screen touch handler
    for (int i = 0; i < keyCount; i++)
    {
      if ((x > keys[i].x) && (x < (keys[i].x + note_W)))
      {
        if ((y > note_Y) && (y < (note_Y + note_H)))
        {
          playNote(keys[i].freq);
        }
      }
    }
  } 
}

void playNote(int f)
{
  {
    tone(buzzerPin, f, duration);
    delay(del);
  }
}









