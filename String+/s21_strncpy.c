#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *res = dest;
  // copy n elements (unprotected as base func)
  for (; n > 0; n--, dest++) {
    // if string 2 is
    if (*src != '\0') {
      *dest = *src;
      src++;
      // fill by empty (null) symbols
    } else {
      *dest = '\0';
    }
  }
  return res;
}