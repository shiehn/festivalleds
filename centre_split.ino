void centreSplit(){   
  strip.clear();  

  splitInHalf();

  //N_PIXELS
  //int color = random(1,65536);
  //strip.setPixelColor(3, color);
  //strip.show();
  //delay(0);
    
//  for (int i = 0; i < N_PIXELS; i++) {  
//   
//  }  
}
int numOfSplit = 1;
void splitInHalf(){ 
  int pause=2;
  int color = 0;

  if (numOfSplit==1){
    int centreOneAB = N_PIXELS/2; 
  
    for (int i = 0; i < N_PIXELS/2; i++) {  
      if (handleButtonClick()) {
        return;
      }
        strip.clear();  

        color = random(1,65536);
        strip.setPixelColor(centreOneAB-i, color);
        strip.setPixelColor(centreOneAB+i, color); 
        delay(pow(pause, 1));
        strip.show();
    }
  } else if (numOfSplit==2){
    int centreTwoA = (N_PIXELS/4);
    int centreTwoB = (N_PIXELS/4)+((N_PIXELS/2)*1);
    
    for (int i = 0; i < N_PIXELS/4; i++) { 
      if (handleButtonClick()) {
        return;
      }
      strip.clear();  
      color = random(1,65536);
      strip.setPixelColor(centreTwoA-i, color);
      strip.setPixelColor(centreTwoA+i, color); 

      color = random(1,65536);
      strip.setPixelColor(centreTwoB-i, color);
      strip.setPixelColor(centreTwoB+i, color); 
      delay(pow(pause, 4));
      strip.show();
    }
  } else if (numOfSplit==3){
    int centreThreeA = (N_PIXELS/8); 
    int centreThreeB = (N_PIXELS/8)+((N_PIXELS/4)*1);
    int centreThreeC = (N_PIXELS/8)+((N_PIXELS/4)*2);
    int centreThreeD = (N_PIXELS/8)+((N_PIXELS/4)*3);
  
    for (int i = 0; i < N_PIXELS/8; i++) {
      if (handleButtonClick()) {
        return;
      } 
      strip.clear();  
      color = random(1,65536);
      strip.setPixelColor(centreThreeA-i, color);
      strip.setPixelColor(centreThreeA+i, color); 
  
      strip.setPixelColor(centreThreeB-i, color);
      strip.setPixelColor(centreThreeB+i, color); 

color = random(1,65536);
      strip.setPixelColor(centreThreeC-i, color);
      strip.setPixelColor(centreThreeC+i, color); 
  
      strip.setPixelColor(centreThreeD-i, color);
      strip.setPixelColor(centreThreeD+i, color);
      delay(pow(pause, 4));
      strip.show();
    }
  } else if (numOfSplit==4){
    int centreFourA = (N_PIXELS/16);
    int centreFourB = (N_PIXELS/16)+((N_PIXELS/8)*1);
    int centreFourC = (N_PIXELS/16)+((N_PIXELS/8)*2);
    int centreFourD = (N_PIXELS/16)+((N_PIXELS/8)*3);
    int centreFourE = (N_PIXELS/16)+((N_PIXELS/8)*4);
    int centreFourF = (N_PIXELS/16)+((N_PIXELS/8)*5);
    int centreFourG = (N_PIXELS/16)+((N_PIXELS/8)*6);
    int centreFourH = (N_PIXELS/16)+((N_PIXELS/8)*7);
  
    for (int i = 0; i < N_PIXELS/16; i++) { 
      if (handleButtonClick()) {
        return;
      }
      strip.clear();   
      color = random(1,65536);
      strip.setPixelColor(centreFourA-i, color);
      strip.setPixelColor(centreFourA+i, color); 
  
      strip.setPixelColor(centreFourB-i, color);
      strip.setPixelColor(centreFourB+i, color); 

      strip.setPixelColor(centreFourC-i, color);
      strip.setPixelColor(centreFourC+i, color); 
  
      strip.setPixelColor(centreFourD-i, color);
      strip.setPixelColor(centreFourD+i, color); 

color = random(1,65536);
      strip.setPixelColor(centreFourE-i, color);
      strip.setPixelColor(centreFourE+i, color); 
  
      strip.setPixelColor(centreFourF-i, color);
      strip.setPixelColor(centreFourF+i, color); 

      strip.setPixelColor(centreFourG-i, color);
      strip.setPixelColor(centreFourG+i, color); 
  
      strip.setPixelColor(centreFourH-i, color);
      strip.setPixelColor(centreFourH+i, color);
      delay(pow(pause, 6));
      strip.show();
    }
  } else if (numOfSplit==5){
    int centreFiveA = (N_PIXELS/32);
    int centreFiveB = (N_PIXELS/32)+((N_PIXELS/16)*1);
    int centreFiveC = (N_PIXELS/32)+((N_PIXELS/16)*2);
    int centreFiveD = (N_PIXELS/32)+((N_PIXELS/16)*3);
    int centreFiveE = (N_PIXELS/32)+((N_PIXELS/16)*4);
    int centreFiveF = (N_PIXELS/32)+((N_PIXELS/16)*5);
    int centreFiveG = (N_PIXELS/32)+((N_PIXELS/16)*6);
    int centreFiveH = (N_PIXELS/32)+((N_PIXELS/16)*7);
    int centreFiveI = (N_PIXELS/32)+((N_PIXELS/16)*8);
    int centreFiveJ = (N_PIXELS/32)+((N_PIXELS/16)*9);
    int centreFiveK = (N_PIXELS/32)+((N_PIXELS/16)*10);
    int centreFiveL = (N_PIXELS/32)+((N_PIXELS/16)*11);
    int centreFiveM = (N_PIXELS/32)+((N_PIXELS/16)*12);
    int centreFiveN = (N_PIXELS/32)+((N_PIXELS/16)*13);
    int centreFiveO = (N_PIXELS/32)+((N_PIXELS/16)*14);
    int centreFiveP = (N_PIXELS/32)+((N_PIXELS/16)*15);
  
    for (int i = 0; i < N_PIXELS/32; i++) {
       
      strip.clear();   
      color = random(1,65536);
      strip.setPixelColor(centreFiveA-i, color);
      strip.setPixelColor(centreFiveA+i, color); 

      strip.setPixelColor(centreFiveB-i, color);
      strip.setPixelColor(centreFiveB+i, color); 

      strip.setPixelColor(centreFiveC-i, color);
      strip.setPixelColor(centreFiveC+i, color); 

      strip.setPixelColor(centreFiveD-i, color);
      strip.setPixelColor(centreFiveD+i, color);

color = random(1,65536);
      strip.setPixelColor(centreFiveE-i, color);
      strip.setPixelColor(centreFiveE+i, color);

      strip.setPixelColor(centreFiveF-i, color);
      strip.setPixelColor(centreFiveF+i, color);

      strip.setPixelColor(centreFiveG-i, color);
      strip.setPixelColor(centreFiveG+i, color);
      
      strip.setPixelColor(centreFiveH-i, color);
      strip.setPixelColor(centreFiveH+i, color);

color = random(1,65536);
      strip.setPixelColor(centreFiveI-i, color);
      strip.setPixelColor(centreFiveI+i, color);

      strip.setPixelColor(centreFiveJ-i, color);
      strip.setPixelColor(centreFiveJ+i, color);

      strip.setPixelColor(centreFiveK-i, color);
      strip.setPixelColor(centreFiveK+i, color);

      strip.setPixelColor(centreFiveL-i, color);
      strip.setPixelColor(centreFiveL+i, color);

color = random(1,65536);
      strip.setPixelColor(centreFiveM-i, color);
      strip.setPixelColor(centreFiveM+i, color);

      strip.setPixelColor(centreFiveN-i, color);
      strip.setPixelColor(centreFiveN+i, color);

      strip.setPixelColor(centreFiveO-i, color);
      strip.setPixelColor(centreFiveO+i, color);

      strip.setPixelColor(centreFiveP-i, color);
      strip.setPixelColor(centreFiveP+i, color);
      
      delay(pow(pause, 6));
      strip.show();
    }
  } 

  delay(pow(pause, 6));

  
 // Serial.println(numOfSplit);

  numOfSplit++;
  if (numOfSplit > 5){
    numOfSplit=1;
  }
}
