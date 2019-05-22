int prevColor = 0;
void colorPulse(){ 
  int increment=2000;
  if (prevColor < (65536-increment)){
    prevColor = prevColor+increment;
  } else {
    prevColor = 1;
  }
   
 // Serial.println(prevColor); 

  int maxBright = 100;
  for (int i = 10; i < maxBright; i++) {
    if (handleButtonClick()) {
        return;
      }
    strip.clear();
    strip.setBrightness(i);
    
    for (int j = 0; j < N_PIXELS; j++) { 
      strip.setPixelColor(j, prevColor);
    }
    strip.show();
    delay(10);
  }

  for (int i = 100; i > 10; i--) {
    if (handleButtonClick()) {
        return;
      }
    strip.clear();
    strip.setBrightness(i);
    
    for (int j = 0; j < N_PIXELS; j++) { 
      strip.setPixelColor(j, prevColor);
    }
    strip.show();
    delay(10);
  }

  delay(500);
}
