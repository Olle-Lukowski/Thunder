#include "math.h"

double my_floor(double x) {
  double integer_part = (double)(long long)x;
  if (x < 0 && x != integer_part) {
    return integer_part - 1.0;
  } else {
    return integer_part;
  }
}
