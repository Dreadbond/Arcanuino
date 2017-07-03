#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <LIS3MDL.h>

LIS3MDL mag;

#define PIN 6 //pin number that you have connected your data pin to
#define PIXNUMBER 16 //number of neopixels you have connected

char report[80];
int angleActual;
int pointA;
int angleAmap;

int velo;
int oldvelo;
int poten;
int sens;
float bright ;
int led;
int col1 ;
int col1b ;
int col2 ;
int col2b ;
int col3 ;
int col3b ;
float disp;

/*
float xO = 0 ;
float yO = 0 ;*/

/*
float xA = -5 ;
float yA = -2 ;*/

long xO = -1.6572029 * 10000000 ; 
long yO = 48.0971294 * 10000000 ;

long xA = -2.398019 * 10000000 ; 
long yA = 47.925296 * 10000000 ;




Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXNUMBER, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options
uint32_t vert = strip.Color(0, 50, 50);//in (0, 0, 0) type in intesities for each color




int rien(int val){
  for(val = 0; val<255 ; val++) {
    delay(20);
  }
  static int i = -i ;
  return val;
}

float fade(int add) {
static int val = 0;
static int dir = 1;
val = val + dir*add;
if (val >100) {
  val = 100; 
  dir *= -1;
  }
if (val <0) {
  val = 0; 
  dir *= -1;
  }
  return val ;
}


void setup()
{
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  
  strip.begin();
  strip.show();//sets all pixels to off state
  
  Serial.begin(9600);
  Wire.begin();

  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);



  if (!mag.init())
  {
    Serial.println("Failed to detect and initialize magnetometer!");
    while (1);
  }

  mag.enableDefault();
}






void loop()


{
  strip.setPixelColor(angleActual, 0, 0, 0); //remise au noir de la Led (à changer)
  strip.setPixelColor(angleAmap, 0, 0, 0);

  mag.read();
    int i = mag.m.x;
    int t = mag.m.z;
    int u = mag.m.y;

i = map(i, -1430, 1330, -180, 180);
  t = map(t, 1100, 4000, -180, 180);
  double mygrad = atan2(-i, t)*180/3.1415927410;
  if (mygrad < 0)    mygrad = mygrad +360;
  angleActual = mygrad;

angleActual = map(angleActual, 0, 360, 0, 16);

 // snprintf(report, sizeof(report), "%6d %6d %6d",mag.m.x, mag.m.y, mag.m.z);


//////////////////////trouvage de tangente////////////////////////////////////////////////////
if (Serial.available()) {xA = Serial.read();}

long diffx = xA - xO ;
long diffy = yA - yO ;

float tangA = float(diffx) / float(diffy) ;
float atanA = atan(tangA);
float angleA = (atanA * 4068) / 71;
//if (pointA < 0)    pointA = pointA +360;


/*
double tangA = atan2(diffx, diffy)*180/3.1415927410;
if (tangA < 0)    tangA = tangA +360;*/


if (diffx >= 0 && diffy >= 0) {angleA = angleA ;}
if (diffx >= 0 && diffy <= 0) {angleA = -1 * angleA ; angleA = 180 - angleA;}
if (diffx <= 0 && diffy <= 0) {angleA = angleA + 180 ;}
if (diffx <= 0 && diffy >= 0) {angleA = -1 * angleA ; angleA = 360 - angleA;}

angleAmap = map(angleA, 0, 360, 15, 0);

angleAmap = angleAmap + angleActual;
if (angleAmap > 16 ) {angleAmap = angleAmap - 16;}
if (angleAmap < 0 ) {angleAmap = angleAmap + 16;}

/*
Serial.print(diffx);
Serial.print(" ");
Serial.print(diffy);
Serial.print(" ");
Serial.print(tangA);
Serial.print(" ");
Serial.print(atanA);
Serial.print(" ");
Serial.print(angleA);
Serial.print(" ");
Serial.println(angleAmap);*/
Serial.println(angleAmap);

//pointA = map(pointA, 0, 360, 15, 0);
//pointA = pointA + angleActual;

//strip.setPixelColor(0, 10, 0, 0);
strip.setPixelColor(angleActual, 30, 30, 30);
strip.setPixelColor(angleAmap, 0, 100, 30);

strip.setBrightness(70);
strip.show();//show the pixels / colors of them after every cycle of loop -- like a refresh state
delay(100);

}












