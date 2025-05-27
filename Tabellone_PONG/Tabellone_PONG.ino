#include <Adafruit_NeoPixel.h>
#include "Arduino.h"
#include "Wire.h"

#define PIN 6
#include "DFRobotIRPosition.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(150, PIN, NEO_GRB + NEO_KHZ800);
DFRobotIRPosition myDFRobotIRPosition;

int y_cam_max = 800;
int y_cam;
int x_cam;

int x = 6;
int y = 4;
int dir_x = 1;
int dir_y = 1;

int y_max = 10;
int x_max = 15;

int y_player;
int y_com;

int grid[10][15][2];

int counter = 0;
int z = 0;
int e = 0;

uint32_t white = strip.Color(255, 255, 255);
uint32_t green = strip.Color(0, 255, 0);
uint32_t red = strip.Color(255, 0, 0);



void setup() {

    strip.begin();
  strip.setBrightness(150);
  strip.show();
  Serial.begin(19200);
  myDFRobotIRPosition.begin();

  for(int i=0; i < y_max; i++){
    
    for(int j=0; j < x_max; j++){

      if(i % 2 == 0){
        grid[i][(x_max-1) -j][0] = x_max*i + j;
      } else {
        grid[i][j][0] = x_max*i + j;  //ordine un po' strano dovuto a come installeremo i led (a serpente)
      }
      grid[i][j][1] = 0;

    }
  }

for(int i=0; i<y_max; i++){
      grid[i][0][1] = 2;
      grid[i][14][1] = 2;
}


for(int i=0; i<x_max; i++){
      grid[0][i][1] = 1;
      grid[9][i][1] = 1;
}


}

void loop() {
  

  myDFRobotIRPosition.requestPosition();          /*Initialize IR Cam*/
  
  if (myDFRobotIRPosition.available()) {          /*whole program is inside this if (look at the end for else condition)*/
                       /*Assign IR Cam sensed info to arrays*/          /*3 x coordinates*/
      y_cam = myDFRobotIRPosition.readY(1);
        if(y_cam <= y_cam_max){
          y_player = floor(y_cam*y_max/y_cam_max);
        } else {
          y_player = 0;
}
      for(int i=0; i<y_max-1; i++){
        
        if((i<y_player-1) || (i>y_player+1)){
          grid[i+1][1][1] = 0;
          
        } else {
          
          grid[i+1][1][1] = 1;
        }

        
        
      }


      grid[y][x][1] = 0;

      y = y+dir_y;
      x = x+dir_x;

      grid[y][x][1] = -1;

      if((x+dir_x < 1) || (x+dir_x > x_max-2)){
      dir_x = -dir_x;

    }


    for(int i=0; i<5; i++){
      if((x + dir_x == 1) && (y + dir_y == y_player-2+i)){
        dir_x = -dir_x;
      }
    }


    if((y+dir_y < 1) || (y+dir_y > y_max-2)) {
      dir_y = -dir_y;
    }
    
    y_com = y;

      for(int i=0; i<y_max-1; i++){
        if((i<y_com-1) || (i>y_com+1)){
          grid[i+1][x_max-2][1] = 0;
          
        } else {
          
          grid[i+1][x_max-2][1] = 1;
        }

   
  }

for(int i=0; i<y_max; i++){
  for(int j=0; j<x_max; j++){
    if(grid[i][j][1] == 1){
      strip.setPixelColor(grid[i][j][0], green);
    } else if(grid[i][j][1] == -1){
      strip.setPixelColor(grid[i][j][0], white);
    } else if(grid[i][j][1] == 2){
      strip.setPixelColor(grid[i][j][0], red);
    } else {
      strip.setPixelColor(grid[i][j][0], 0,0,0);
    }
    
  }
}
 
} else {

  for(z=0; z<2; z++){
    for(e=0; e<2; e++){
  strip.setPixelColor(grid[4+z][6+e][0], white);
    }
  }
  

  
}
Serial.print("y_cam: ");
Serial.print(y_cam);

Serial.print("y: ");
Serial.print(y);

Serial.print("\n");



strip.show();
delay(100);
}
