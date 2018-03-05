#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "mipslab.h"  /* Declatations for these labs */
//methods for storing, processing, and accessing gps data

//macro for defining variables
#define DEFINEGPSVAR(TYPE, VAR) TYPE VAR = 0;

/*shared variables*/
DEFINEGPSVAR(uint32_t, iTOW) //GPS time of week (milliseconds)

//macro for pulling data out of payload
#define EXTRACT(TYPE, VAR, OFFSET) VAR = *((TYPE*)(payload+OFFSET));

/*UBX-NAV-PVT "Navigation Position, Velocity, and Time Solution"*/
//unique variables
DEFINEGPSVAR(uint16_t, year) //current UTC year (years)
DEFINEGPSVAR(uint8_t, month) //current UTC month (months)
DEFINEGPSVAR(uint8_t, day) //current UTC day of the month (days)
DEFINEGPSVAR(uint8_t, hour) //current UTC hour of the day (hours)
DEFINEGPSVAR(uint8_t, min) //current UTC minute of the hour (minutes)
DEFINEGPSVAR(uint8_t, sec) //current UTC second of the minute (seconds)
DEFINEGPSVAR(_Bool, validDate) //date fields have data (may not be accurate)
DEFINEGPSVAR(_Bool, validTime) //time fields have data (may not be accurate)
DEFINEGPSVAR(_Bool, fullyResolved) // true if all UTC time fields are known
DEFINEGPSVAR(uint32_t, tAcc) //time accuracy estimate (±nanoseconds)
DEFINEGPSVAR(int32_t, nano) //current UTC nanosecond (nanoseconds)
DEFINEGPSVAR(uint8_t, fixType) //current status of our GPS Lock
//(0: no fix, 1: dead reckoning, 2: 2D fix, 3: 3D fix, 4: (not used on ours), 5: time only fix
DEFINEGPSVAR(uint8_t, numSV) //number of satellites used for data
DEFINEGPSVAR(int32_t, lon) //longitude (fixed point number, LSB is 1e-7)
DEFINEGPSVAR(int32_t, lat) //latitude (fixed point number, LSB is 1e-7)
DEFINEGPSVAR(int32_t, hMSL) //height above sea level (millimeters)
DEFINEGPSVAR(uint32_t, hAcc) //horizontal accuracy estimate (±millimeters)
DEFINEGPSVAR(uint32_t, vAcc) //vertical accuracy estimate (±millimeters)
DEFINEGPSVAR(int32_t, gSpeed) //ground speed (millimeters/second)
DEFINEGPSVAR(int32_t, headMot) //heading of motion (degrees, LSB is 1E-5)

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
  EXTRACT(uint8_t, fixType, 20)
  EXTRACT(uint8_t, numSV, 23)
  EXTRACT(int32_t, lon, 24)
  EXTRACT(int32_t, lat, 28)
  EXTRACT(int32_t, hMSL, 36)
  EXTRACT(uint32_t, hAcc, 40)
  EXTRACT(uint32_t, vAcc, 44)
  EXTRACT(int32_t, gSpeed, 60)
  EXTRACT(int32_t, headMot, 64)
}


/*UBX-NAV-POSECEF "Position Solution in ECEF"*/
//unique variables
DEFINEGPSVAR(int32_t, ecefX) //(centimeters)
DEFINEGPSVAR(int32_t, ecefY) //(centimeters)
DEFINEGPSVAR(int32_t, ecefZ) //(centimeters)
DEFINEGPSVAR(uint32_t, pAcc) //(±centimeters)

// payload storer
void store_nav_posecef_payload(uint8_t* payload) {
  EXTRACT(int32_t, ecefX, 4)
  EXTRACT(int32_t, ecefY, 8)
  EXTRACT(int32_t, ecefZ, 12)
  EXTRACT(uint32_t, pAcc, 16)
}


/*getters*/

//macro used to define getters
#define GETTER(TYPE, VAR) TYPE get_##VAR() { return VAR; }

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
GETTER(uint8_t, fixType)
GETTER(uint8_t, numSV)
GETTER(int32_t, lon)
GETTER(int32_t, lat)
GETTER(int32_t, hMSL)
GETTER(uint32_t, hAcc)
GETTER(uint32_t, vAcc)
GETTER(int32_t, gSpeed)
GETTER(int32_t, headMot)

GETTER(int32_t, ecefX)
GETTER(int32_t, ecefY)
GETTER(int32_t, ecefZ)
GETTER(uint32_t, pAcc)
