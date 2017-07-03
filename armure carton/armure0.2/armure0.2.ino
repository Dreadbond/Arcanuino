const int ledPin = 13;      // led connected to digital pin 13
const int SensPlas = A0; // the piezo is connected to analog pin 0
const int SensAbG = A1;
const int SensAbD = A2;
const int SensSw = A3;
const int thresPlas = 40;  // threshold value to decide when the detected sound is a knock or not
const int thresAbG = 40;
const int thresAbD = 40;
const int thresSw = 40;

int CoolPlas = 40 ;
int CoolAbG = 40 ;
int CoolAbD = 40 ;
int CoolSw = 50 ;

bool FlagPlas = HIGH ;
bool FlagAbG = HIGH ;
bool FlagAbD = HIGH ;
bool FlagSw = HIGH ;

unsigned long temps ;

unsigned long GatePlas ;
unsigned long GateAbG ;
unsigned long GateAbD ;
unsigned long GateSw ;

int puissPlas ;
int puissAbG ;
int puissAbD ;
int puissSw ;

int sensorReadPlas = 0;
int sensorReadAbG = 0;
int sensorReadAbD = 0;
int sensorReadSw = 0;

int OldsensorReadPlas = 0;
int OldsensorReadAbG = 0;
int OldsensorReadAbD = 0;
int OldsensorReadSw = 0;

int ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT); // declare the ledPin as as OUTPUT
  Serial.begin(9600);       // use the serial port
}



void loop() {
  temps  = millis() ;


  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////Arme///A3///////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////

  /*
      OldsensorReadSw = sensorReadSw;

    if(analogRead(SensSw) != 0) {sensorReadSw = analogRead(SensSw);}


    if (sensorReadSw >= thresSw && FlagSw == HIGH) {
      Serial.print("Epee ");
      Serial.println(sensorReadSw);
      FlagSw = LOW ;
      GateSw = temps + CoolSw ;
    }

    if (GateSw < temps) {FlagSw = HIGH ;}
  */

  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////Torse/////A0////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////

  OldsensorReadPlas = sensorReadPlas;

  if (analogRead(SensPlas) != 0 ) {
    sensorReadPlas = analogRead(SensPlas);
  }


  if (sensorReadPlas >= thresPlas && FlagPlas == HIGH) {
    // Serial.print("Torse ");
    Serial.println(sensorReadPlas);
    FlagPlas = LOW ;
    GatePlas = temps + CoolPlas ;
  }

  if (GatePlas < temps) {
    FlagPlas = HIGH ;
  }


  /*
     OldsensorReadPlas = sensorReadPlas;

     sensorReadPlas = analogRead(SensPlas);

    if (sensorReadPlas >= thresPlas && FlagPlas == HIGH) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState);


      FlagPlas = LOW ;
      GatePlas = temps + CoolPlas ;
     // puissPlas = sensorReadPlas ;
    }

    if (GatePlas < temps) {FlagPlas = HIGH ;}

    if (sensorReadPlas >= thresPlas && puissPlas < sensorReadPlas ) {
    puissPlas = sensorReadPlas;
    }

    if (FlagPlas == HIGH && FlagSw == HIGH) {
    if(puissPlas > 40) {

     // Serial.print("Torse ");
      Serial.println(sensorReadPlas);

    }
    puissPlas = 0;}*/



  ////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////Avant-bras Gauche//A1////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////

  OldsensorReadAbG = sensorReadAbG;

  if (analogRead(SensAbG) != 0) {
    sensorReadAbG = analogRead(SensAbG);
  }


  if (sensorReadAbG >= thresAbG && FlagAbG == HIGH) {
    // Serial.print("Avant-bras Gauche ");
    Serial.println(sensorReadAbG);
    FlagAbG = LOW ;
    GateAbG = temps + CoolAbG ;
  }

  if (GateAbG < temps) {
    FlagAbG = HIGH ;
  }

  /*
     OldsensorReadAbG = sensorReadAbG;

     sensorReadAbG = analogRead(SensAbG);

    if (sensorReadAbG >= thresAbG && FlagAbG == HIGH) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState);


      FlagAbG = LOW ;
      GateAbG = temps + CoolAbG ;
     // puissAbG = sensorReadAbG ;
    }

    if (GateAbG < temps) {FlagAbG = HIGH ;}

    if (sensorReadAbG >= thresAbG && puissAbG < sensorReadAbG ) {
    puissAbG = sensorReadAbG;
    }

    if (FlagAbG == HIGH && FlagSw == HIGH) {
    if(puissAbG > 40) {
     // Serial.print("Avant-bras gauche ");
      Serial.println(sensorReadAbG);

    }
    puissAbG = 0;}*/


  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////Avant-bras droit//A2///////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////

  OldsensorReadAbD = sensorReadAbD;

  if (analogRead(SensAbD) != 0) {
    sensorReadAbD = analogRead(SensAbD);
  }


  if (sensorReadAbD >= thresAbD && FlagAbD == HIGH) {
    //  Serial.print("Avant-bras droit ");
    Serial.println(sensorReadAbD);
    FlagAbD = LOW ;
    GateAbD = temps + CoolAbD ;
  }

  if (GateAbD < temps) {
    FlagAbD = HIGH ;
  }

  /*
     OldsensorReadAbD = sensorReadAbD;

     sensorReadAbD = analogRead(SensAbD);

    if (sensorReadAbD >= thresAbD && FlagAbD == HIGH) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState);


      FlagAbD = LOW ;
      GateAbD = temps + CoolAbD ;
     // puissAbD = sensorReadAbD ;
    }

    if (GateAbD < temps) {FlagAbD = HIGH ;}

    if (sensorReadAbD >= thresAbD && puissAbD < sensorReadAbD ) {
    puissAbD = sensorReadAbD;
    }

    if (FlagAbD == HIGH && FlagSw == HIGH) {
    if(puissAbD > 40) {
    //   Serial.print("Avant-bras droit ");
      Serial.println(sensorReadAbD);
      }
    puissAbD = 0;}*/



  //Serial.println(sensorReadPlas);
  /* Serial.print(OldsensorReadPlas);
     Serial.print(" ");
     Serial.print(sensorReadPlas);
     Serial.print(" ");*/


}

