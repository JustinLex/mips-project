#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */

//functions for presenting data to the user
int page=1; //variable for current page

void display_page(void) //put data to the textbuffer according to the page
{
  switch (page)
  {
    case 1:
    {
      int hej = 10;
      display_debug(&hej);
      break;
    }
    case 2:
    {
      int hejj = 11;
      display_debug(&hejj);
      break;
    }
    case 3:
    {
      int hj = 12;
      display_debug(&hj);
      break;
    }
    case 4:
    {
      int heej = 13;
      display_debug(&heej);
      break;
    }
  }
}


void page_switch(void)
{
  {
    if(getbtns() & 0x4)
      {
        if(page==1)
        page=4;
        else
        page--;
      }
      if(getbtns() & 0x2)
      {
        if(page==4)
        page=1;
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
