#include <Wire.h> //add arduino I2C library;
//list of all registers binary addresses;
byte WHO_AM_I           = 0B00001111;
byte CTRL_REG1          = 0B00100000;
byte CTRL_REG2          = 0B00100001;
byte CTRL_REG3          = 0B00100010;
byte CTRL_REG4          = 0B00100011;
byte CTRL_REG5          = 0B00100100;
byte REFERENCE          = 0B00100101;
byte OUT_TEMP           = 0B00100110;
byte STATUS_REG         = 0B00100111;
byte OUT_X_L            = 0B00101000;
byte OUT_X_H            = 0B00101001;
byte OUT_Y_L            = 0B00101010;
byte OUT_Y_H            = 0B00101011;
byte OUT_Z_L            = 0B00101100;
byte OUT_Z_H            = 0B00101101;
byte FIFO_CTRL_REG      = 0B00101110;
byte FIFO_SRC_REG       = 0B00101111;
byte INT1_CFG           = 0B00110000;
byte INT1_SRC           = 0B00110001;
byte INT1_TSH_XH        = 0B00110010;
byte INT1_TSH_XL        = 0B00110011;
byte INT1_TSH_YH        = 0B00110100;
byte INT1_TSH_YL        = 0B00110101;
byte INT1_TSH_ZH        = 0B00110110;
byte INT1_TSH_ZL        = 0B00110111;
byte INT1_DURATION      = 0B00111000;

byte Read    = 0B00000001;
byte Write   = 0B00000000;
byte Address   = 0B11010110;  //address of accelerometer/magnetometer with SAO connected to Vdd
//byte Address = 0B11010100;  //address of accelerometer/magnetometer with SAO connected to ground
/*
Wire.h sets these for us in arduino...that's analog pin 4 and 5
const int SDA = 4; 
const int SCL = 5; 
*/

void setup() {
  Serial.begin(9600);
  //start the Wire library;
  Wire.begin();
//activate accelerometer/magnetometer  
WriteRegister(CTRL_REG1,0B00001111);
delay(100);
}

void loop() {


byte Who = ReadRegister(WHO_AM_I);
byte X_L = ReadRegister(OUT_X_L);
byte X_H = ReadRegister(OUT_X_H);
byte Y_L = ReadRegister(OUT_Y_L);
byte Y_H = ReadRegister(OUT_Y_H);
byte Z_L = ReadRegister(OUT_Z_L);
byte Z_H = ReadRegister(OUT_Z_H);

int X_AXIs = X_H <<8 | X_L;
int Y_AXIs = Y_H <<8 | Y_L;
int Z_AXIs = Z_H <<8 | Z_L;

Serial.print("X-Axis: ");
Serial.println(X_AXIs, DEC);
Serial.print("Y-Axis: ");
Serial.println(Y_AXIs, DEC);
Serial.print("Z-Axis: ");
Serial.println(Z_AXIs, DEC);

Serial.print("X-Axis: ");
Serial.print((X_AXIs-70)*.00875, DEC);
Serial.println(" dps");
Serial.print("Y-Axis: ");
Serial.print((Y_AXIs+90)*.00875, DEC);
Serial.println(" dps");
Serial.print("Z-Axis: ");
Serial.print((Z_AXIs+57)*.00875, DEC);
Serial.println(" dps");

delay(500);
}

byte ReadRegister(int Register){
byte result = 0;
Wire.beginTransmission((Address | Write) >>1 ); //slave ID start talking
//ask for info in register
Wire.write(Register);
//complete the send
Wire.endTransmission(0);
//Request 1 byte

Wire.requestFrom((Address | Read) >>1 , 1);
//wait for info
while( Wire.available() == 0);
result = Wire.read();  
//get info
Wire.endTransmission();
return(result);  
}

void WriteRegister(byte Register, byte Value){
  Wire.beginTransmission((Address | Write) >>1 );
  Wire.write(Register);
  Wire.write(Value);
  Wire.endTransmission();
}
