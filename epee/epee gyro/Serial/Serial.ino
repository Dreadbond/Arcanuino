/*
The sensor outputs provided by the library are the raw 16-bit values
obtained by concatenating the 8-bit high and low gyro data registers.
They can be converted to units of dps (degrees per second) using the
conversion factors specified in the datasheet for your particular
device and full scale setting (gain).
 
Example: An L3GD20H gives a gyro X axis reading of 345 with its
default full scale setting of +/- 245 dps. The So specification
in the L3GD20H datasheet (page 10) states a conversion factor of 8.75
mdps/LSB (least significant bit) at this FS setting, so the raw
reading of 345 corresponds to 345 * 8.75 = 3020 mdps = 3.02 dps.
*/

#include <Wire.h>
#include <L3G.h>

L3G gyro;

long x_data;
long y_data;
long z_data;

long arf;

bool flagHit = LOW;
long buff[20];
int i;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!gyro.init())
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }

  gyro.enableDefault();
}

void loop() {
  gyro.read();
/*
x_data = (int)gyro.g.x;
y_data = (int)gyro.g.y;
z_data = (int)gyro.g.z;*/

  //Serial.print("G ");
  //Serial.print("X: ");
  Serial.println(gyro.g.x);
  //Serial.print(" Y: ");
  Serial.println(gyro.g.y);
  //Serial.print(" Z: ");
  Serial.println(gyro.g.z);





if(gyro.g.z <= -10000) {flagHit = HIGH;}


    if (flagHit == HIGH && gyro.g.z > -10000) { 
  i++;
  //if(gyro.g.z < 0) {gyro.g.z = gyro.g.z * -1;}
  buff[i] = gyro.g.z;   }

if(i==19)  {
  flagHit=LOW; 
  i=0; 
  
  arf = buff[2] + buff[3] + buff[4] + buff[5] + buff[6] + buff[7] + buff[8] + buff[9] + buff[10] ; 
  arf = arf + buff[11] + buff[12] + buff[13] + buff[14] + buff[15] + buff[16] + buff[17] + buff[18] + buff[19];

  /*
  Serial.println(arf);
  
  Serial.println(" ");
  Serial.println(buff[1]);
  Serial.println(buff[2]);
  Serial.println(buff[3]);
  Serial.println(buff[4]);
  Serial.println(buff[5]);
  Serial.println(buff[6]);
  Serial.println(buff[7]);
  Serial.println(buff[8]);
  Serial.println(buff[9]);
  Serial.println(buff[10]);

  Serial.println(buff[11]);
  Serial.println(buff[12]);
  Serial.println(buff[13]);
  Serial.println(buff[14]);
  Serial.println(buff[15]);
  Serial.println(buff[16]);
  Serial.println(buff[17]);
  Serial.println(buff[18]);
  Serial.println(buff[19]);
  //Serial.println(buff[20]);
  Serial.println(" ");*/
  /*
  if(arf > 40000) {
    Serial.print("Coup : deg : ");
    Serial.println(arf);}
  if(arf <= 40000) {Serial.println("Rate !");}*/
  }  


  delay(20);
}
