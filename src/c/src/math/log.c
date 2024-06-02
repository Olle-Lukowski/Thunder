#include "math.h"

#include "float.h"
#include "errno.h"

#include "common.h"

double my_log(double x) {
  if (x <= 0) {
    errno = EDOM;
    double zero = 0.0;
    return zero / zero; /* NaN */
  }

  double result = 0;
  double term = (x - 1) / (x + 1);
  double power = term;
  int n = 1;

  while (my_fabs(power / n) > DBL_EPSILON) {
    result += power / n;
    power *= term * term;
    n += 2;
  }

  return 2 * result;
}
