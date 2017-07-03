#include <Wire.h> 
byte Version[3];
int8_t x_data;
int8_t y_data;
int8_t z_data;
byte range=0x00;
float divi=16;
float x,y,z;
int oldx, oldy, oldz ;
int diffx, diffy, diffz;
int mainx, mainy, mainz;



void setup() 
{ 
  Serial.begin(9600); 
  Wire.begin(); 
  Wire.beginTransmission(0x0A); // address of the accelerometer 
  // range settings
  Wire.write(0x22); //register address
  Wire.write(range); //can be set at"0x00""0x01""0x02""0x03", refer to Datashhet on wiki
  // low pass filter  
  Wire.write(0x20); //register address
  Wire.write(0x05); //can be set at"0x05""0x04"......"0x01""0x00", refer to Datashhet on wiki
  Wire.endTransmission();
  digitalWrite(3, OUTPUT);
  digitalWrite(5, OUTPUT);
  digitalWrite(9, OUTPUT);
} 
   
void AccelerometerInit() 
{ 
  Wire.beginTransmission(0x0A); // address of the accelerometer 
  // reset the accelerometer 
  Wire.write(0x04); // Y data
  Wire.endTransmission(); 
  Wire.requestFrom(0x0A,1);    // request 6 bytes from slave device #2
  while(Wire.available())    // slave may send less than requested
  { 
    Version[0] = Wire.read(); // receive a byte as characte
  }  
  x_data=(int8_t)Version[0]>>2;
   
  Wire.beginTransmission(0x0A); // address of the accelerometer 
  // reset the accelerometer 
  Wire.write(0x06); // Y data
  Wire.endTransmission(); 
  Wire.requestFrom(0x0A,1);    // request 6 bytes from slave device #2
  while(Wire.available())    // slave may send less than requested
  { 
    Version[1] = Wire.read(); // receive a byte as characte
  }  
  y_data=(int8_t)Version[1]>>2;
    
  Wire.beginTransmission(0x0A); // address of the accelerometer 
  // reset the accelerometer 
  Wire.write(0x08); // Y data
  Wire.endTransmission(); 
  Wire.requestFrom(0x0A,1);    // request 6 bytes from slave device #2
   while(Wire.available())    // slave may send less than requested
  { 
    Version[2] = Wire.read(); // receive a byte as characte
  }  
   z_data=(int8_t)Version[2]>>2; 
    
   x=(float)x_data/divi; 
   y=(float)y_data/divi;
   z=(float)z_data/divi;
  /* Serial.print("X=");   
   Serial.print(x);         // print the character
   Serial.print("  "); 
   Serial.print("Y=");   
   Serial.print(y);         // print the character
   Serial.print("  "); 
   Serial.print("Z=");           // print the character
   Serial.println(z);   */
} 
   
void loop() {
oldx = mainx;
oldy = mainy;
oldz = mainz;
 
  switch(range)  //change the data dealing method based on the range u've set
  {
  case 0x00:divi=16;  break;
  case 0x01:divi=8;  break;
  case 0x02:divi=4;  break;
  case 0x03:divi=2;  break;
  default: Serial.println("range setting is Wrong,range:from 0to 3.Please check!");while(1); 
  }
  AccelerometerInit(); 

mainx = x*100;
mainy = y*100;
mainz = z*100;

mainx = mainx;
mainy = mainy;
mainz = mainz;

diffx = oldx - mainx;
diffy = oldy - mainy;
diffz = oldz - mainz; 

     Serial.print(diffx);   
     Serial.print(" ");
     Serial.print(diffy);   
     Serial.print(" ");
     Serial.println(diffz);   

mainx = mainx;
mainy = mainy;
mainz = mainz;

  constrain(mainx, 0, 255);
  constrain(mainy, 0, 255);
  constrain(mainz, 0, 255);
     
  analogWrite(3, mainx);
  analogWrite(5, mainy);
  analogWrite(9, mainz);



delay(100);
  
}
