//Used to draw a line between two points of a given color
void drawLine(uint8_t from, uint8_t to, uint32_t c) {
    uint8_t fromTemp;
    if (from > to) {
        fromTemp = from;
        from = to;
        to = fromTemp;
    }
    for (int i = from; i <= to; i++) {
        strip.setPixelColor(i, c);
    }
}

float fscale(float originalMin, float originalMax, float newBegin, float newEnd, float inputValue, float curve) {

    float OriginalRange = 0;
    float NewRange = 0;
    float zeroRefCurVal = 0;
    float normalizedCurVal = 0;
    float rangedValue = 0;
    boolean invFlag = 0;

    // condition curve parameter
    // limit range

    if (curve > 10) curve = 10;
    if (curve < -10) curve = -10;

    curve = (curve * -.1); // - invert and scale - this seems more intuitive - postive numbers give more weight to high end on output
    curve = pow(10, curve); // convert linear scale into lograthimic exponent for other pow function

    /*
      Serial.println(curve * 100, DEC);   // multply by 100 to preserve resolution
      Serial.println();
    */

    // Check for out of range inputValues
    if (inputValue < originalMin) {
        inputValue = originalMin;
    }
    if (inputValue > originalMax) {
        inputValue = originalMax;
    }

    // Zero Refference the values
    OriginalRange = originalMax - originalMin;

    if (newEnd > newBegin) {
        NewRange = newEnd - newBegin;
    } else {
        NewRange = newBegin - newEnd;
        invFlag = 1;
    }

    zeroRefCurVal = inputValue - originalMin;
    normalizedCurVal = zeroRefCurVal / OriginalRange; // normalize to 0 - 1 float

    // Check for originalMin > originalMax  - the math for all other cases i.e. negative numbers seems to work out fine
    if (originalMin > originalMax) {
        return 0;
    }

    if (invFlag == 0) {
        rangedValue = (pow(normalizedCurVal, curve) * NewRange) + newBegin;

    } else // invert the ranges
    {
        rangedValue = newBegin - (pow(normalizedCurVal, curve) * NewRange);
    }

    return rangedValue;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
    if (WheelPos < 85) {
        return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    } else if (WheelPos < 170) {
        WheelPos -= 85;
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    } else {
        WheelPos -= 170;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
}
