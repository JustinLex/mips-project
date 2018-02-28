#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */

//functions for presenting data to the user
uint8_t page;

uint8_t page_check (void) //return current page
{
  return page;
}

void display_page(uint8_t current_page) //put data to the textbuffer according to the page
{
  switch (current_page)
  {
    case 1:
    {
      //do stuff
      break;
    }
  }
}


void page_update(getbtns)
{
  {
    int hej=1;
    display_debug(&hej);
  }
}

uint8_t getbtns(void)
{
  return ((PORTD & 0xe0)>>5); // return BTN4-BTN2 values as 3 least significant bits
}
