#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <math.h> /*Declarations of sin,cos and so on*/

//functions for handling ecef data

//XYZ coords of Kistan, in cm
#define KISTAN_X 309597600
#define KISTAN_X 100301600
#define KISTAN_X 546711700

//returns the distance to kistan, takes centimeters, returns meters
uint32_t distance_to_kistan(uint32_t x, uint32_t y, uint32_t z) {
  int32_t x_diff = KISTAN_X - x;
  int32_t y_diff = KISTAN_Y - y;
  int32_t z_diff = KISTAN_Z - z;
  uint32_t dist_squared = ((x_diff * x_diff) + (y_diff * y_diff) + (z_diff * z_diff)) / 100 //technically this could overflow?
  return (uint32_t) (sqrt(dist_squared))
}
