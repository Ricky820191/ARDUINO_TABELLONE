#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "Wire.h"
#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(150, PIN, NEO_GRB + NEO_KHZ800);
  
  int x_max = 15;
  int y_max = 10; 
  int counter[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int c[10] = {240, 220, 200, 180, 160, 140, 120, 100, 80, 60}; //non mettere c[0] = 0
  uint32_t acc[10] = {strip.Color(0, 0, 0), strip.Color(0, 0, 0), strip.Color(0, 0, 0), strip.Color(0, 0, 0), strip.Color(0, 0, 0),
                      strip.Color(0, 0, 0), strip.Color(0, 0, 0), strip.Color(0, 0, 0), strip.Color(0, 0, 0), strip.Color(0, 0, 0)};

  int grid[10][15];

  
  void circle0(uint32_t acc);
  void circle1(uint32_t acc);
  void circle2(uint32_t acc);
  void circle3(uint32_t acc);
  void circle4(uint32_t acc);
  void circle5(uint32_t acc);
  void circle6(uint32_t acc);
  void circle7(uint32_t acc);
  void circle8(uint32_t acc);
  void circle9(uint32_t acc);
  
  void bright(int circle, int brightness, int counter);

void setup() {
  strip.begin();
  strip.setBrightness(150);
  strip.show();

  for(int i=0; i < y_max; i++){
    
    for(int j=0; j < x_max; j++){

      if(i % 2 == 0){
        grid[i][(x_max-1) -j] = x_max*i + j;
      } else {
        grid[i][j] = x_max*i + j;  //ordine un po' strano dovuto a come installeremo i led (a serpente)
      }
      
    }
  }


}

void loop() {



for(int i=0; i<10; i++){
    if(c[i]<256){
      bright(i, c[i], counter[i]);
  } else if((c[i]>=256) && (c[i]<=255*2)){
      bright(i, 255*2-c[i], counter[i]);
  } else {
    c[i]=0;
    counter[i] = counter[i] +1;
  }
     if(counter[i]>2){
      counter[i] = 0;
  }
}



for(int j=0; j<10; j++){

  
    c[j] = c[j]+10;
  
}



}

void circle0(uint32_t acc){
 

  
  strip.setPixelColor(grid[4][6], acc);
  strip.setPixelColor(grid[4][7], acc);
  strip.setPixelColor(grid[5][6], acc);
  strip.setPixelColor(grid[5][7], acc);
  strip.show();


}

void circle1(uint32_t acc) {
 


  for(int i=0; i<2; i++){
    strip.setPixelColor(grid[4+i][8], acc);
    strip.setPixelColor(grid[4+i][5], acc);
    strip.setPixelColor(grid[3][6+i], acc);
    strip.setPixelColor(grid[6][6+i], acc);
  }

  strip.show();

  }

void circle2(uint32_t acc) {
  


  for(int i=0; i<4; i++){
    strip.setPixelColor(grid[3+i][4], acc);
    strip.setPixelColor(grid[3+i][9], acc);
    strip.setPixelColor(grid[2][5+i], acc);
    strip.setPixelColor(grid[7][5+i], acc);

    if(i<2){
      strip.setPixelColor(grid[4+i][3], acc);
      strip.setPixelColor(grid[4+i][10], acc);
    //  strip.setPixelColor(grid[1][6+i], acc);
    //  strip.setPixelColor(grid[8][6+i], acc);
    }
  }
  strip.setPixelColor(grid[3][8], acc);
  strip.setPixelColor(grid[6][8], acc);
  strip.setPixelColor(grid[6][5], acc);
  strip.setPixelColor(grid[3][5], acc);

  strip.show();


}

void circle3(uint32_t acc) {
  


  for(int i=0; i<4; i++){
    strip.setPixelColor(grid[1][5+i], acc);
    strip.setPixelColor(grid[8][5+i], acc);


    if(i<2){
      strip.setPixelColor(grid[4+i][11], acc);
      strip.setPixelColor(grid[4+i][2], acc);
    }
  }

  for(int j=0; j<4; j=j+3){
    strip.setPixelColor(grid[3+j][10], acc);
    strip.setPixelColor(grid[3+j][3], acc);
  }

  strip.setPixelColor(grid[2][9], acc);
  strip.setPixelColor(grid[7][9], acc);
  strip.setPixelColor(grid[2][4], acc);
  strip.setPixelColor(grid[7][4], acc);

  strip.show();


}

void circle4(uint32_t acc) {
  


  for(int i=0; i<4; i++){
    strip.setPixelColor(grid[0][5+i], acc);
    strip.setPixelColor(grid[9][5+i], acc);

    if(i<2){
      strip.setPixelColor(grid[1+i][9+i], acc);
      strip.setPixelColor(grid[7+i][10-i], acc);
      strip.setPixelColor(grid[1+i][4-i], acc);
      strip.setPixelColor(grid[7+i][3+i], acc);
      strip.setPixelColor(grid[4+i][12], acc);
      strip.setPixelColor(grid[4+i][1], acc);
    }
  }
for(int j=0; j<4; j=j+3){
  strip.setPixelColor(grid[3+j][11], acc);
  strip.setPixelColor(grid[3+j][2], acc);
}

  strip.show();

}

void circle5(uint32_t acc){
  

  for(int i=0; i<5; i++){
    strip.setPixelColor(grid[5+i][13-i], acc);
    strip.setPixelColor(grid[4-i][13-i], acc);
    strip.setPixelColor(grid[5+i][i], acc);
    strip.setPixelColor(grid[4-i][i], acc);
  }
  strip.show();
}

void circle6(uint32_t acc){
 

  for(int i=0; i<5; i++){
    strip.setPixelColor(grid[5+i][14-i], acc);
    strip.setPixelColor(grid[4-i][14-i], acc);
    
    if(i<4){
      strip.setPixelColor(grid[6+i][i], acc);
      strip.setPixelColor(grid[3-i][i], acc);
    }
  }
  strip.show();  
}


void circle7(uint32_t acc){
  

  for(int i=0; i<4; i++){
    strip.setPixelColor(grid[6+i][14-i], acc);
    strip.setPixelColor(grid[3-i][14-i], acc);
    
    if(i<3){
      strip.setPixelColor(grid[7+i][i], acc);
      strip.setPixelColor(grid[2-i][i], acc);
    }
  }
  strip.show();  
}


void circle8(uint32_t acc){
  

  for(int i=0; i<3; i++){
    strip.setPixelColor(grid[7+i][14-i], acc);
    strip.setPixelColor(grid[2-i][14-i], acc);
    
    if(i<2){
      strip.setPixelColor(grid[8+i][i], acc);
      strip.setPixelColor(grid[1-i][i], acc);
    }
  }
  strip.show();  
}



void circle9(uint32_t acc){
  

  for(int i=0; i<2; i++){
    strip.setPixelColor(grid[8+i][14-i], acc);
    strip.setPixelColor(grid[1-i][14-i], acc);
    
    if(i<1){
      strip.setPixelColor(grid[9+i][i], acc);
      strip.setPixelColor(grid[i][i], acc);
    }
  }
  strip.show();  
}




void bright(int circle, int brightness, int counter){



  switch(counter){
    case 0:
      acc[circle] = strip.Color(brightness, 0, 0);
      break;

    case 1:
      acc[circle] = strip.Color(0, brightness, 0);
      break;

    case 2:
      acc[circle] = strip.Color(0, 0, brightness);
      break;
  }

  switch(circle){
    case 0:
      circle0(acc[circle]);
      break;

    case 1:
      circle1(acc[circle]);
      break;

    case 2:
      circle2(acc[circle]);
      break;

    case 3:
      circle3(acc[circle]);
      break;

    case 4:
      circle4(acc[circle]);
      break;

    case 5:
      circle5(acc[circle]);
      break;

    case 6:
      circle6(acc[circle]);
      break;

    case 7:
      circle7(acc[circle]);
      break;

    case 8:
      circle8(acc[circle]);
      break;

    case 9:
      circle9(acc[circle]);
      break;
  }
  
}
