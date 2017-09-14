void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("emmeteur");

pinMode(3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(3, HIGH);
delayMicroseconds(26);
digitalWrite(3, LOW);
delayMicroseconds(26);


}
