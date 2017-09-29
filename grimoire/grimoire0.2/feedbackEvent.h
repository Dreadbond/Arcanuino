void eventFeedback() {
Serial.println("làààààà");

if (fire) {
  for (int i=0 ; i<PIX ; i++) {
    page.setPixelColor(i, 255, 200, 0);
    page.show();
    
  }
}





}
