
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

int prime = 1234567;

int mytime = 0x0000;

uint8_t timeoutcount = 0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  /*if uart interrupt, call uart packet handler*/
  if(IFS(1) & 0x100) {
    //int a_byte = read_byte();
    //display_debug(&a_byte);
    handlepacket();
    IFSCLR(1) = 0x100;
  }


  if(IFS(0) & 0x100) { //T2
    //see what page we're on, then write the correct data to the screen and update
    //display_debug(get_nav_clock_iTOW());
    //display_update();
    IFSCLR(0) = 0x100;
  }

  //button interrupts for changing pages?
  /*if(IFS(0) & 0x800) { //INT2
    tick( &mytime );
    tick( &mytime );
    tick( &mytime );
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    IFSCLR(0) = 0x800;

  }*/

  return;
}

/* Lab-specific initialization goes here */
void labinit( void ) {



  /*initialize timer2*/ //TODO: Reconfig for project
  T2CONCLR = 0xFFFF; //disable timer 2 and clear registers if enabled
  T2CONSET = 0x70; //set timer prescale to 256:1 (we need to count to 8M cycles, which is not possible with 1:64 or lower)
  TMR2 = 0x0; //clear timer 2 count
  PR2 = 0x7a12; //set period to 31250 = 100ms@312.5khz (80Mhz@1:256)
  IFSCLR(0) = 0x100; //reset timer 2 Interrupt flag
  IPC(2) = 0x1A; //set timer2 interrupts to 2nd highest priority
  IEC(0) = 0x100; //enable timer 2 interrupts
  T2CONSET = 0x8000; //enable timer

  /*initialize uart2 rx interrupt*/
  IFSCLR(1) = 0x100; //reset U2RX Interrupt flag
  IPC(8) = 0x1F; //set U2RX interrupts to highest priority
  IEC(1) = 0x100; //enable U2RX interrupts //TODO: (ISN'T LISTED IN 320 SERIES REGISTER DIAGRAM??)
  setupuart(); //initialize uart2 port

  enable_interrupt();

  return;
}

/* This function is called repetitively from the main program */
void labwork( void ) {
  //format packets into ready-to-print strings and images
  //constantly handle button presses for screen change? or button interrupts?
  return;
}
