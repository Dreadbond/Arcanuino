char val;
String latitude, longitude;

int count ;
int ledPin = 13;

void setup() {
pinMode(ledPin, OUTPUT);
Serial.begin(9600);
}

void loop() {

  if(Serial.available()) {val = Serial.read();}
    

  if (val == ":"){ ++count ;}

  switch(count) {
  case 1 :
    if ( val == '0' || val == '1' || val == '2' || val == '3' || val == '4' || val == '5' || val == '6' || val == '7' || val == '8' || val == '9' || val == '.' || val == '-') 
    {latitude += val; }
    break ;
  case 2 :
    if ( val == '0' || val == '1' || val == '2' || val == '3' || val == '4' || val == '5' || val == '6' || val == '7' || val == '8' || val == '9' || val == '.' || val == '-') 
    {latitude += val; }
    break ;
  }

  if () {count = 0;}

  Serial.println(val);




//delay(100);
}
