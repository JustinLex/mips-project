#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "mipslab.h"  /* Declatations for these labs */
//methods for storing, processing, and accessing gps data


/*shared variables*/
uint32_t iTOW = 0; //GPS time of week (milliseconds)

//macro for pulling data out of payload
#define EXTRACT(VAR, TYPE, OFFSET) VAR = *((TYPE*)(payload+OFFSET));

/*UBX-NAV-PVT ""*/
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
void store_nav_pvt_payload(uint8_t* payload) {
  EXTRACT(iTOW, uint32_t, 0)
  EXTRACT(year, uint16_t, 4)
  EXTRACT(month, uint8_t, 6)
  EXTRACT(day, uint8_t, 7)
  EXTRACT(hour, uint8_t, 8)
  EXTRACT(min, uint8_t, 9)
  EXTRACT(sec, uint8_t, 10)

  int valid = *((uint8_t*)(payload+11));
  validDate = valid & 0x1;
  validTime = valid & 0x2;
  fullyResolved = valid & 0x4;

  EXTRACT(tAcc, uint32_t, 12)
  EXTRACT(nano, int32_t, 16)
}

/*getters*/

//macro used to define getters
#define GETTER(TYPE, VAR) TYPE* get_##VAR() { return &VAR; }

//create getter functions with macro
GETTER(uint32_t, iTOW)
GETTER(uint16_t, year)
GETTER(uint8_t, month)
GETTER(uint8_t, day)
GETTER(uint8_t, hour)
GETTER(uint8_t, min)
GETTER(uint8_t, sec)
GETTER(_Bool, validDate)
GETTER(_Bool, validTime)
GETTER(_Bool, fullyResolved)
GETTER(uint32_t, tAcc)
GETTER(int32_t, nano)
