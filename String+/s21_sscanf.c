#include "s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
  va_list list;
  va_start(list, format);
  flag flags = {0};
  int counter = 0, error = 0, empty = 1;
  const char *start = str;
  while (!error && *str != '\0' && *format != 0) {
    if (*format++ == '%') {
      flags = (flag){0};
      s21_read_flags((char **)&format, list, &flags);
      s21_read_size((char **)&format, &flags);
      error = s21_read_type((char **)&str, list, format, &flags, start);
      counter += !flags.suppression && !error;
      empty = 0;
    }
    while (*str == ' ') str++;
  }
  if (empty || (error && counter == 0)) counter = EOF;
  va_end(list);
  return counter;
}

void s21_read_flags(char **format, va_list list, flag *flags) {
  int error;
  if (**format == '*') {
    flags->suppression = 1;
    (*format)++;
  } else if (**format >= '0' && **format <= '9') {
    flags->width = s21_get_num(format, 0, &error);
  }
}


int s21_read_type(char **str, va_list list, const char *format, flag *flags,
                  const char *start) {
  int error = 0;
  if (*format == 'c')
    error = s21_parse_c(str, list, *flags);
  else if (*format == 's')
    error = s21_parse_s(str, list, *flags);
  else if (*format == 'x' || *format == 'X')
    error = s21_parse_x(str, list, *flags);
  else if (*format == 'o')
    error = s21_parse_o(str, list, *flags);
  else if (*format == 'd')
    error = s21_parse_d(str, list, *flags);
  else if (*format == 'i') {
        while (**str == ' ') 
        {
            (*str)++;
            flags->space = 1;
        }
    if (*(*str + 1) == 'x' || *(*str + 1) == 'X')
    error = s21_parse_x(str, list, *flags);
    else if(*(*str) == '0')
    error = s21_parse_o(str, list, *flags);
    else
    error = s21_parse_d(str, list, *flags);
  }
  else if (*format == 'u')
    error = s21_parse_u(str, list, *flags);
  else if (*format == 'f' || *format == 'e' || *format == 'E' ||
           *format == 'g' || *format == 'G')
    error = s21_parse_f(str, list, *flags);
  else if (*format == 'p')
    error = s21_parse_p(str, list, *flags);
  else if (*format == '%')
    (*str)--;
  else if (*format == 'n') {
    *va_arg(list, long int *) = *str - start;
      flags->suppression = 1;
  }
  format++;
  return error;
}

s21_size_t s21_get_o_num(char **n, int width, int *error) {
  s21_size_t num = 0;
  *error = 1;
  int sign = s21_get_sign(n, &width);
  *n += 1;
  for (; **n >= '0' && **n <= '7' && width > 0; (*n)++, width--) {
    if (*error) *error = 0;
    num *= 8;
    num += (**n - '0');
  }
  return num * sign;
}

s21_size_t s21_get_x_num(char **n, int width, int *error) {
  s21_size_t num = 0;
  *error = 1;
  int sign = s21_get_sign(n, &width);
  *n += 2;
  for (; **n >= '0' && **n <= '9' || **n >= 'a' && **n <= 'f' ||
         **n >= 'A' && **n <= 'F' && width > 0;
       (*n)++, width--) {
        if (*error) *error = 0;
    num *= 16;
    if (**n >= '0' && **n <= '9') num += (**n - '0');
    if (**n >= 'a' && **n <= 'f') num += (**n - 'a') + 10;  // сдвиг для
    if (**n >= 'A' && **n <= 'F') num += (**n - 'A') + 10;  // 10-15
  }
  return num * sign;
}

float s21_get_float_num(char **n, int width) {
  float num = 0.0;
  int sign = s21_get_sign(n, &width);
  // Читаем целую часть числа
  for (; **n >= '0' && **n <= '9' && width > 0; (*n)++, width--) {
    num = num * 10.0 + (**n - '0');
  }
  // Обрабатываем дробную часть числа
  if (**n == '.') {
    (*n)++;
    width--;
    float fraction = 0.0;
    float fraction_power = 0.1;  // Для умножения на десятичные разряды
    for (; **n >= '0' && **n <= '9' && width > 0; (*n)++, width--) {
      fraction += (**n - '0') * fraction_power;
      fraction_power *= 0.1;
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
    for (; **n >= '0' && **n <= '9' && width > 0; (*n)++, width--) {
      exponent = exponent * 10 + (**n - '0');
    }
    num *= pow(10, exponent * exponent_sign);
  }
  return num * sign;
}

long double s21_get_double_num(char **n, int width) {
  long double num = 0.0;
  int sign = s21_get_sign(n, &width);
  // Читаем целую часть числа
  for (; **n >= '0' && **n <= '9' && width > 0; (*n)++, width--) {
    num = num * 10.0 + (**n - '0');
  }
  // Обрабатываем дробную часть числа
  if (**n == '.') {
    (*n)++;
    width--;
    long double fraction = 0.0;
    long double fraction_power = 0.1;  // Для умножения на десятичные разряды
    for (; **n >= '0' && **n <= '9' && width > 0; (*n)++, width--) {
      fraction += (**n - '0') * fraction_power;
      fraction_power *= 0.1;
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
    for (; **n >= '0' && **n <= '9' && width > 0; (*n)++, width--) {
      exponent = exponent * 10 + (**n - '0');
    }
    num *= pow(10, exponent * exponent_sign);
  }
  return num * sign;
}

int s21_parse_c(char **str, va_list list, flag flags) {
  int error = 0;
  if (!flags.suppression) {
    char *arg = va_arg(list, char *);
    if (arg != s21_NULL)
      *arg = **str;
    else
      error = 1;
  }
  (*str)++;
  return error;
}

int s21_parse_s(char **str, va_list list, flag flags) {
   int error = 0;
  char *result = s21_NULL;
  if (!flags.width) flags.width = INT_MAX;
  if (!flags.suppression) {
    result = va_arg(list, char *);
  }
    int i = 0;
    for (; i < flags.width && **str != ' ' && **str != '\t' && **str != '\n'; i++) {
         (*str)++;
    }
  if (flags.width > i && i != 0) {
    flags.width = i;
  }
  if (result != s21_NULL) {
        result = s21_strncpy(result, *(str)-i, flags.width);
  } else {
    error = 1;
  }
  if (**str == ' ' || **str == '\t' || **str == '\n') (*str)++;
  return error;
}

int s21_parse_d(char **str, va_list list, flag flags) {
  int error = 0;
  long long int number = (long long int)s21_get_num(str, flags.width, &error);
  if (!flags.suppression) {
    long long int *arg = va_arg(list, long long int *);
    if (arg != s21_NULL)
      *arg = number;
    else
      error = 1;
  }
  return error;
}

int s21_parse_u(char **str, va_list list, flag flags) {
  int error = 0;
  long long unsigned number = (long long unsigned)s21_get_num(str, flags.width, &error);
  if (!flags.suppression) {
    long long unsigned int *arg = va_arg(list, long long unsigned int *);
    if (arg != s21_NULL)
      *arg = number;
    else
      error = 1;
  }
  return error;
}

int s21_parse_x(char **str, va_list list, flag flags) {
  int error = 0;
  long long int number = (long long int)s21_get_x_num(str, flags.width, &error);
  if (!flags.suppression) {
    long long unsigned int *arg = va_arg(list, long long unsigned int *);
    if (arg != s21_NULL)
      *arg = number;
    else
      error = 1;
  }
  return error;
}

int s21_parse_o(char **str, va_list list, flag flags) {
  int error = 0;
  long long int number = (long long int)s21_get_o_num(str, flags.width, &error);
  if (!flags.suppression) {
    long long unsigned int *arg = va_arg(list, long long unsigned int *);
    if (arg != s21_NULL)
      *arg = number;
    else
      error = 1;
  }
  return error;
}

int s21_parse_f(char **str, va_list list, flag flags) {
  int error = 0;
  long double long_number;
  double number;
  if (flags.longest)
    long_number = (long double)s21_get_double_num(str, flags.width);
  else
    number = (float)s21_get_float_num(str, flags.width);
  if (!flags.suppression) {
    if (flags.longest) {
      long double *arg = va_arg(list, long double *);
      if (arg != s21_NULL)
        *arg = long_number;
      else
        error = 1;
    } else {
      float *arg = va_arg(list, float *);
      if (arg != s21_NULL)
        *arg = number;
      else
        error = 1;
    }
  }
  return error;
}

int s21_parse_p(char **str, va_list list, flag flags) {
  int error = 0, sign = 1;
  if (**str == '-') {
    sign = -1;
    *str += 1;
  }
  *str += 2;  // 0x
  long long int number = s21_get_x_num(str, flags.width, &error);
  if (!flags.suppression) {
    void **arg = va_arg(list, void **);
    if (arg != s21_NULL)
      *arg = (void *)(0x0 + sign * number);
    else
      error = 1;
  }
  return error;
}
