void setup() {
  pinMode(A0, INPUT);
Serial.begin(9600);
}

void loop() {
int qsd = analogRead(A0);
Serial.println(qsd);
delay(100);
}
