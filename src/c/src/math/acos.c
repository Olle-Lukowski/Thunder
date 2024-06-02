#include "math.h"

#include "errno.h"

#include "common.h"

double my_acos(double x) {
  if (x >= -1 && x <= 1) {
    return PI / 2 - my_asin(x);
  } else {
    errno = EDOM;
    double zero = 0.0;
    return zero / zero; /* NaN */
  }
}
