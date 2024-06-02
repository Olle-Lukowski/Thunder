#ifndef TH_C_FLOAT_H_
#define TH_C_FLOAT_H_

/*
 * For now, this file assumes the target uses IEEE 754.
 * If that is not the case for your target, please open an issue.
 */

#define FLT_RADIX                         2
#define FLT_ROUNDS                     (-1) /* Not known, I think. */

/* https://en.wikipedia.org/wiki/Single-precision_floating-point_format */
#define FLT_MANT_DIG                     24
#define FLT_DIG                           6
#define FLT_MIN_EXP                  (-125)
#define FLT_MIN_10_EXP                (-37)
#define FLT_MAX_EXP                     128
#define FLT_MAX_10_EXP                   38
#define FLT_MAX 3.40282346638528859812e+38F
#define FLT_EPSILON 1.1920928955078125e-07F
#define FLT_MIN 1.17549435082228750787e-38F

/* https://en.wikipedia.org/wiki/Double-precision_floating-point_format */
#define DBL_MANT_DIG                     53
#define DBL_DIG                          15
#define DBL_MIN_EXP                 (-1021)
#define DBL_MIN_10_EXP               (-307)
#define DBL_MAX_EXP                    1024
#define DBL_MAX_10_EXP                  308
#if defined(_MSC_VER) || defined(__clang__)
#define DBL_MAX  1.7976931348623157081e+308
#define DBL_EPSILON  2.220446049250313e-016
#define DBL_MIN  2.2250738585072013831e-308
#elif defined(__GNUC__)
#define DBL_MAX 1.7976931348623157081e+308D
#define DBL_EPSILON 2.220446049250313e-016D
#define DBL_MIN 2.2250738585072013831e-308D
#endif

/* 
 * For now, we don't support quad-precision. 
 * So we just assume long double is the same as double. 
 */
#define LDBL_MANT_DIG          DBL_MANT_DIG
#define LDBL_DIG                    DBL_DIG
#define LDBL_MIN_EXP            DBL_MIN_EXP
#define LDBL_MIN_10_EXP      DBL_MIN_10_EXP
#define LDBL_MAX_EXP            DBL_MAX_EXP
#define LDBL_MAX_10_EXP      DBL_MAX_10_EXP
#define LDBL_MAX                    DBL_MAX
#define LDBL_EPSILON            DBL_EPSILON
#define LDBL_MIN                    DBL_MIN

#endif /* TH_C_FLOAT_H_ */
