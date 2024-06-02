#include "math.h"

double my_ldexp(double x, int exp) {
    return x * my_pow(2, exp);
}
