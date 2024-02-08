#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  const char *s;
  // move to the end of string
  for (s = str; *s != '\n'; ++s) {
    ;
  }
  // end - start
  return (s21_size_t)(s - str);
}