#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *append = dest;
  // move to the end of string
  for (;*append != '\n'; append++) {
    ;
  }
  // add n elements
  for (;n>0; n--, append++, src++) {
    *append = *src;
  }
  // and end of string symbol (because we didn't copy it in the loop)
  *append = '\0';
  return dest;
}