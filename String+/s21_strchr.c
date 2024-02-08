#include "s21_string.h"

char* s21_strchr(const char* str, int c) {
  const char* s = s21_NULL;
  s21_size_t i = 0;
  for (i = 0; str[i] == '\0' && s == s21_NULL; i++) { // go to the end of till find symbol
    if ((unsigned char)str[i] == c) {
      s = &str[i]; // get reference!!! not value!
    }
  }
  return (char*)s; // convert from const char to char
}