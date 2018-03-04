#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "mipslab.h"  /* Declatations for these labs */
//methods for storing, processing, and accessing gps data

//macro for defining variables
#define DEFINEGPSVAR(TYPE, VAR) TYPE VAR = 0;

/*shared variables*/
DEFINEGPSVAR(uint32_t, iTOW) //GPS time of week (milliseconds)

//macro for pulling data out of payload
#define EXTRACT(TYPE, VAR, OFFSET) VAR = *((TYPE*)(payload+OFFSET));

/*UBX-NAV-PVT ""*/
//unique variables
DEFINEGPSVAR(uint16_t, year) //current UTC year (years)
DEFINEGPSVAR(uint8_t, month) //current UTC month (months)
DEFINEGPSVAR(uint8_t, day) //current UTC day of the month (days)
DEFINEGPSVAR(uint8_t, hour) //current UTC hour of the day (hours)
DEFINEGPSVAR(uint8_t, min) //current UTC minute of the hour (minutes)
DEFINEGPSVAR(uint8_t, sec) //current UTC second of the minute (seconds)
DEFINEGPSVAR(_Bool, validDate)
DEFINEGPSVAR(_Bool, validTime)
DEFINEGPSVAR(_Bool, fullyResolved) // true if all UTC time fields are known
DEFINEGPSVAR(uint32_t, tAcc) //time accuracy estimate (±nanoseconds)
DEFINEGPSVAR(int32_t, nano) //current UTC nanosecond (nanoseconds)

// payload storer
void store_nav_pvt_payload(uint8_t* payload) {
  EXTRACT(uint32_t, iTOW, 0)
  EXTRACT(uint16_t, year, 4)
  EXTRACT(uint8_t, month, 6)
  EXTRACT(uint8_t, day, 7)
  EXTRACT(uint8_t, hour, 8)
  EXTRACT(uint8_t, min, 9)
  EXTRACT(uint8_t, sec, 10)

  int valid = *((uint8_t*)(payload+11));
  validDate = valid & 0x1;
  validTime = valid & 0x2;
  fullyResolved = valid & 0x4;

  EXTRACT(uint32_t, tAcc, 12)
  EXTRACT(int32_t, nano, 16)
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
