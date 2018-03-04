/* mipslab.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

/* Declare Poll sequence functions from polling.c */
void poll(void);
void pollseq_next_step(void);

/* Declare UART bus functions from uart.c */
void uart_start_tx(void);
void uart_start_rx(void);
void disableuart(void);
uint8_t read_byte(void);
void clear_framing_error(void);

/* Declare packet-handling functions from packet.c */
void handlepacket(void);
void set_packet(int packet_nr);
void send_packet(int type);

/* Declare packet data functions from gpsdata.c */

void store_nav_pvt_payload(uint8_t* payload);

uint32_t* get_iTOW(void);
uint16_t* get_year(void);
uint8_t* get_month(void);
uint8_t* get_day(void);
uint8_t* get_hour(void);
uint8_t* get_min(void);
uint8_t* get_sec(void);
_Bool* get_validDate(void);
_Bool* get_validTime(void);
_Bool* get_fullyResolved(void);
uint32_t* get_tAcc(void);
int32_t* get_nano(void);

/* Deckare UI functions */
void display_page(void);
void page_switch(void);
int getbtns(void);

/* Declare display-related functions from mipslabfunc.c */
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

/* Declare lab-related functions from mipslabfunc.c */
char * itoaconv( int num );
void labwork(void);
int nextprime( int inval );
void quicksleep(int cyc);
void tick( unsigned int * timep );

/* Declare display_debug - a function to help debugging.

   After calling display_debug,
   the two middle lines of the display show
   an address and its current contents.

   There's one parameter: the address to read and display.

   Note: When you use this function, you should comment out any
   repeated calls to display_image; display_image overwrites
   about half of the digits shown by display_debug.
*/
void display_debug( volatile int * const addr );

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];
/* Declare text buffer for display output */
extern char textbuffer[4][16];

/* Declare functions written by students.
   Note: Since we declare these functions here,
   students must define their functions with the exact types
   specified in the laboratory instructions. */
/* Written as part of asm lab: delay, time2string */
void delay(int);
void time2string( char *, int );
/* Written as part of i/o lab: getbtns, getsw, enable_interrupt */
int getbtns(void);
int getsw(void);
void enable_interrupt(void);
