/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

void user_isr( void )
{
  return;
}

//set up uart and start listening to the gps module
void setupuart() {
  /*See PIC32MX3XX datasheet for addresses, Reference manual 21 for settings.*/
  U2BRG = 0x208; // set uart baud to 9600 if pbclk is 1:1 and BRGH=0 [=(80Mhz/16/9600)-1]
  U2STA = 0x1080; //00 0 1 0 0 0 0 10 0 0 0 0 0 0 set only RX, interrupt when buffer is 3/4 filled
  U2MODE = 0x8000; //1 0 0 0 0 0 00 0 0 0 0 0 00 0 Enable UART2, no special options
}

void disableuart() {
  U2MODE = 0;
}

int datastringcounter = 0;

//checks if there is a NMEA message in the uart buffer
/*void lookforgga(char* datastring) {
  int* reg_u2sta = (int *) 0xBF806210; //UART2 status/control register
  _Bool data_available = 0;

  char screendelaycounter = 0; //skip every 20 updates so we get 60fps, not 1200 fps
  /*loop here, updating display until data is available*/
  /*while(!data_available) {
    delay( 1 );

    if(screendelaycounter > 19) {
      //check idle bit
      _Bool r_idle = (_Bool) ((U2STA & 0x10) >> 4); //RIDLE is bit 4 of U2STA
      //show data status
      if(r_idle) display_string( 3, "IDLE" );
      else display_string( 3, "recieving...");
      display_update();
      screendelaycounter = 0;
    }
    else screendelaycounter++;

    data_available = (_Bool) (U2STA & 0x1); // check if there's data available
  }

  /* read byte from bus*/
  /*int read_error = USTA & 0x0c; //check for PERR or FERR
  char newchar = (char) U2RXREG; //read byte
  if(read_error) newchar = '?';

  /*update datastring*/
  //if this is a new string or our string is too long already (might have missed a $), then reset the data string.
  /*if(newchar == '$' || datastringcounter > 4 ) {
    datastring[0] = '$';
    datastring[1] = '\0';
    datastringcounter = 1;
  } else {
    datastring[datastringcounter] = newchar;
    datastring[datastringcounter + 1] = '\0';
    datastringcounter++;
  }

}*/