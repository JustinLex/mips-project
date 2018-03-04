#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <string.h>
#include "mipslab.h"

#define NUMBEROFPAGES 3

//functions for presenting data to the user

uint8_t page=0; //variable for current page
_Bool spinner_enabled = 0;

char pages[NUMBEROFPAGES][4][17] = { //page, line, char-in-string
  {
    "",
    "",
    "",
    ""
  },
  {
    "Current time:",
    "",
    "Current date:",
    ""
  },
  {
    "You spin me",
    "right round",
    "like record",
    "round round"
  }
};

static char month[12][4] = {
  "Jan",
  "Feb",
  "Mar",
  "Apr",
  "May",
  "Jun",
  "Jul",
  "Aug",
  "Sep",
  "Oct",
  "Nov",
  "Dec"
};


void page_update(void)
{
  /*page 0*/
  int8_t longitude_int = get_lon() / 10000000;
  uint32_t longitude_frac = get_lon() - longitude_int;
  strcpy(pages[0][0], "Long: ");
  strcat(pages[0][0], itoaconv(longitude_int));
  strcat(pages[0][0], ".");
  strncat(pages[0][0], itoaconv(longitude_frac),5); //copy only 5 so we dont run off the screen

  int8_t latitude_int = get_lat() / 10000000;
  uint32_t latitude_frac = get_lat() - latitude_int;
  strcpy(pages[0][1], "Lat:  ");
  strcat(pages[0][1], itoaconv(latitude_int));
  strcat(pages[0][1], ".");
  strncat(pages[0][1], itoaconv(latitude_frac), 5); //copy only 5 so we dont run off the screen

  strcpy(pages[0][2], "Alt: ");
  strcat(pages[0][2], itoaconv(get_hMSL() / 1000)); //(convert altitude from mm to meters)
  strcat(pages[0][2], " m");

  /*page 1*/
  //put a null at the beginning of the string so we can use strcat
  pages[1][1][0] = 0;
  pages[1][3][0] = 0;

#define STRCPY_LEADINGZERO(DEST, GETFUNC) \
  if(GETFUNC < 10) { \
    strcat(DEST, "0"); \
    strcat(DEST, itoaconv(GETFUNC)); \
  } else { \
    strcat(DEST, itoaconv(GETFUNC)); \
  }

  STRCPY_LEADINGZERO(pages[1][1], get_hour())
  strcat(pages[1][1], ":");
  STRCPY_LEADINGZERO(pages[1][1], get_min())
  strcat(pages[1][1], ":");
  STRCPY_LEADINGZERO(pages[1][1], get_sec())

  strcpy(pages[1][3], itoaconv(get_day()));
  strcat(pages[1][3], " ");
  strcat(pages[1][3], month[get_month() - 1]);
  strcat(pages[1][3], " ");
  strcat(pages[1][3], itoaconv(get_year()));

}

void display_page(void) //put data to the textbuffer according to the page
{
  display_string(0, pages[page][0]);
  display_string(1, pages[page][1]);
  display_string(2, pages[page][2]);
  display_string(3, pages[page][3]);
  disableuart();
  display_clear();
  display_update();
  switch(page) { //optionally display an image if we're on a page that uses one
    case 3:
      compasswork();
      break;
  }
  uart_start_rx();
}


void page_switch(void) {
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
  if(page == 2) spinner_enabled = 1;
  else spinner_enabled = 0;
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
  else {
    char ledset = 0;
    int i;
    for(i=0; i < get_numSV(); i++) { //convert binary number into one-hot count
      ledset<<=1;
      ledset|=1;
    }
    PORTE=ledset;
  }
}

_Bool spinner_status(void) {
  return spinner_enabled;
}
