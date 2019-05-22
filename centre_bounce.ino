void centerBounce(){
  // %%%%%%%%%%%%%%%%%%%%%%%% VU_METER CODE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      //Serial.println("CENTRE BOUNCE");
      
  int colorSeed = random(1,65536); 
  int color = random(1,65536);
  
  int pause = 2;
  int di = N_PIXELS/2;
  int ui = N_PIXELS/2;
  int maxVal=(float)N_PIXELS/(float)2 * 2;
  for (int i = 0; i < maxVal; i++) { 
    strip.clear();  

    float ratio = (float)i/(float)maxVal;
    int baseColor = colorSeed*ratio;

    bool flip=false;
    
    for (int t = 0; t < (int)(i*0.5); t++) {
      float ratio = (float)t/(float)i*0.5;

      
     
      int trailColor = colorSeed*ratio;
      //Serial.println(trailColor);
      

      if(t > (int)(i*0.5)/4){
        int tempColor = trailColor+(t*50); 
        if (tempColor > 65535){
          tempColor = trailColor;
        } 
        
        if(flip==0){
          strip.setPixelColor(t, tempColor);
        }else{
          strip.setPixelColor(maxVal-t, tempColor);
        }
        flip = !flip; 

        if (handleButtonClick()) {
          return;
        }
      }
           
      strip.setPixelColor(ui-t, color);
      strip.setPixelColor(di+t, color);
    }
    
    strip.setPixelColor(ui, color);
    strip.setPixelColor(di, color);

    ui++;
    di--;
    
    strip.show();

    if(i<N_PIXELS/2){
      pause = pow(2,(i*0.005));
    }else{
      pause = 0;
    }
    pause = 0;
    delay(pause);
  }  
}
