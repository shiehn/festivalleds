


int candyLength = 6;
int spacing = 20;
int offset = 0;

int colorCombos[27][2] = {{4845,3072},
{-1024,216},
{-17920,24576},
{-17920,24576},
{-28928,16910},
{-7791,543},
{-9953,5667},
{12513,22343},
{6143,-19723},
{-32012,18665},
{-32012,18665},
{10243,11854},
{-29165,27974},
{-29165,27974},
{21706,2315},
{21706,2315},
{7840,29215},
{7469,5121},
{21035,6920},
{14592,1811},
{-31774,9240},
{-24106,21124},
{16889,-3002},
{-17897,23849},
{14062,8210},
{-14144,13321},
{-8279,28591}};

int currentColor = 0;
int currentColor2 = 0;

int togglePhase = 0;
int toggleIndex = 0;

int getOffSet(int index, int off_set, int maxlen){
  int value = index + off_set;

  if(value < maxlen){
    return value;
  } else {
    return value - maxlen;  
  }
}

void candy_cane(){ 
  int comboSize = sizeof colorCombos/sizeof colorCombos[0];
 
  if(currentColor ==0 || currentColor2 ==0){
    int randy = random(0,sizeof(colorCombos));
    currentColor = colorCombos[randy][0]; 
    currentColor2 = colorCombos[randy][1];
  }
  
  int candyCount = 0;
  int singlePixPos = N_PIXELS-offset;

  int contact [N_PIXELS];
  
  for (int i = 0; i < N_PIXELS; i++) { 
    contact[i] = 0;
    
    if (candyCount < candyLength) {
      contact[i] = 1;  
      strip.setPixelColor(getOffSet(i, offset, N_PIXELS), currentColor); 
      candyCount++;
    } else if (candyCount < candyLength+spacing) {
      contact[i] = 0;
      //SPACING COLOR
      strip.setPixelColor(getOffSet(i, offset, N_PIXELS), currentColor2);
      candyCount++;
    } else {
      strip.setPixelColor(getOffSet(i, offset, N_PIXELS), currentColor2);
      contact[i] = 0;
      candyCount=0;
    }  
  }
 
  delay(10);

  if(offset >= N_PIXELS){
    for (int i = 0; i < N_PIXELS/3; i++) { 
      strip.setPixelColor(i, colorCombos[toggleIndex][0]);
      strip.setPixelColor(N_PIXELS-i, colorCombos[toggleIndex][0]);
      strip.show();
    }

    
    //randomSeed(analogRead(A0));
    int randy = random(0,comboSize);
 
    togglePhase++;
    if(togglePhase >= 3){
      
      togglePhase = 0;

      toggleIndex++;
      if(toggleIndex >= comboSize){
        toggleIndex=0;
      }
    } 
 
    if(togglePhase == 0){
      currentColor = colorCombos[toggleIndex-1][0];
      currentColor2 = colorCombos[toggleIndex][1];
    }else if(togglePhase == 1){
      currentColor = colorCombos[toggleIndex][0];
      currentColor2 = colorCombos[toggleIndex][1];
    }else{
      currentColor = colorCombos[toggleIndex+1][0];
      currentColor2 = colorCombos[toggleIndex][1];
    }
     
    offset=0;  
  }else{
    //SINGLE PIXEL ...
    if(contact[singlePixPos] == 1){ 
      strip.setPixelColor(singlePixPos, strip.Color(127, 127, 127));
    }

    if(contact[singlePixPos+1] == 1){ 
      strip.setPixelColor(singlePixPos+1, strip.Color(127, 127, 127));
    }

    if(contact[singlePixPos+2] == 1){ 
      strip.setPixelColor(singlePixPos+2, strip.Color(127, 127, 127));
    }

    if(contact[singlePixPos+3] == 1){ 
      strip.setPixelColor(singlePixPos+2, strip.Color(127, 127, 127));
    }

    if(contact[singlePixPos+5] == 1){ 
      strip.setPixelColor(singlePixPos+5, strip.Color(127, 127, 127));
    }

    if(contact[singlePixPos+7] == 1){ 
      strip.setPixelColor(singlePixPos+7, strip.Color(127, 127, 127));
    }

    if(contact[singlePixPos+10] == 1){ 
      strip.setPixelColor(singlePixPos+10, strip.Color(127, 127, 127));
    }

    if(contact[singlePixPos+13] == 1){ 
      strip.setPixelColor(singlePixPos+13, strip.Color(127, 127, 127));
    }

    offset++;
  }
 
  handleButtonClick(); 
  strip.show();
  strip.clear();
}
