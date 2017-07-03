void setup() {
Serial.begin(9600);
}

void loop() {
int sensorValue0 = analogRead(0);
int serialValue0 = sensorValue0 / 4;
Serial.write(serialValue0);
delay(1);

//deuxième sensor
int sensorValue1 = analogRead(1);
int serialValue1 = sensorValue1 / 4;
Serial.write(serialValue1);
delay(1);
}
