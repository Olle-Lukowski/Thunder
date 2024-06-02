#ifndef TH_C_LIMITS_H_
#define TH_C_LIMITS_H_

/* 
 * For now, all of these are the miminum the spec requires. 
 * TODO: Make it properly detected on different platforms.
 */

#define CHAR_BIT 8
#define SCHAR_MIN -128
#define SCHAR_MAX 127
#define UCHAR_MAX 255

#if '\xff' > 0
#define CHAR_MIN 0
#define CHAR_MAX 255
#else
#define CHAR_MIN (-128)
#define CHAR_MAX 127
#endif

#define MB_LEN_MAX 4 /* TODO: Check this */

#define SHRT_MIN -32768
#define SHRT_MAX 32767
#define USHRT_MAX 65535

#define INT_MIN -32768
#define INT_MAX 32767
#define UINT_MAX 65535

#define LONG_MIN -2147483648
#define LONG_MAX 2147483647
#define ULONG_MAX 4294967295

#endif /* TH_C_LIMITS_H_ */
