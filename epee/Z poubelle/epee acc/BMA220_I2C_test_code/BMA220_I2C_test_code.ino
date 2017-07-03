#include <Wire.h> 
byte Version[3];
int8_t x_data;
int8_t y_data;
int8_t z_data;
int arf;

bool flagHit = LOW;
int buff[20];
int i;

void setup() 
{ 
  Serial.begin(9600); 
  Wire.begin(); 
  Wire.beginTransmission(0x0A); // address of the accelerometer 
  // low pass filter, range settings 
  Wire.write(0x20); 
  Wire.write(0x05); 
  Wire.endTransmission();
  
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
   
   Serial.print("X=");   
   Serial.print(x_data);         // print the character
   Serial.print("  "); 
   Serial.print("Y=");   
   Serial.print(y_data);         // print the character
   Serial.print("  "); 
   Serial.print("Z=");  
   Serial.println(z_data);   
} 
 
void loop() 
{ 
  AccelerometerInit(); 
 
if(y_data > 0) {y_data = y_data * -1;}

if(y_data == -32) {flagHit = HIGH;}


    if (flagHit == HIGH && y_data > -32) { 
  i++;
buff[i] = y_data;   }

if(i==19)  {
  flagHit=LOW; 
  i=0; 
  arf = buff[1] + buff[2] + buff[3] + buff[4] + buff[5] + buff[6] + buff[7] + buff[8] + buff[9] + buff[10] + 
  buff[11] + buff[12] + buff[13] + buff[14] + buff[15] + buff[16] + buff[17] + buff[18] + buff[19] + buff[0] ;
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
  Serial.println(buff[20]);
  Serial.println(" ");*/
  if(arf > -230) {
    Serial.print("Coup : deg : ");
    Serial.println(arf);}
  if(arf <= -230) {Serial.println("Rate !");}
  }  

// -230 : limite

  
delay(20);
}
















