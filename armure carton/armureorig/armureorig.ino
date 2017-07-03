const int ledPin = 13;      // led connected to digital pin 13
const int knockSensor = A3; // the piezo is connected to analog pin 0
const int threshold = 17;  // threshold value to decide when the detected sound is a knock or not
int knockCool = 40 ;

bool knockFlag = HIGH ;

unsigned long temps ;
unsigned long knockGate ;
int puissance ;
int sensorReading = 0;
int OldSensorReading = 0;
int ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT); // declare the ledPin as as OUTPUT
  Serial.begin(9600);       // use the serial port
}

void loop() {
   temps  = millis() ;

   OldSensorReading = sensorReading;
   
   sensorReading = analogRead(knockSensor);
  
  if (sensorReading >= threshold && knockFlag == HIGH) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);

    
    knockFlag = LOW ;
    knockGate = temps + knockCool ;
   // puissance = sensorReading ;
  }

if (knockGate < temps) {knockFlag = HIGH ;}

if (sensorReading >= threshold && puissance < sensorReading ) {
  puissance = sensorReading;   
  }
  
if (knockFlag == HIGH) {
  if(puissance > 40) {Serial.println(puissance);}
  puissance = 0;}

//Serial.println(sensorReading);
 /* Serial.print(OldSensorReading);
    Serial.print(" ");
    Serial.print(sensorReading);
    Serial.print(" ");*/


}

