const int marge = 3;
const int cible = 100;
int x = 80 ;

void setup() {
delay(3000);
}

void loop() {

while(x<121) {
  x++;
  Serial.println(x);
  if ( x <= cible + marge && x >= cible - marge ) {Serial.println("J'ai !");}

  
  delay(50);
}

}
