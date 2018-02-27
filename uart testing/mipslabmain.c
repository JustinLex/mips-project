/* mipslabmain.c

   This file written 2015 by Axel Isaksson,
   modified 2015, 2017 by F Lundevall

   Latest update 2017-04-21 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
#include <string.h>


int screendelaycounter = 0;
/*reserve 110 characters for gps data strings*/
char datastring[] ="aaaaaaaaaaaaaa";
uint8_t datastringlength = 0;

int main(void) {
        /*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */

	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;

	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;

	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);

	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
        SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;

	display_init();
	display_string(0, "Bork Bork"); //Bork Bork
	display_string(1, "You're doing"); //good timing
	display_string(2, "me a heck"); //pupper
	display_string(3, "Welcome!");
	display_update();

	display_image(96, icon);

	int mytime = 0x5957;

	setupuart();

	_Bool data_available = 0;

	while(1) {
		while(!data_available) {
	    delay( 1 );
			data_available = (_Bool) (U2STA & 0x1); // check if there's data available
		}
		/* read byte from bus*/
	  int read_error = U2STA & 0x0c; //check for PERR or FERR
	  char newchar = (char) U2RXREG; //read byte
	  if(read_error) newchar = '?';

		/*update datastring*/
	  //if this is a new string or our string is too long already (might have missed a $), then reset the data string.
		if(newchar == '$' || datastringlength > 11 ) {
	    datastring[0] = '$';
	    datastring[1] = '\0';
			datastringlength = 1;
	  } else {
	    datastring[datastringlength] = newchar;
	    datastring[datastringlength + 1] = '\0';
			datastringlength++;
	  }

		disableuart();
		display_string( 2, datastring);
	  display_update();
	}

	return 0;


}