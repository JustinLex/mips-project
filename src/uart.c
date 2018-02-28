#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */

/*functions for interacting with the UART module, written mainly by Justin Lex*/

//set up uart bus and start listening to the gps module
void setupuart() {
  /*See PIC32MX3XX datasheet for addresses, Reference manual 21 for settings.*/
  U2BRG = 129; // set uart baud to 38400 baud when BRGH=0 [=(80Mhz/16/38400)-1]
  U2STA = 0x1000; //00 0 1 0 0 0 0 00 0 0 0 0 0 0 set only RX, interrupt whenever buffer has data
  U2MODE = 0x8000; //1 0 0 0 0 0 00 0 0 0 0 0 00 0 Enable UART2, no special options
}

//disable uart bus so we can update the display
void disableuart() {
  U2MODE = 0;
}


/*functions to handle byte alignment on the bus*/
uint16_t buffer = 0; //holds last two bytes read from UART bus, unaligned

void pull_in_uart_data() {
  buffer <<= 8; //shift out oldest byte
  buffer |= U2RXREG; //read in newest byte
}

uint8_t read_shifted_byte( uint8_t shift_amt ) {
  return (uint8_t) (buffer >> shift_amt);
}

void clear_framing_error() {
  pull_in_uart_data(); //read the errored byte to clear the error
  buffer = 0; //erase the buffer
}

uint16_t* get_uart_buffer() {
  return &buffer;
}
