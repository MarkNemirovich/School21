#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  char *buff = (char *)str; // convert bytes to chars
  for (s21_size_t i = 0; i < n; i++) { // (unprotected as base func)
    buff[i] = c; // just change symbol :)
  }
  return str;
}