#include <Adafruit_NeoPixel.h>
#include <math.h>

#define N_PIXELS  180  // Number of pixels in strand
#define MIC_PIN   A0  // Microphone is attached to this analog pin
#define LED_PIN    6  // NeoPixel LED strand is connected to this pin
#define SAMPLE_WINDOW   10  // Sample window for average level
int PEAK_HANG = 24; //Time of pause before peak dot falls
int PEAK_FALL = 4; //Rate of falling peak dot
int INPUT_FLOOR = 10; //Lower range of analogRead input
int INPUT_CEILING = 1000; //Max range of analogRead input, the lower the value the more sensitive (1023 = max)
byte peak = 16;      // Peak level of column; used for falling dots
unsigned int sample;
byte dotCount = 0;  //Frame counter for peak dot
byte dotHangCount = 0; //Frame counter for holding peak dot

// BOTTOM_UP VU CODE
#define DC_OFFSET  0  // DC offset in mic signal - if unusure, leave 0
#define NOISE     20  // Noise/hum/interference in mic signal
#define SAMPLES   40  // Length of buffer for dynamic level adjustment
#define TOP       (N_PIXELS + 2) // Allow dot to go slightly off scale

byte volCount  = 0;      // Frame counter for storing past volume data

int
vol[SAMPLES],       // Collection of prior volume samples
    lvl       = 20,      // Current "dampened" audio level
    minLvlAvg = 0,      // For dynamic adjustment of graph low & high
    maxLvlAvg = 512;
// END BOTTOM_UP CODE


int currentCase = 999;
int buttonVal = 2;
    
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // This is only needed on 5V Arduinos (Uno, Leonardo, etc.).
  // Connect 3.3V to mic AND TO AREF ON ARDUINO and enable this
  // line.  Audio samples are 'cleaner' at 3.3V.
  // COMMENT OUT THIS LINE FOR 3.3V ARDUINOS (FLORA, ETC.):
  //analogReference(EXTERNAL);
  memset(vol, 0, sizeof(vol));
  strip.begin();
  strip.setBrightness(100);

  Serial.begin(9600); 
}

int randSpeed=0;
int randPause=0;







 
void loop() {

  handleButtonClick();


  switch (buttonVal) {
    case 0 :
      currentCase = 0;
      // %%%%%%%%%%%%%%%%%%%%%%%% COLOR PATERNS CODE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      Serial.println("COLOR PATTERNS!!!");
 
      randSpeed = random(0,5); 
      randPause = random(0,4000);
 
      colorWipe(strip.Color(255, random(0,255), random(0,255)), randSpeed); // Red
      colorWipe(strip.Color(random(0,255), 255, random(0,255)), randSpeed); // Green
      colorWipe(strip.Color(random(0,255), random(0,255), 255), randSpeed); // Blue
      theaterChase(strip.Color(random(0,255), random(0,255), random(0,255)), 50); // White, half brightness
      
      quickPaint(strip.Color(0, 0, 0)); // clear
      delay(randPause);
      break; 
    case 1 :
      currentCase = 1;
      theaterChase(strip.Color(127, 127, 127), 50); // White, half brightness
      break;
    case 2 : 
      currentCase = 2;
      centerBounce();
      //theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
      break;
    case 3 :
      currentCase = 3;
      Serial.println("COLOR PULSE!!!");
      colorPulse();
      break;
    case 4 :
      currentCase = 4;
      rainbow(10);
      break;
    case 5 :
      currentCase = 5;
      theaterChaseRainbow(50);
      break;
    case 6 :
      // %%%%%%%%%%%%%%%%%%%%%%%% VU_METER CENTRE CODE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      Serial.println("VU CENTRE CODE!!!");
      if(currentCase != 6){
        PEAK_HANG = 24; //Time of pause before peak dot falls
        PEAK_FALL = 4; //Rate of falling peak dot
        INPUT_FLOOR = 10; //Lower range of analogRead input
        INPUT_CEILING = 1000; //Max range of analogRead input, the lower the value the more sensitive (1023 = max)
      }
      currentCase = 6;
      
      vuCentre(); 
      break;
    case 7 :
      // %%%%%%%%%%%%%%%%%%%%%%%% VU_METER BOTTOM_UP CODE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      Serial.println("VU BOTTOM_UP CODE!!!");
      if(currentCase != 7){
        PEAK_FALL = 60;
        peak      = 0,      // Used for falling dot
        dotCount  = 0,      // Frame counter for delaying dot-falling speed
        volCount  = 0;      // Frame counter for storing past volume data
        vol[SAMPLES],       // Collection of prior volume samples
        lvl       = 20,      // Current "dampened" audio level
        minLvlAvg = 0,      // For dynamic adjustment of graph low & high
        maxLvlAvg = 512;
      } 
      currentCase = 7;
       
      vuBottomUp();
      break;
  }
}

int randomColor(){
  return random(0,255);
}

bool handleButtonClick() {
  if (digitalRead(12) == HIGH) {
    int prevVal = buttonVal;

    buttonVal++;
    if (buttonVal > 7) { 
      buttonVal = 0;
    }

    if (prevVal != buttonVal) {
      delay(500);
      return true;
    }

    return false;
  } 
}
