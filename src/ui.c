#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <string.h>

#define NUMBEROFPAGES 2

//functions for presenting data to the user

uint8_t page=0; //variable for current page

char pages[NUMBEROFPAGES][4][16] = { //page, line, char-in-string
  {
    "1111111111111111",
    "1111111111111111",
    "1111111111111111",
    "1111111111111111"
  },
  {
    "2222222222222222",
    "2222222222222222",
    "2222222222222222",
    "2222222222222222"
  }
};
char point[] = "."; //used to create decimalpoints in numbers


void page_update(void)
{
  /*page 0*/
  int32_t* lon_ptr = get_lon();
  int8_t longitude_int = *lon_ptr >> 7;
  uint8_t longitude_frac = *lon_ptr & 0x7f;

  strcpy(itoaconv(longitude_int), pages[0][1]);
  strcat(point, pages[0][1]);
  strcat(itoaconv(longitude_frac), pages[0][1]);

  int32_t* lat_ptr = get_lat();
  int8_t latitude_int = *lat_ptr >> 7;
  uint8_t latitude_frac = *lat_ptr & 0x7f;

  strcpy(itoaconv(latitude_int), pages[0][2]);
  strcat(point, pages[0][2]);
  strcat(itoaconv(latitude_frac), pages[0][2]);

  /*page 1*/
  uint8_t* min_ptr = get_min();
  strcpy(itoaconv(*min_ptr), pages[1][1]);

}

void display_page(void) //put data to the textbuffer according to the page
{
  disableuart();
  display_string(0, pages[page][0]);
  display_string(1, pages[page][1]);
  display_string(2, pages[page][2]);
  display_string(3, pages[page][3]);
  display_clear();
  display_update();
  uart_start_rx();
}


void page_switch(void)
{
  {
    if(getbtns() & 0x4) //go to previous page
      {
        if(page==0)
        page=NUMBEROFPAGES-1;
        else
        page--;
      }
      if(getbtns() & 0x2) //go to next page
      {
        if(page==NUMBEROFPAGES-1)
        page=0;
        else
        page++;
      }
  }
}

int getbtns(void)
{
  return ((PORTD & 0xe0)>>5); // return BTN4-BTN2 values as 3 least significant bits
}

void setleds(void) //lights up leds according to the number of satellites we see
{
  PORTECLR = 0x7f;
  if(get_numSV()>6)
  PORTESET=0x7f;
  else
  {
    char ledset = 0;
    int i;
    for(i=get_numSV();i>0;i--) {
      ledset|=1;
      ledset<<1;
    }
    PORTESET=ledset;
  }
}
