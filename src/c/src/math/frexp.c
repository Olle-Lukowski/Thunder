#include "math.h"

double my_frexp(double value, int *exp) {
    *exp = 0;
    while (my_fabs(value) >= 1.0) {
        value /= 2.0;
        (*exp)++;
    }
    while (my_fabs(value) < 0.5) {
        value *= 2.0;
        (*exp)--;
    }
    return value;
}
