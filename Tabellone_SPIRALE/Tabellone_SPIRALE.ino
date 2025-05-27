#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "Wire.h"
#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(150, PIN, NEO_GRB + NEO_KHZ800);
  
  int x_max = 15;
  int y_max = 10;

  int dim;

  int t=50;

  int x_new = 7;
  int y_new;

  int x_old = 6;
  int y_old = 4;

  int next = 1;
  int counter = 0;

  int i = 0;
  int j = 0;

  int grid[10][15];

  uint32_t acc = strip.Color(255,0,0);
  uint32_t color= strip.Color(255,0,0);

  uint32_t colorSwitch(int counter);

  
void setup() {
  
  strip.begin();
  strip.setBrightness(150);
  strip.show();

  for(int i=0; i < y_max; i++){
    
    for(int j=0; j < x_max; j++){

      if(i % 2 == 0){
        grid[i][j] = x_max*i + j;
      } else {
        grid[i][(x_max-1) -j] = x_max*i + j;  //ordine un po' strano dovuto a come installeremo i led (a serpente)
      }

    }
  }

}

void loop() {



  if(i % 2 == 0){
    
    if(next >= 0){
      
        if(x_old+j <= x_new){
          strip.setPixelColor(grid[y_old][x_old+j], color);
          delay(t);
          j++;
          
        } else {
          j = 0;
          x_old = x_new;
          y_new = y_old + next;
          next = next + 1;
          i = i+1;
        }
        
    } else {
      
        if(x_old+j >= x_new){
          strip.setPixelColor(grid[y_old][x_old+j], color);
          delay(t);
          j--;
          
        } else {
          j = 0;
          x_old = x_new;
          y_new = y_old + next;
          next = next - 1;
          i = i+1;
        }
    }
    
  } else {   
    if(next >= 0){

      if(y_old+j <= y_new){
        strip.setPixelColor(grid[y_old+j][x_old], color);
        delay(t);
        j++;
        
      } else {
        j=0;
        y_old = y_new;
        next = -next;
        x_new = x_old + next;
        i = i+1;
      }
      
    } else {

      if(y_old+j >= y_new){
        strip.setPixelColor(grid[y_old+j][x_old], color);
        delay(t);
        j--;
        
      } else {
        j=0;
        y_old = y_new;
        next = -next;
        x_new = x_old + next;
        i = i+1;
      }
    }  
  }


  strip.show();

  
  if( (x_new >= x_max) || (y_new >= y_max) || (x_new < 0) || (y_new < 0)){
    counter = counter + 1;
    if(counter > 2){
      counter = 0;
    }

    color = colorSwitch(counter);
  
    x_old = 6;
    y_old = 4;

    x_new = 7;
    y_new = 4;

    i = 0;
    next = 1;
  }


}


uint32_t colorSwitch(int counter){
  switch(counter){
    case 0: 
      return strip.Color(255,0,0);
      break;

    case 1:
      return strip.Color(0,255,0);
      break;

    case 2:
      return strip.Color(0,0,255);
      break;
  }
}
