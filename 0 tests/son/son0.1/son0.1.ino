#include <Tune.h>
#include <SdFat.h>
Tune player;

bool b1;
bool b2;
bool b3;
bool b4;
bool b5;
bool b6;
bool b7;
bool b8;

void setup() {

pinMode(3, INPUT_PULLUP);
pinMode(4, INPUT_PULLUP);
pinMode(5, INPUT_PULLUP);
pinMode(6, INPUT_PULLUP);
pinMode(7, INPUT_PULLUP);
pinMode(8, INPUT_PULLUP);
pinMode(9, INPUT_PULLUP);
pinMode(10, INPUT_PULLUP);
  
  Serial.begin(9600);
  player.begin();
  player.setVolume(50);
  delay(10);
  player.setVolume(100);
  delay(10);
  player.setVolume(150);
  delay(10);
  player.setVolume(200);
  delay(10);

}




void loop() {


b1 = digitalRead(3);
b2 = digitalRead(4);
b3 = digitalRead(5);
b4 = digitalRead(6);
b5 = digitalRead(7);
b6 = digitalRead(8);
b7 = digitalRead(9);
b8 = digitalRead(10);

/*
Serial.print(b1);
Serial.print(" ");
Serial.print(b2);
Serial.print(" ");
Serial.print(b3);
Serial.print(" ");
Serial.print(b4);
Serial.print(" ");
Serial.print(b5);
Serial.print(" ");
Serial.print(b6);
Serial.print(" ");
Serial.print(b7);
Serial.print(" ");
Serial.print(b8);
Serial.println(" ");*/

  delay(10);
if (b1 == LOW){
player.play("liming avant.mp3"); 
  Serial.println("liming avant.mp3");}
if (b2 == LOW){
  Serial.println("liming av-droite.mp3");
player.play("liming av-droite.mp3"); }
if (b3 == LOW){
  Serial.println("liming droite.mp3");
player.play("liming droite.mp3"); }
if (b4 == LOW){
  Serial.println("liming ar-droite.mp3");
player.play("liming ar-droite.mp3"); }
delay(10);
if (b5 == LOW){
  Serial.println("liming arriere.mp3");
player.play("liming arriere.mp3"); }
if (b6 == LOW){
  Serial.println("liming ar-gauche.mp3");
player.play("liming ar-gauche.mp3"); }
if (b7 == LOW){
  Serial.println("liming gauche.mp3");
player.play("liming gauche.mp3");} 
if (b8 == LOW){
  Serial.println("liming av-gauche.mp3");
player.play("liming av-gauche.mp3"); }




}
