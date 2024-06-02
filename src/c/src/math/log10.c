#include "math.h"

#include "float.h"
#include "errno.h"

double my_log10(double x) {
  if (x <= 0) {
    errno = EDOM;
    double zero = 0.0;
    return zero / zero; /* NaN */
  } 

  return my_log(x) / my_log(10);
}
