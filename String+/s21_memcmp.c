#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  // convert bytes to chars
  char *buff1 = (char *)str1;
  char *buff2 = (char *)str2;
  int result = 0;
  // go till end of string or find different symbols
  for (s21_size_t i = 0; i < n && !result; i++) {
    // compare ascii codes (65- 32 for example)
    if (buff1[i] != buff2[i]) {
      result = buff1[i] - buff2[i];
    }
  }
  return result;
}