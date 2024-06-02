#include "math.h"

#include "float.h"
#include "errno.h"

/*
 * We are using a very basic version here,
 * for ultimate compatibility. Eventually we will have a bunch
 * of platform-specific versions, and this will be the fallback.
 */ 
double my_sqrt(double x) {
  if (x < 0) {
    errno = EDOM;
    double zero = 0.0;
    return zero / zero; /* NaN */
  }

  if (x == 0 || x == 1) {
    return x;
  }

  double guess = x / 2.0;

  while (my_fabs(guess * guess - x) > (x * DBL_EPSILON)) {
    guess = 0.5 * (guess + x / guess);
  }

  return guess;
}

