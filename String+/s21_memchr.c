#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  // convert bytes to chars
  const unsigned char *buff = (const unsigned char *)str;
  void *out = s21_NULL;
  // go till end of string or find
  for (s21_size_t i = 0; i < n && out == s21_NULL; i++) {
    if (buff[i] == c) {
      // convert char to byte
      out = (void *)&buff[i];
    }
  }
  return out;
}