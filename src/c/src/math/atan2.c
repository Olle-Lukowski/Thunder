#include "math.h"

#include "errno.h"

#include "common.h"

double my_atan2(double y, double x) {
  if (x > 0) {
    return my_atan(y / x);
  } else if (x < 0 && y >= 0) {
    return my_atan(y / x) + PI;
  } else if (x < 0 && y < 0) {
    return my_atan(y / x) - PI;
  } else if (x == 0 && y > 0) {
    return PI / 2;
  } else if (x == 0 && y < 0) {
    return -PI / 2;
  } else {
    errno = EDOM;
    double zero = 0.0;
    return zero / zero; /* NaN */
  }
}
