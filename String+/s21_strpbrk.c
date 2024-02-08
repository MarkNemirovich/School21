#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *fp = s21_NULL;
  // go ti the end of 1st string till match
  for (s21_size_t i = 0; *str1 != '\0' && *fp == s21_NULL; str1++, i++) {
  // go ti the end of 2nd string till match
    for (const char *s = str2; *s != '\0' && *fp == s21_NULL; s++) {
      // match
        if (*str1 == s) {
          fp = str1;
        }
    }
  }
  return fp;
}