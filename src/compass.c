#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <math.h> /*Declarations of sin,cos and so on*/

const _Bool north [32][32]={ //original north facing matrix on which we will perform rotation
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  };

_Bool compass [32][32]; //rotated matrix
uint8_t compass_data[128]; //rotated matrix in a display_image() compatible array


void clear_matrix(void) //clean current compass matrix
{
  int i,j;
  for(i=0; i<32; i++)
    for(j=0; j<32; j++)
    {
       compass[i][j]=0;
    }

}

void rotation(double radian)   // function for rotating the north matrix about the middle/origin for X radians
{                              // and storing it in compass matrix
  double x,y;
  double rx,ry; //rotated x and y
  int i,j;
  int ri,rj; //rotated i and j
  for(i=0; i<32; i++)
    for(j=0; j<32; j++)
    {
      if(north[i][j]==0) //skip 0 values since we care only about 1s
      continue;
      x=(double) -15 + j; //convert i into x coordinates (origin=[15][15])
      y=(double) 15 - i; //convert j into y coordinates
      rx=cos(radian)*x+sin(radian)*y; //find rotated coordinates
      ry=-sin(radian)*x+cos(radian)*y; //find rotated coordinates
      rx=(int)(rx < 0 ? (rx - 0.5) : (rx + 0.5));
      ry=(int)(ry < 0 ? (ry - 0.5) : (ry + 0.5)); //rounding double to int
      rj=15+rx;
      ri=15-ry; //getting rotated matrix coordinates
      compass[ri][rj]=1; //setting the rotated bit in the final matrix to 1
    }
  }

void fix_matrix(void){ //deletes bit gaps
  int i,j,k;
  for(i=0; i<32; i++){
    for(j=0; j<32; j++)
    {
      if(compass[i-1][j]&&compass[i+1][j]||compass[i][j-1]&&compass[i][j+1]) //checking if there are any gaps
        compass[i][j]=1;                                                     //and filling them with 1s
      if(compass[i-1][j]&&compass[i+2][j]||compass[i-2][j]&&compass[i+1][j]) //check for wider vertical gaps
        { compass[i][j]=1;
          compass[i+1][j]=1;
          compass[i-1][j]=1;}
      if(compass[i][j+1]&&compass[i][j-2]||compass[i][j-1]&&compass[i][j+2]) //check for wider horizontal gaps
        { compass[i][j]=1;
          compass[i][j+1]=1;
          compass[i][j-1]=1;}

    }
  }
}
uint8_t * get_compass_data(void) //function for getting the data for display_image (probably not working right)
{
  return compass_data;
}

int rot=0;
void increase_rot(void) //function for testing
{
  rot++;
}
void convert_to_data(void) //converts the 32x32 bitmap into 4 lines of 32 vertical bytes ready to be printed on the display
{
  int i,j,k;
  for(i=0;i<4;i++) //splits data into 4 lines
    for(j=0;j<32;j++) //goes through every single byte
      for(k=8;k>0;k--) //converts single bits of the array into one byte
      {
        compass_data[j+i*32]=compass_data[j+i*32]<<1; //shift the current value of the byte by 1 (multiply by 2)
        compass_data[j+i*32]=compass_data[j+i*32]+(1*compass[i*8+k][j]); //add (1*array bit) to the current value
      }
}
void compasswork(void) //function for testing
{
  clear_matrix();
  rotation((double)rot/10);
  fix_matrix();
  convert_to_data();
  display_image(96,compass_data);
}
