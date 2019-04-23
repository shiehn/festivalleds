void vuCentre() {
  unsigned long startMillis = millis(); // Start of sample window
      float peakToPeak = 0; // peak-to-peak level
  
      unsigned int signalMax = 0;
      unsigned int signalMin = 1023;
      unsigned int c, y;
  
      // collect data for length of sample window (in mS)
      while (millis() - startMillis < SAMPLE_WINDOW) {
          sample = analogRead(MIC_PIN);
          if (sample < 1024) // toss out spurious readings
          {
              if (sample > signalMax) {
                  signalMax = sample; // save just the max levels
              } else if (sample < signalMin) {
                  signalMin = sample; // save just the min levels
              }
          }
      }
      peakToPeak = signalMax - signalMin; // max - min = peak-peak amplitude
  
      // Serial.println(peakToPeak);
  
      /*
        //Fill the strip with rainbow gradient
        for (int i = 0; i <= strip.numPixels() - 1; i++) {
          strip.setPixelColor(i, Wheel(map(i, 0, strip.numPixels() - 1, 30, 150)));
        }
      */
  
      //Fill the strip with rainbow gradient
      for (int i = 0; i <= strip.numPixels() / 2; i++) {
          // left - works
          strip.setPixelColor(strip.numPixels() / 2 - i, Wheel(map(i, 0, strip.numPixels() / 2, 30, 150)));
          // right - maybe fixme
          strip.setPixelColor(i + strip.numPixels() / 2, Wheel(map(i, 0, strip.numPixels() / 2, 30, 150)));
      }
  
      //Scale the input logarithmically instead of linearly
      c = fscale(INPUT_FLOOR, INPUT_CEILING, strip.numPixels() / 2, 0, peakToPeak, 2);
  
      if (c < peak) {
          peak = c; // Keep dot on top
          dotHangCount = 0; // make the dot hang before falling
      }
      if (c <= strip.numPixels() / 2) { // Fill partial column with off pixels
          // left - okay
          drawLine(0, c, strip.Color(0, 0, 0));
          // right - maybe fixed?
          drawLine(strip.numPixels() - c, strip.numPixels(), strip.Color(0, 0, 0));
      }
  
      // Set the peak dot to match the rainbow gradient
      y = strip.numPixels() / 2 - peak;
  
      // left - okay
      strip.setPixelColor(strip.numPixels() / 2 - (y - 1), Wheel(map(y, 0, strip.numPixels() / 2, 30, 150)));
      // right - maybe fixme
      strip.setPixelColor(strip.numPixels() / 2 + y - 1, Wheel(map(y, 0, strip.numPixels() / 2, 30, 150)));
  
      strip.show();
  
      // Frame based peak dot animation
      if (dotHangCount > PEAK_HANG) { //Peak pause length
          if (++dotCount >= PEAK_FALL) { //Fall rate
              peak++;
              dotCount = 0;
          }
      } else {
          dotHangCount++;
      }
}
