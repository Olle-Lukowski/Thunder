#include "math.h"

#include "float.h"
#include "errno.h"

#include "common.h"

double my_atan(double x) {
  if (my_fabs(x) > 1) {
    return (x > 0 ? PI / 2 : -PI / 2) - my_atan(1 / x);
  }

  double result = 0.0;
  double term = x;
  double x_squared = x * x;
  double numerator = x;
  double denominator = 1;
  int i = 1;

  while (my_fabs(term) > (x * DBL_EPSILON)) {
    result += term;
    numerator *= -x_squared;
    denominator = 2 * i + 1;
    term = numerator / denominator;
    ++i;
  }

  return result;
}
