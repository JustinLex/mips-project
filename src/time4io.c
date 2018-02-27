#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

volatile uint32_t* reg_portd = 0xbf8860d0; //Input register

int getsw(void)
{
  return ((*reg_portd & 0xf00)>>8); // return SW4-SW1 values as 4 least significant bits
}

int getbtns(void)
{
  return ((*reg_portd & 0xe0)>>5); // return BTN4-BTN2 values as 3 least significant bits
}
