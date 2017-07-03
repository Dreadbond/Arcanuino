/*
 * http://appinventor.pevest.com/?p=718
BTArduino sketch By Edward Mitchell http://appinventor.pevest.com
Description:
Uses the JY-MCU Bluetooth module to enable an Arduino board to communicate over Bluetooth
wireless to an Android app written in MIT App Inventor 2, running on an Android device.

Buy the JY-MCU module here
(Amazon Prime) http://www.amazon.com/gp/product/B0093XAV4U/ref=as_li_tl?ie=UTF8&camp=1789&creative=390957&creativeASIN=B0093XAV4U&linkCode=as2&tag=commonsensevi-20&linkId=4L5VQJW7JJKBGCMU
(Amazon non Prime option) http://www.amazon.com/gp/product/B009DZQ4MG/ref=as_li_tl?ie=UTF8&camp=1789&creative=390957&creativeASIN=B009DZQ4MG&linkCode=as2&tag=commonsensevi-20&linkId=S6VEEZVTF4GBGYWC

Credit:
This Arduino code based very loosely on the original Arduino code for the JY-MCU Bluetooth module tutorial at
http://robotosh.blogspot.com/2012/07/arduino-jy-mcu-bluetooth.html

A tutorial for using this code with App Inventor 2, is available at the appinventor.pevest.com
web site. Please refer to the tutorial for information and source code for the Android side of this sketch.

Note - this sample code is intended only to show how the basic Bluetooth communications link may
be set up, and illustrates just one possible way of sending commands from the Android device
to the Arduino phone. The purpose of this code is as an introduction/tutorial and is not meant
to be used for any particular purpose. No warranties.
*/

// Constant Definitions
#define LEDPIN 8 // Pin on Arduino board to which status LED is connected
#define READ_RATE 100 // How often the serial link is read, in milliseconds
#define FLASH_RATE 100 // The on/off period in milliseconds, for the LED Flash status feedback

// Declarations
byte cmd; // Stores the next byte of incoming data, which is a "command" to do something
byte param; // Stores the 2nd byte, which is the command parameter

// Initialization
void setup() {

pinMode(LEDPIN, OUTPUT); // pin 48 (on-board LED) as OUTPUT
digitalWrite(LEDPIN, LOW);
Serial.begin(9600); // start serial communication at 9600bps
}

// Arduino Execution Loop
void loop() {

if ( Serial.available() ) // if data is available to read
{
cmd = Serial.read(); // read it and store it in 'cmd'
// Data format is byte 1 = command, byte 2 = parameter
};

switch ( cmd ) {
case 1:
// First byte contains a generic "command" byte. We arbitrarily defined '1' as the command to then check the 2nd parameter byte
// User can additional commands by adding case 2, 3, 4, etc
{
// read the parameter byte
param = Serial.read();
switch (param)
{
case 1:
// Android device requests the Arduino to send some data back to Android
flashLED(1);
if (Serial)
{
// Send back 2 bytes with a value of 1, 2
Serial.write(1);
Serial.write(2);
};
break;

case 2:
// Turn on status LED
flashLED(2);
digitalWrite(LEDPIN, HIGH );
break;

case 3:
// Turn off status LED
flashLED(3);
digitalWrite(LEDPIN, LOW);
break;

case 4:
// Demonstrate flashing the LED 4 times
flashLED(4);
break;

case 5:
// Demonstrate flashing the LED 5 times
// Could add code here to control a servo via PWM outputs
flashLED(5);
break;

default: break; // do nothing
} // switch (param)
} // switch (cmd) case 1
default: break; // do nothing
} // switch (cmd)

delay(READ_RATE); // wait 100ms for next reading
}

// Support routine
void flashLED (int n) {
// Flash the LED n times, to provide an on board status indicator
for (int i=1; i<=n; i++) {
digitalWrite (LEDPIN, HIGH);
delay (FLASH_RATE);
digitalWrite (LEDPIN, LOW);
delay(FLASH_RATE);
};
return;
}
