#include "math.h"

#include "float.h"

double my_cos(double x) {
  double result = 1;
  double term = 1;
  double x_squared = x * x;
  int i = 2;

  while (my_fabs(term) > DBL_EPSILON) {
    term *= -x_squared / (i * (i - 1));
    result += term;
    i += 2;
  }

  return result;
}
