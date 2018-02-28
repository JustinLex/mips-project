#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "mipslab.h"  /* Declatations for these labs */
//methods for storing, processing, and accessing gps data


/*UBX-NAV-CLOCK "Clock Solution"*/
//variables
uint32_t nav_clock_iTOW = 0; //GPS time of week (milliseconds)
int32_t nav_clock_clkB = 0; //clock bias (nanoseconds)
int32_t nav_clock_clkD = 0; //clock drift (nanoseconds/second)
uint32_t nav_clock_tAcc = 0; //Time accuracy estimate (nanoseconds)
uint32_t nav_clock_fAcc = 0; //Frequency accuracy estimate (picoseconds/second)
//storing
void store_nav_clock_payload(uint8_t* payload) {
  nav_clock_iTOW = *((uint32_t*)payload);
  nav_clock_clkB = *((int32_t*)(payload+4));
  nav_clock_clkD = *((int32_t*)(payload+8));
  nav_clock_tAcc = *((uint32_t*)(payload+12));
  nav_clock_fAcc = *((uint32_t*)(payload+16));
}
//retrieving
uint32_t* get_nav_clock_iTOW() {
  return &nav_clock_iTOW;
}
int32_t* get_nav_clock_clkB() {
  return &nav_clock_clkB;
}
int32_t* get_nav_clock_clkD() {
  return &nav_clock_clkD;
}
uint32_t* get_nav_clock_tAcc() {
  return &nav_clock_tAcc;
}
uint32_t* get_nav_clock_fAcc() {
  return &nav_clock_fAcc;
}
