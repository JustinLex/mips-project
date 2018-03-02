#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */


/*functions for interacting with the UART module, written mainly by Justin Lex*/

//set up uart bus and start listening to the gps module
void uart_start_rx() {
  /*See PIC32MX3XX datasheet for addresses, Reference manual 21 for settings.*/
  U2BRG = 520; // set uart baud to 38400 baud when BRGH=0 [=(80Mhz/16/38400)-1] 520 129
  U2STA = 0x1080; //00 0 1 0 0 0 0 10 0 0 0 0 0 0 set only RX, interrupt whenever buffer is 3/4 full
  U2MODE = 0x8000; //1 0 0 0 0 0 00 0 0 0 0 0 00 0 Enable UART2, no special options
}



//disable uart bus so we can update the display
void disableuart() {
  U2MODE = 0;
}

uint8_t read_byte() {
  return U2RXREG;
}

void clear_framing_error() {
  int null = U2RXREG; //read the errored byte to clear the error
  *((&U2STA)+4) = 0x2; //clear FERR bit
}
