#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "mipslab.h"  /* Declatations for these labs */
//methods for storing, processing, and accessing gps data


/*shared variables*/
uint32_t iTOW = 0; //GPS time of week (milliseconds)

/*UBX-NAV-CLOCK "Clock Solution"*/
//unique variables
uint16_t year = 0; //current UTC year (years)
uint8_t month = 0; //current UTC month (months)
uint8_t day = 0; //current UTC day of the month (days)
uint8_t hour = 0; //current UTC hour of the day (hours)
uint8_t min = 0; //current UTC minute of the hour (minutes)
uint8_t sec = 0; //current UTC second of the minute (seconds)
_Bool validDate = 0;
_Bool validTime = 0;
_Bool fullyResolved = 0; // true if all UTC time fields are known
uint32_t tAcc = 0; //time accuracy estimate (±nanoseconds)
int32_t nano = 0; //current UTC nanosecond (nanoseconds)

// payload storer
void store_nav_clock_payload(uint8_t* payload) {
  iTOW = *((uint32_t*)(payload+0));
  year = *((uint16_t*)(payload+4));
  month = *((uint8_t*)(payload+6));
  day = *((uint8_t*)(payload+7));
  hour = *((uint8_t*)(payload+8));
  min = *((uint8_t*)(payload+9));
  sec = *((uint8_t*)(payload+10));

  int valid = *((uint8_t*)(payload+11));
  validDate = valid & 0x1;
  validTime = valid & 0x2;
  fullyResolved = valid & 0x4;

  tAcc = *((uint32_t*)(payload+12));
  nano = *((int32_t*)(payload+16));
}

/*getters*/

//macro used to define getters
#define getter(type, var) \
  type* get_var() { \
    return &var; \
  }

//create getter functions with macro
getter(uint32_t, iTOW)
getter(uint16_t, year)
getter(uint8_t, month)
getter(uint8_t, day)
getter(uint8_t, hour)
getter(uint8_t, min)
getter(uint8_t, sec)
getter(_Bool, validDate)
getter(_Bool, validTime)
getter(_Bool, fullyResolved)
getter(uint32_t, tAcc)
getter(int32_t, nano)


/*uint32_t* get_iTOW() {
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
}*/
