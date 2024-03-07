#include "s21_string.h"

void s21_read_size(char **format, flag *flags) {
  if (**format == 'h') {
    flags->shorter = 1;
    (*format)++;
  } else if (**format == 'l') {
    flags->longer = 1;
    (*format)++;
    if (**format == 'l') {
      flags->longer = 0;
      flags->longest = 1;
      (*format)++;
    }
  } else if (**format == 'L') {
    flags->longest = 1;
    (*format)++;
  }
}

s21_size_t s21_get_num(char **n, int width, int *error) {
  s21_size_t num = 0;
  int sign = s21_get_sign(n, &width);
  *error = 1;
  for (; **n >= '0' && **n <= '9' && width > 0; (*n)++, width--) {
    if (*error) *error = 0;
    num *= 10;
    num += (**n - '0');
  }
  return num * sign;
}

int s21_get_sign(char **n, int *width) {
  int sign = 1;
  if (*width == 0) {
    *width = INT_MAX;
  }
  if (**n == '-') {
    sign = -1;
    (*n)++;
    (*width)--;
  }
  else if (**n == ' ' || **n == '+') {
    sign = 1;
    (*n)++;
    (*width)--;
  }
  return sign;
}
