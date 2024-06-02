#include "math.h"

double my_pow(double x, double y) {
  double result = 1;
  int i;

  for (i = 0; i < y; i++) {
    result *= x;
  }

  return result;
}
