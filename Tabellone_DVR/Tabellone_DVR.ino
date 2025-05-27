#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "Wire.h"
#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(150, PIN, NEO_GRB + NEO_KHZ800);
  
  int x_max = 15;
  int y_max = 10;

  int start_x = 0;
  int start_y = 0;

  int dir_x = 2;
  int dir_y = 1;

  int x;
  int y;

  int grid[10][15];
  int grid_fade[10][15];
  int grid_color[10][15];

  int pixel_size = 3;

  uint32_t acc_full[3] = {strip.Color(255, 0, 0), strip.Color(0, 255, 0), strip.Color(0, 0, 255)};
  uint32_t acc_fade;

  int color=0;

  

  int fade_length = 7;

  uint32_t trail_color(int pos, int color);
  
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

    grid_color[i][j] = 0;

    }
  }

    x=start_x;
    y=start_y;


  

}

void loop() {


      x = x+dir_x;
      y = y+dir_y;




    for(int i=0; i<pixel_size; i++){
      for(int j=0; j<pixel_size; j++){

      if((y+i>=0) && (y+i<y_max) && (x+j>=0) && (x+j<x_max)){
        grid_fade[y+i][x+j] = fade_length;
        grid_color[y+i][x+j] = color;
      }
        
      }
    }

/*
    grid_fade[y][x] = fade_length;
    grid_color[y][x] = color;
*/

    if((x <= 0) || (x >= x_max-pixel_size)){
      dir_x = -dir_x;
      
      color = color+1;
      if(color > 2){
        color = 0;
      }

    }


    if((y <= 0) || (y >= y_max-pixel_size)){
      dir_y = -dir_y;
      color = color+1;
      if(color > 2){
        color = 0;
      }

    }




    for(int a=0; a < y_max; a++){
      for(int b=0; b < x_max; b++){

          if(grid_fade[a][b] == fade_length){
            strip.setPixelColor(grid[a][b], acc_full[color]);
            grid_fade[a][b] = grid_fade[a][b]-1;

            
          } else if((grid_fade[a][b] < fade_length) && (grid_fade[a][b] > 0)){            
             strip.setPixelColor(grid[a][b], trail_color(grid_fade[a][b], grid_color[a][b]));
             grid_fade[a][b] = grid_fade[a][b]-1;

          } else if(grid_fade[a][b] == 0){
            strip.setPixelColor(grid[a][b], 0, 0, 0);
            
          } 
        
    }
  }

    
    
    delay(50*(abs(dir_x)+abs(dir_y)));
    strip.show();



}




uint32_t trail_color(int pos, int color){


  switch(color){
    case 0:
    acc_fade = strip.Color(20*pos, 0, 0);
    break;

    case 1:
    acc_fade = strip.Color(0, 20*pos, 0);
    break;

    case 2:
    acc_fade = strip.Color(0, 0, 20*pos);
    break;
  }

return acc_fade;
  
}
