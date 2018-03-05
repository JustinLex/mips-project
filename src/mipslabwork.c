
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

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{

  if(IFS(1) & 0x200) { //U2RX (UART recieve)
    while(U2STA & 0x1) { //interrupt only triggers once on RX, so we need to loop until we've read them all (actually, this has been changed to interrupt whenever buffer is 3/4 full, but we want to empty the buffer whenever it goes)
      handlepacket();
    }
  }

  if(IFS(0) & 0x100) { //T2 (Screen timer)
    if(spinner_status()) { //refresh the screen for the spinner
      disableuart();
      compasswork();
      uart_start_rx();
    }
    IFSCLR(0) = 0x100;
  }

  if(IFS(1) & 0x1) { // CN (button press)
    if(getbtns()){ //only trigger on button rising edge
      page_switch();
      display_page();
    }
  IFSCLR(1) = 0x1;
  }

  return;
}

/* Lab-specific initialization goes here */
void labinit( void ) {
  display_clear(); //clear display (screen remembers data between boots)

  TRISECLR = 0xff; //enable led output

  /*initialize timer2*/
  T2CONCLR = 0xFFFF; //disable timer 2 and clear registers if enabled
  T2CONSET = 0x60; //set timer prescale to 64:1
  TMR2 = 0x0; //clear timer 2 count
  PR2 = 0x30D4; //set period to
  IFSCLR(0) = 0x100; //reset timer 2 Interrupt flag
  IPC(2) = 0x1A; //set timer2 interrupts to 2nd highest priority
  IEC(0) = 0x100; //enable timer 2 interrupts
  T2CONSET = 0x8000; //enable timer

  /*initialize uart2 rx interrupt*/
  IFSCLR(1) = 0x200; //reset U2RX Interrupt flag
  IPC(8) = 0x1F; //set UART2 interrupts to highest priority
  IEC(1) = 0x200; //enable U2RX interrupts (Undocumented register! :D )

  /*initialize change notice interrupt*/
  CNCON = 0x8000; //enable change notice interrupts
  CNEN = 0x18000; //enable CN15(BTN3) and CN16(BTN4)
  PORTD = 0; //clear PORTD
  IPC(6) = 0x170000; //set CN to 3rd highest priority
  IFS(1) = 0; //clear CN interrupt flag
  IEC(1) = (IEC(1)|1); //enable CN interrupt enable bit

  enable_interrupt();

  uart_start_rx(); //start recieving bytes

  return;
}

/* This function is called repetitively from the main program */
void labwork( void ) {
  delay(1000);
  return;
}
