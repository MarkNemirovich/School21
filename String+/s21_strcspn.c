#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t match = 0;
  for (s21_size_t i = 0; *str1 != '\0' && !match;
       str1++, i++) {  // go to the end of the 1st string till find symbol
    for (const char *s = str2; *s != '\0' && !match;
         s++) {  // go to the end of the 2nd string till find symbol
      if (*str1 == s) {
        match = i;  // get index of the 1st string :)
      }
    }
  }
  return match;
}