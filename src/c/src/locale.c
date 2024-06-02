#include "locale.h"

#include "limits.h"

static struct lconv c_lconv = {
  ".",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX,
};

char *setlocale(int category, const char *locale) {
  return locale ? NULL : "C"; /* We only support the "C" locale. */
}

struct lconv *localeconv(void) {
  return &c_lconv;
}
