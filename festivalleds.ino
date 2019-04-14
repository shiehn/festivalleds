// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define N_PIXELS  150 // Number of pixels in strand
#define MIC_PIN   A0  // Microphone is attached to this analog pin
#define LED_PIN    6  // NeoPixel LED strand is connected to this pin
#define DC_OFFSET  0  // DC offset in mic signal - if unusure, leave 0
#define NOISE     20  // Noise/hum/interference in mic signal
#define SAMPLES   40  // Length of buffer for dynamic level adjustment
#define TOP       (N_PIXELS + 2) // Allow dot to go slightly off scale
#define PEAK_FALL 60  // Rate of peak falling dot

byte
peak      = 0,      // Used for falling dot
dotCount  = 0,      // Frame counter for delaying dot-falling speed
volCount  = 0;      // Frame counter for storing past volume data
int
vol[SAMPLES],       // Collection of prior volume samples
    lvl       = 20,      // Current "dampened" audio level
    minLvlAvg = 0,      // For dynamic adjustment of graph low & high
    maxLvlAvg = 512,
    buttonVal = 0;
Adafruit_NeoPixel
strip = Adafruit_NeoPixel(N_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // This is only needed on 5V Arduinos (Uno, Leonardo, etc.).
  // Connect 3.3V to mic AND TO AREF ON ARDUINO and enable this
  // line.  Audio samples are 'cleaner' at 3.3V.
  // COMMENT OUT THIS LINE FOR 3.3V ARDUINOS (FLORA, ETC.):
  //analogReference(EXTERNAL);

  memset(vol, 0, sizeof(vol));
  strip.begin();
  strip.setBrightness(50);

  Serial.begin(9600);
}


void loop() {

  handleButtonClick();

  switch (buttonVal) {
    case 0 :
      // %%%%%%%%%%%%%%%%%%%%%%%% COLOR PATERNS CODE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      Serial.println("COLOR PATTERNS!!!");
      colorWipe(strip.Color(255,   0,   0), 50); // Red
      break;
    case 1 :
      colorWipe(strip.Color(  0, 255,   0), 50); // Green
      break;
    case 2 :
      colorWipe(strip.Color(  0,   0, 255), 50); // Blue
      break;
    case 3 :
      theaterChase(strip.Color(127, 127, 127), 50); // White, half brightness
      break;
    case 4 :
      theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
      break;
    case 5 :
      theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness
      break;
    case 6 :
      rainbow(10);
      break;
    case 7 :
      theaterChaseRainbow(50);
      break;
    case 8 :
      // %%%%%%%%%%%%%%%%%%%%%%%% VU_METER CODE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      Serial.println("VU CODE!!!");

      uint8_t  i;
      uint16_t minLvl, maxLvl;
      int      n, height;

      n   = analogRead(MIC_PIN);            // Raw reading from mic
      n   = abs(n - 512 - DC_OFFSET);       // Center on zero
      n   = (n <= NOISE) ? 0 : (n - NOISE); // Remove noise/hum
      lvl = ((lvl * 7) + n) >> 3;           // "Dampened" reading (else looks twitchy)

      // Calculate bar height based on dynamic min/max levels (fixed point):
      height = TOP * (lvl - minLvlAvg) / (long)(maxLvlAvg - minLvlAvg);

      if (height < 0L) {
        height = 0;      // Clip output
      } else if (height > TOP) {
        height = TOP;
      }

      if (height > peak) {
        peak   = height; // Keep 'peak' dot at top
      }

      // Color pixels based on rainbow gradient
      for (i = 0; i < N_PIXELS; i++) {
        if (i >= height)               {
          strip.setPixelColor(i,   0,   0, 0);
        } else {
          strip.setPixelColor(i, Wheel(map(i, 0, strip.numPixels() - 1, 30, 150)));
        }
      }
      // Draw peak dot
      if (peak > 0 && peak <= N_PIXELS - 1) {
        strip.setPixelColor(peak, Wheel(map(peak, 0, strip.numPixels() - 1, 30, 150)));
      }

      strip.show(); // Update strip

      // Every few frames, make the peak pixel drop by 1:

      if (++dotCount >= PEAK_FALL) { //fall rate
        if (peak > 0) {
          peak--;
        }
        dotCount = 0;
      }

      vol[volCount] = n;                      // Save sample for dynamic leveling
      if (++volCount >= SAMPLES) {
        volCount = 0; // Advance/rollover sample counter
      }

      // Get volume range of prior frames
      minLvl = maxLvl = vol[0];
      for (i = 1; i < SAMPLES; i++) {
        if (vol[i] < minLvl) {
          minLvl = vol[i];
        } else if (vol[i] > maxLvl) {
          maxLvl = vol[i];
        }
      }
      // minLvl and maxLvl indicate the volume range over prior frames, used
      // for vertically scaling the output graph (so it looks interesting
      // regardless of volume level).  If they're too close together though
      // (e.g. at very low volume levels) the graph becomes super coarse
      // and 'jumpy'...so keep some minimum distance between them (this
      // also lets the graph go to zero when no sound is playing):
      if ((maxLvl - minLvl) < TOP) {
        maxLvl = minLvl + TOP;
      }
      minLvlAvg = (minLvlAvg * 63 + minLvl) >> 6; // Dampen min/max levels
      maxLvlAvg = (maxLvlAvg * 63 + maxLvl) >> 6; // (fake rolling average)
      break;
  }
}

bool handleButtonClick() {
  if (digitalRead(12) == HIGH) {
    int prevVal = buttonVal;

    buttonVal++;
    if (buttonVal > 9) { 
      buttonVal = 0;
    }

    if (prevVal != buttonVal) {
      delay(500);
      return true;
    }

    return false;
  } 
}
