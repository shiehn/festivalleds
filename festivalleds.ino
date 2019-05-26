#include <Adafruit_NeoPixel.h> 
#include <math.h>

#define N_PIXELS  180  // Number of pixels in strand
#define MIC_PIN   A0  // Microphone is attached to this analog pin
#define LED_PIN    2  // NeoPixel LED strand is                 connected to this pin
#define SAMPLE_WINDOW   10  // Sample window for average level
int PEAK_HANG = 24; //Time of pause before peak dot falls
int PEAK_FALL = 4; //Rate of falling peak dot
int INPUT_FLOOR = 10; //Lower range of analogRead input
int INPUT_CEILING = 500; //Max range of analogRead input, the lower the value the more sensitive (1023 = max)
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
int buttonVal = 0;

int DEBUG=0;
    
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
 
void setup() {
  // This is only needed on 5V Arduinos (Uno, Leonardo, etc.).
  // Connect 3.3V to mic AND TO AREF ON ARDUINO and enable this
  // line.  Audio samples are 'cleaner' at 3.3V.
  // COMMENT OUT THIS LINE FOR 3.3V ARDUINOS (FLORA, ETC.):
  //analogReference(EXTERNAL);

  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  pinMode(12,INPUT);
  pinMode(13,INPUT);

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
      if(DEBUG){
        Serial.println("PATTERN: 0");
      }
      if(currentCase != 6){
        PEAK_HANG = 24; //Time of pause before peak dot falls
        PEAK_FALL = 4; //Rate of falling peak dot
        INPUT_FLOOR = 10; //Lower range of analogRead input
        INPUT_CEILING = 1000; //Max range of analogRead input, the lower the value the more sensitive (1023 = max)
      }
      currentCase = 6;
      
      //vuCentre(); 


      disperse();


      
      break;
    case 1 :
      if(DEBUG){
        Serial.println("PATTERN: 1");
      }
      currentCase = 1;
      handleButtonClick(); 
      
      candy_cane(); 
      break;
    case 2 : 
      if(DEBUG){
        Serial.println("PATTERN: 2");
      }
      currentCase = 2;
      centerBounce();
      //theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
      break;
    case 3 :
      if(DEBUG){
        Serial.println("PATTERN: 3");
      }
      currentCase = 3; 
      colorPulse();
      break;
    case 4 :
      if(DEBUG){
        Serial.println("PATTERN: 4");
      }
      currentCase = 4;
      rainbow(10);
      break;
    case 5 :
      if(DEBUG){
        Serial.println("PATTERN: 5");
      }
      currentCase = 5;
      theaterChaseRainbow(50);
      break;
    case 6 :
      if(DEBUG){
        Serial.println("PATTERN: 6");
      }
      currentCase = 0;
      // %%%%%%%%%%%%%%%%%%%%%%%% COLOR PATERNS CODE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      
      handleButtonClick();
 
      randSpeed = random(0,5); 
      randPause = random(0,4000);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
      colorWipe(strip.Color(255, random(0,255), random(0,255)), randSpeed); // Red
      colorWipe(strip.Color(random(0,255), 255, random(0,255)), randSpeed); // Green
      colorWipe(strip.Color(random(0,255), random(0,255), 255), randSpeed); // Blue
      theaterChase(strip.Color(random(0,255), random(0,255), random(0,255)), 50); // White, half brightness
      
      quickPaint(strip.Color(0, 0, 0)); // clear
      delay(randPause);
      break; 
    case 7 :
      if(DEBUG){
        Serial.println("PATTERN: 7");
      }
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
    case 8 :
      if(DEBUG){
        Serial.println("PATTERN: 8");
      }
      currentCase = 8;
      centreSplit();
      break;
  } 
}

int randomColor(){
  return random(0,255);
}

bool handleButtonClick() {  
  for (int x = 4; x < 14; x++) {
    if (digitalRead(x) == 0){
      int prevVal = buttonVal;
  
      buttonVal = x-4;
      if (prevVal != buttonVal) {
        Serial.println("BUTTON CLICKED");
        Serial.println(buttonVal);
        //delay(500);
        return true;
      } 
    }
  }

/*
  if (digitalRead(13) == 0) {
    int prevVal = buttonVal;

    buttonVal++;
    if (buttonVal > 8) { 
      buttonVal = 0;
    }

    if (prevVal != buttonVal) {
      Serial.println("BUTTON CLICK" + buttonVal);
      delay(500);
      return true;
    }

    return false;
  } 
*/
}

/*
bool handleButtonClick() { 
  if (digitalRead(13) == 0) {
    int prevVal = buttonVal;

    buttonVal++;
    if (buttonVal > 8) { 
      buttonVal = 0;
    }

    if (prevVal != buttonVal) {
      Serial.println("BUTTON CLICK" + buttonVal);
      delay(500);
      return true;
    }

    return false;
  } 
}
*/
