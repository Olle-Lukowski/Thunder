#ifndef TH_C_ASSERT_H_
#define TH_C_ASSERT_H_

#ifdef NDEBUG
#define assert(ignore) ((void)0)
#else
#define assert(x) ((x) ? ((void)0) : (__assert_fail(#x, __FILE__, __LINE__), (void)0))
#endif

void __assert_fail(const char *expr, const char *file, unsigned int line);

#endif /* TH_C_ASSERT_H_ */
