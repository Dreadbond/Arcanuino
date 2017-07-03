/*
The sensor outputs provided by the library are the raw 16-bit values
obtained by concatenating the 8-bit high and low magnetometer data registers.
They can be converted to units of gauss using the
conversion factors specified in the datasheet for your particular
device and full scale setting (gain).

Example: An LIS3MDL gives a magnetometer X axis reading of 1292 with its
default full scale setting of +/- 4 gauss. The GN specification
in the LIS3MDL datasheet (page 8) states a conversion factor of 6842
LSB/gauss (where LSB means least significant bit) at this FS setting, so the raw
reading of 1292 corresponds to 1292 / 6842 = 0.1888 gauss.
*/

#include <Wire.h>
#include <LIS3MDL.h>

LIS3MDL mag;

char report[80];

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  if (!mag.init())
  {
    Serial.println("Failed to detect and initialize magnetometer!");
    while (1);
  }

  mag.enableDefault();
}

void loop()
{
  mag.read();
    int i = mag.m.x + 3000;
    int t = mag.m.y + 3000;
    int u = mag.m.z + 3000;
    int s = i + t - 2000 ;

i = map(i, 1960, 2151, -180, 180);
  t = map(t, 1939, 2131, -180, 180);
  double mygrad = atan2(-i, t)*180/3.1415927410;
  if (mygrad < 0)    mygrad = mygrad +360;
  int angleActual = mygrad;


 // snprintf(report, sizeof(report), "%6d %6d %6d",mag.m.x, mag.m.y, mag.m.z);
/*
Serial.print(mygrad);
Serial.print(" ");*/
Serial.println(angleActual);/*
Serial.print(" ");
Serial.println(s);*/

  delay(100);
}
