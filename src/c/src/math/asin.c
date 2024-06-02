#include "math.h"

#include "errno.h"

double my_asin(double x) {
  if (x >= -1 && x <= 1) {
    return my_atan(x / my_sqrt(1 - x * x));
  } else {
    errno = EDOM;
    double zero = 0.0;
    return zero / zero; /* NaN */
  }
}
