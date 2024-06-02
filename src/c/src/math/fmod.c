#include "math.h"

double my_fmod(double x, double y) {
  return x - y * my_floor(x / y);
}
