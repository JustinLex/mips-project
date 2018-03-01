#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

//asynchronously sequences the steps needed to poll the gps for data and then recieve it

int current_step = 0;

//perform a poll if one is not running already
void poll(){
  if(current_step == 0)
    pollseq_next_step();
}

//poll sequencer, calling it either begins a poll sequence, or executes
//the next step in the poll sequence
void pollseq_next_step() {

  switch (current_step) {
    case 0: //Poll UBX-NAV-PVT data
      //display_page(); //update screen before activating bus
      set_packet(0);
      current_step++;
      uart_start_tx();
      break;

    case 1: //recieve packets until we get back our UBX-NAV-PVT packet
      //TODO:
      //tell packet.c what kind of packet to look for
      //maybe set a timeout?
      current_step++;
      uart_start_rx();
      break;

    default: //sequence finished, reset sequence and update screen
      current_step = 0;
      //display_page();
  }

}
