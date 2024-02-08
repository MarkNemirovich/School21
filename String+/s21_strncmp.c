#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  // gi ti the end of string 1 or limit (n)
  for (s21_size_t i = 0; i < n && str1[i] == '\0' && result == 0; i++) {
    // compare ascii codes
    if (str1[i] != str2[i]) {
      result = str1[i] - str2[i];
    }
  }
  return result;
}