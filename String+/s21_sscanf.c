#include <string.h>  // temprorarys delete after finish!!!

#include "s21_string.h"

s21_size_t get_num(char **format) {
  s21_size_t num = 0;
  int sign = 1;
  if (**format == '-') {
    sign = -1;
    (*format)++;
  }
  for (; **format >= '0' && **format <= '9'; (*format)++) {
    num *= 10;
    num += (**format - '0');
  }
  return num * sign;
}

s21_size_t get_o_num(char **format) {
  s21_size_t num = 0;
  int sign = 1;
  if (**format == '-') {
    sign = -1;
    (*format)++;
  }
  for (; **format >= '0' && **format <= '7'; (*format)++) {
    num *= 8;
    num += (**format - '0');
  }
  return num * sign;
}

s21_size_t get_x_num(char **format) {
  s21_size_t num = 0;
  int sign = 1;
  if (**format == '-') {
    sign = -1;
    (*format)++;
  }
  for (;
       **format >= '0' && **format <= '9' ||
       **format >= 'a' && **format <= 'f' || **format >= 'A' && **format <= 'F';
       (*format)++) {
    num *= 16;
    if (**format >= '0' && **format <= '9') num += (**format - '0');
    if (**format >= 'a' && **format <= 'f') num += (**format - 'a') + 10;
    if (**format >= 'A' && **format <= 'F') num += (**format - 'A') + 10;
  }
  return num * sign;
}

float get_double_num(char **format) {
  float num = 0.0;
  int sign = 1;
  if (**format == '-') {  // Определяем знак числа
    sign = -1;
    (*format)++;
  }
  // Читаем целую часть числа
  while (**format >= '0' && **format <= '9') {
    num = num * 10.0 + (**format - '0');
    (*format)++;
  }
  // Обрабатываем дробную часть числа
  if (**format == '.') {
    (*format)++;
    float fraction = 0.0;
    float fraction_power = 0.1;  // Для умножения на десятичные разряды
    while (**format >= '0' && **format <= '9') {
      fraction += (**format - '0') * fraction_power;
      fraction_power *= 0.1;
      (*format)++;
    }
    num += fraction;
  }
  // Обрабатываем экспоненту
  if (**format == 'e' || **format == 'E') {
    (*format)++;
    int exponent_sign = 1;
    if (**format == '-') exponent_sign = -1;
    (*format)++;
    int exponent = 0;
    while (**format >= '0' && **format <= '9') {
      exponent = exponent * 10 + (**format - '0');
      (*format)++;
    }
    num *= pow(10, exponent * exponent_sign);
  }
  return num * sign;
}

void read_flags(char **format, va_list list, flag *flags) {
  if (**format == '*') {
    flags->width = va_arg(list, int);
    (*format)++;
  } else if (**format >= '0' && **format <= '9') {
    flags->width = get_num(format);
  }
}

void read_size(const char *format, flag *flags) {
  if (*format == 'h') {
    flags->shorter = 1;
    format++;
  } else if (*format == 'l') {
    flags->longer = 1;
    format++;
    if (*format == 'l') {
      flags->longer = 0;
      flags->longest = 1;
      format++;
    }
  } else if (*format == 'L') {
    flags->longest = 1;
    format++;
  }
}

int parse_c(char **str, va_list list, flag flags) {
  int error = 0;
  char *ch = va_arg(list, char *);
  *ch = **str;
  *str += 1;
  return error;
}

int parse_s(char **str, va_list list, flag flags) {
  int error = 0;
  char *result = va_arg(list, char *);
  char *len = s21_strpbrk(*str, " \t\n\0");
  int size = len - *str;
  for (; size > 0; size--, result++, *str += 1) {
    *result = **str;
  }
  *result = '\0';
  return error;
}

int parse_d(char **str, va_list list, flag flags) {
  int error = 0;
  long long int *num = va_arg(list, long long int *);
  *num = (long long int)get_num(str);
  return error;
}

int parse_u(char **str, va_list list, flag flags) {
  int error = 0;
  long long unsigned *num = va_arg(list, long long unsigned int *);
  *num = (long long unsigned)get_num(str);
  return error;
}

int parse_x(char **str, va_list list, flag flags) {
  int error = 0;
  long long int *num = va_arg(list, long long int *);
  *num = (long long int)get_x_num(str);
  return error;
}

int parse_o(char **str, va_list list, flag flags) {
  int error = 0;
  long long int *num = va_arg(list, long long int *);
  *num = (long long int)get_o_num(str);
  return error;
}

int parse_f(char **str, va_list list, flag flags) {
  int error = 0;
  float *num = va_arg(list, float *);
  *num = (float)get_double_num(str);
  return error;
}

int parse_p(char **str, va_list list, flag flags) {
  int error = 0;
  long long unsigned int *p = va_arg(list, long long unsigned int *);
  *str += 2; // 0x
  *p = get_x_num(str);
  *str += 1;
  return error;
}

int read_types(char **str, va_list list, const char *format, flag flags) {
  int error = 0;
  switch (*format) {
    case 'c':
      parse_c(str, list, flags);
      break;
    case 's':
      parse_s(str, list, flags);
      break;
    case 'd':
      parse_d(str, list, flags);
      break;
    case 'u':
      parse_u(str, list, flags);
      break;
    case 'x':
    case 'X':
      parse_x(str, list, flags);
      break;
    case 'o':
      parse_o(str, list, flags);
      break;
    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
      parse_f(str, list, flags);
      break;
    case 'p':
      parse_p(str, list, flags);
      break;
    case '%':
      *str -= 1;
      break;
    default:
      error = 1;
      break;
  }
  format++;
  *str += 1;
  return error;
}

int s21_sscanf(const char *str, const char *format, ...) {
  va_list list;
  va_start(list, format);
  flag flags = {0};
  int error = 0;
  while (!error && *str != '\0' && *format != 0) {
    if (*format++ == '%') {
      flags = (flag){0};
      read_flags((char **)&format, list, &flags);
      read_size(format, &flags);
      error = read_types((char **)&str, list, format, flags);
    }
  }
  va_end(list);
  return 0;
}

int main() {
  char i, you, percent;
  int day, year, oct, hex, HEX;
  float a, b, c, d, e, f;
  char at[5], weekday[5], month[5], strings[100], integers[100], fractals[100];
  strcpy(strings, "I at Saturday March ! 25 1989 -40 F aBc");
  strcpy(integers, "25 1989 -40 F aBc");
  strcpy(fractals, "25.1989 -40.5 7e02 9e-02 1.2e+12 4e+102");

  s21_sscanf(strings, "%c %s %s %s %c %%", &i, at, weekday, month, &you);
  printf("MY:     \t%c \t%s \t%s \t%s \t%c \t%%\n", i, at, weekday, month, you);

  sscanf(strings, "%c %s %s %s %c %%", &i, at, weekday, month, &you);
  printf("BASE:   \t%c \t%s \t%s \t%s \t%c \t%%\n", i, at, weekday, month, you);

  s21_sscanf(integers, "%d %u %o %x %X", &day, &year, &oct, &hex, &HEX);
  printf("MY:   \t%d \t%u \t%o \t%x \t%X\n", day, year, oct, hex, HEX);
  sscanf(integers, "%d %u %o %x %X", &day, &year, &oct, &hex, &HEX);
  printf("BASE: \t%d \t%u \t%o \t%x \t%X\n", day, year, oct, hex, HEX);

  s21_sscanf(fractals, "%f %f %e %E %g %G", &a, &b, &c, &d, &e, &f);
  printf("MY:   \t%f \t%f \t%e \t%E \t%g \t%G\n", a, b, c, d, e, f);

  sscanf(fractals, "%f %f %e %E %g %G", &a, &b, &c, &d, &e, &f);
  printf("BASE: \t%f \t%f \t%e \t%E \t%g \t%G\n", a, b, c, d, e, f);

  return (0);
}