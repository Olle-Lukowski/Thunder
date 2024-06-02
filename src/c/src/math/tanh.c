#include "math.h"

#include "float.h"

double my_tanh(double x) {
  double exp_2x = my_exp(2 * x);
  double exp_neg_2x = my_exp(-2 * x);

  return (exp_2x - exp_neg_2x) / (exp_2x + exp_neg_2x);
}