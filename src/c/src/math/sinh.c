#include "math.h"

#include "float.h"

double my_sinh(double x) {
  double result = x;
  double term = x;
  double x_squared = x * x;
  int i = 3;

  while (my_fabs(term) > DBL_EPSILON) {
    term *= x_squared / (i * (i - 1));
    result += term;
    i += 2;
  }

  return result;
}