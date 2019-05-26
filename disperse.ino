int dispersePattern[N_PIXELS];
int doffset = 0;

void disperse(){ 
 
  int index=0;
  int patternLen = 0;
  
  int seedlen = 8;
  int curlen = seedlen;
  int spacelen = 1;

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

  int randy = random(0,sizeof(colorCombos));
  int color1 = colorCombos[randy][0]; 
  int color2 = colorCombos[randy][1];

  for(int i=0; spacelen < seedlen*2; i++){
    for(int j=0; j<curlen; j++){
        dispersePattern[index]=1;
        index++;
    }

    for(int j=0; j<spacelen; j++){
        dispersePattern[index] = 0;
        index++;
    }

    curlen--;
    spacelen = spacelen +2 ; 
  } 
 
  for (int i = 0; i < N_PIXELS; i++) {  
    if(dispersePattern[i]==1){ 
      strip.setPixelColor(i+doffset, color1);
      strip.setPixelColor(N_PIXELS-i-doffset, color1);
    } 
 
    strip.show(); 
  }
 
  doffset++;

  for (int i = 0; i < N_PIXELS; i++) {  
    if(dispersePattern[i]==1){ 
      strip.setPixelColor(i+doffset, color2);
      strip.setPixelColor(N_PIXELS-i-doffset, color2);
    }  
 
    
  }
strip.show();  
  doffset++; 

  if(doffset > N_PIXELS/2){
    doffset=0;
    strip.clear();
  }
}
