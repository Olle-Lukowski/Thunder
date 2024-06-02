#include "src/c/src/errno.c"
#include "src/c/src/math/exp.c"
#include "src/c/src/math/pow.c"
#include "src/c/src/math/sqrt.c"
#include "src/c/src/math/acos.c"
#include "src/c/src/math/asin.c"
#include "src/c/src/math/atan.c"
#include "src/c/src/math/atan2.c"
#include "src/c/src/math/fabs.c"
#include "src/c/src/math/fmod.c"
#include "src/c/src/math/floor.c"
#include "src/c/src/math/cos.c"
#include "src/c/src/math/cosh.c"
#include "src/c/src/math/sin.c"
#include "src/c/src/math/sinh.c"
#include "src/c/src/math/tan.c"
#include "src/c/src/math/tanh.c"
#include "src/c/src/math/log.c"
#include "src/c/src/math/log10.c"
#include "stdarg.h"

void log_wrapper(int count, ...) {
  va_list args;
  va_start(args, count);

  int i;
  for (i = 0; i < count; ++i) {
    double x = my_log(va_arg(args, double));
  }

  va_end(args);
}

void _start() {
  double x = 1.0, y = 2.0, z = 3.0;
  log_wrapper(3, x, y, z);
}
