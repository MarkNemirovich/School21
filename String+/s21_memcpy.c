#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  // convert bytes to chars
  char *buff = (char *)src; 
  char *result = (char *)dest;
  // count how much elements left to copy (unprotected as base func)
  while (n-- > 0) { 
    *result++ = *buff++;
  }
  return dest;
}