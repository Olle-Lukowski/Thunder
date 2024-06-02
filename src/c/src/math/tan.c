#include "math.h"

#include "common.h"
#include "float.h"
#include "errno.h"

double my_tan(double x) {
  x = my_fmod(x, PI);

  double cos_x = my_cos(x);

  if (my_fabs(cos_x) < DBL_EPSILON) {
    errno = EDOM;
    return cos_x > 0 ? HUGE_VAL : -HUGE_VAL;
  }

  return my_sin(x) / cos_x;
}
