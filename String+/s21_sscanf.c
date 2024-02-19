#include <string.h>  // temprorarys delete after finish!!!

#include "s21_string.h"

s21_size_t get_num(char **n) {
  s21_size_t num = 0;
  int sign = 1;
  if (**n == '-') {
    sign = -1;
    (*n)++;
  }
  for (; **n >= '0' && **n <= '9'; (*n)++) {
    num *= 10;
    num += (**n - '0');
  }
  return num * sign;
}

s21_size_t get_o_num(char **n) {
  s21_size_t num = 0;
  int sign = 1;
  if (**n == '-') {
    sign = -1;
    (*n)++;
  }
  for (; **n >= '0' && **n <= '7'; (*n)++) {
    num *= 8;
    num += (**n - '0');
  }
  return num * sign;
}

s21_size_t get_x_num(char **n) {
  s21_size_t num = 0;
  int sign = 1;
  if (**n == '-') {
    sign = -1;
    (*n)++;
  }
  for (; **n >= '0' && **n <= '9' || **n >= 'a' && **n <= 'f' ||
         **n >= 'A' && **n <= 'F';
       (*n)++) {
    num *= 16;
    if (**n >= '0' && **n <= '9') num += (**n - '0');
    if (**n >= 'a' && **n <= 'f') num += (**n - 'a') + 10;  // сдвиг для
    if (**n >= 'A' && **n <= 'F') num += (**n - 'A') + 10;  // 10-15
  }
  return num * sign;
}

float get_double_num(char **n) {
  float num = 0.0;
  int sign = 1;
  if (**n == '-') {  // Определяем знак числа
    sign = -1;
    (*n)++;
  }
  // Читаем целую часть числа
  while (**n >= '0' && **n <= '9') {
    num = num * 10.0 + (**n - '0');
    (*n)++;
  }
  // Обрабатываем дробную часть числа
  if (**n == '.') {
    (*n)++;
    float fraction = 0.0;
    float fraction_power = 0.1;  // Для умножения на десятичные разряды
    while (**n >= '0' && **n <= '9') {
      fraction += (**n - '0') * fraction_power;
      fraction_power *= 0.1;
      (*n)++;
    }
    num += fraction;
  }
  // Обрабатываем экспоненту
  if (**n == 'e' || **n == 'E') {
    (*n)++;
    int exponent_sign = 1;
    if (**n == '-') exponent_sign = -1;
    (*n)++;
    int exponent = 0;
    while (**n >= '0' && **n <= '9') {
      exponent = exponent * 10 + (**n - '0');
      (*n)++;
    }
    num *= pow(10, exponent * exponent_sign);
  }
  return num * sign;
}

void read_flags(char **format, va_list list, flag *flags) {
  if (**format == '*') {
    flags->suppression = 1;
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
  if (!flags.suppression) {
    *va_arg(list, char *) = **str;
  }
  (*str)++;
  return error;
}

int parse_s(char **str, va_list list, flag flags) {
  int error = 0;
  char *result;
  if (flags.width == 0) {
    flags.width = INT_MAX;
  }
  if (!flags.suppression) {
    result = va_arg(list, char *);
  }
  for (; **str && flags.width > 0 && **str != ' ';
       result++, flags.width--, (*str)++) {
    if (!flags.suppression) *result = **str;
  }
  *result = '\0';
  return error;
}

int parse_d(char **str, va_list list, flag flags) {
  int error = 0;
  long long int number = (long long int)get_num(str);
  if (!flags.suppression) {
    *va_arg(list, long long int *) = number;
  }
  return error;
}

int parse_u(char **str, va_list list, flag flags) {
  int error = 0;
  long long unsigned number = (long long unsigned)get_num(str);
  if (!flags.suppression) {
    *va_arg(list, long long unsigned int *) = number;
  }
  return error;
}

int parse_x(char **str, va_list list, flag flags) {
  int error = 0;
  long long int number = (long long int)get_x_num(str);
  if (!flags.suppression) {
    *va_arg(list, long long int *) = number;
  }
  return error;
}

int parse_o(char **str, va_list list, flag flags) {
  int error = 0;
  long long int number = (long long int)get_o_num(str);
  if (!flags.suppression) {
    *va_arg(list, long long int *) = number;
  }
  return error;
}

int parse_f(char **str, va_list list, flag flags) {
  int error = 0;
  float number = (float)get_double_num(str);
  if (!flags.suppression) {
    *va_arg(list, float *) = number;
  }
  return error;
}

int parse_p(char **str, va_list list, flag flags) {
  int error = 0, sign = 1;
  if (**str == '-') {
    sign = -1;
    *str += 1;
  }
  *str += 2;  // 0x
  long long int number = get_x_num(str);
  if (!flags.suppression) {
    void **p = va_arg(list, void **);
    *p = (void *)(0x0 + sign * number);
  }
  *str += 1;
  return error;
}

int read_types(char **str, va_list list, const char *format, flag flags,
               const char *start) {
  int error = 0;
  if (*format == 'c')
    parse_c(str, list, flags);
  else if (*format == 's')
    parse_s(str, list, flags);
  else if (*format == 'x' || *format == 'X' ||
           *format == 'i' && (*(*str + 2) == 'x' || *(*str + 2) == 'X'))
    parse_x(str, list, flags);
  else if (*format == 'o' || *format == 'i' && *(format + 1) == '0')
    parse_o(str, list, flags);
  else if (*format == 'd')
    parse_d(str, list, flags);
  else if (*format == 'u')
    parse_u(str, list, flags);
  else if (*format == 'f' || *format == 'e' || *format == 'E' ||
           *format == 'g' || *format == 'G')
    parse_f(str, list, flags);
  else if (*format == 'p')
    parse_p(str, list, flags);
  else if (*format == '%')
    *str -= 1;
  else if (*format == 'n')
    *va_arg(list, long int *) = *str - start;
  format++;
  *str += 1;
  return error;
}

int s21_sscanf(const char *str, const char *format, ...) {
  va_list list;
  va_start(list, format);
  flag flags = {0};
  int error = 0;
  const char *start = str;
  while (!error && *str != '\0' && *format != 0) {
    if (*format++ == '%') {
      flags = (flag){0};
      read_flags((char **)&format, list, &flags);
      read_size(format, &flags);
      error = read_types((char **)&str, list, format, flags, start);
    }
  }
  va_end(list);
  return 0;
}

int main() {
  char i, you, percent;
  int day, year, oct, hex, HEX, any, *p;
  float a, b, c, d, e, f;
  char word[5], weekday[5], month[5], strings[100], integers[100],
      fractals[100];
  strcpy(strings, "I at Saturday March F aBc");
  strcpy(integers, "25 1989 -40 F aBc");
  strcpy(fractals, "25.1989 -40.5 7e02 9e-02 1.2e+12 4e+102");

  s21_sscanf(strings, "%*c %s %*s %s %c %% %p", /*&i,*/ word,
             /*weekday,*/ month, &you, &p);
  printf("MY:     \t%s \t%s \t%c \t%% \t%p\n", /*i,*/ word, /*weekday, */ month,
         you, &p);

  strcpy(strings, "I at Saturday March F aBc");

  sscanf(strings, "%*c %s %*s %s %c %% %p", /*&i,*/ word, /*weekday,*/ month,
         &you, &p);
  printf("BASE:   \t%s \t%s \t%c \t%% \t%p\n", /*i,*/ word, /*weekday, */ month,
         you, &p);

  s21_sscanf(integers, "%d %u %o %x %X %*X", &day, &year, &oct, &hex, &HEX/*,
               &any*/);
  printf("MY:   \t%d \t%u \t%o \t%x \t%X \n", day, year, oct, hex, HEX/*,
         any*/);

  strcpy(integers, "25 1989 -40 F aBc");

  sscanf(integers, "%d %u %o %x %X %*X", &day, &year, &oct, &hex,
         &HEX /*, &any*/);
  printf("BASE: \t%d \t%u \t%o \t%x \t%X \n", day, year, oct, hex, HEX/*,
         any*/);

  s21_sscanf(fractals, "%f %f %e %E %g %G", &a, &b, &c, &d, &e, &f);
  printf("MY:   \t%f \t%f \t%e \t%E \t%g \t%G\n", a, b, c, d, e, f);

  strcpy(fractals, "25.1989 -40.5 7e02 9e-02 1.2e+12 4e+102");

  sscanf(fractals, "%f %f %e %E %g %G", &a, &b, &c, &d, &e, &f);
  printf("BASE: \t%f \t%f \t%e \t%E \t%g \t%G\n", a, b, c, d, e, f);

  return (0);
}