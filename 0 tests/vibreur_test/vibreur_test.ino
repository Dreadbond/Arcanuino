unsigned long timeTag ;
int intens = 70;
int message ;

void setup() {
Serial.begin(9600);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
Serial.println("Vibreur test");
}

void loop() {

if (Serial.available() >0) {message = Serial.read(); Serial.println(message);}

//if (intens > 255) {intens = 70;}

analogWrite(5, message);
analogWrite(6, message);



//intens++;
//delay(100);
}
