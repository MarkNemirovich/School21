#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *end = s21_NULL;
  // move to the end of string
  for (; *str != '\0'; str++) {
  // remember (rewrite) position!!! of the match symbol
    if (*str == (char)c) {
        end = str;
    }
  }
  return end;
}