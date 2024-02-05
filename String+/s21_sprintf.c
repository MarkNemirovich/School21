#include "s21_sprintf.h"


int s21_sprintf(char *str, const char *format, ...) {
  va_list list;
  va_start(list, format);
  int size = (int)strlen(format);
  int i = 0;

  while (*format != 0 && i < size) {
    if (*format++ == '%') {
      int minus_flag = 0;
      s21_size_t padding = 0;
      modificate_specificator((char **)&format, &minus_flag, &padding);
      size += transform_specificator(str, &i, list, (char **)&format,
                                     minus_flag, padding);
    } else {
      str[i++] = *(format - 1);
      str[i] = '\0';
    }
  }
  va_end(list);
  return 0;
}

int transform_specificator(char *str, int *i, va_list list, char **format,
                           int minus_flag, s21_size_t padding) {
  int length_change = 0;
  switch (**format) {
    case 'c':
      length_change =
          c_specific(str, i, va_arg(list, int), minus_flag, padding);
      (*format)++;
      break;
    case 'd':
      break;
    case 'f':
      break;
    case 's':
      break;
    case 'u':
      break;
    default:
      break;
  }
  return length_change;
}

void modificate_specificator(char **format, int *minus_flag,
                             s21_size_t *padding) {
  if (**format == '-') {
    *minus_flag = 1;
    (*format)++;
  }
  if (**format >= '0' && **format <= '9') {
    *padding = get_num(format);
  }
}

s21_size_t get_num(char **format) {
  s21_size_t num = 0;
  int power = 1;
  for (; **format >= '0' && **format <= '9'; (*format)++) {
    num *= power;
    num += ((**format) - '0');
    power *= 10;
  }
  return num;
}

int c_specific(char *str, int *i, char symbol, int minus_flag,
               s21_size_t padding) {
  if (minus_flag) {
    str[*i] = symbol;
    (*i)++;
    add_spaces(str, i, padding, 1);
  } else {
    add_spaces(str, i, padding, 1);
    str[*i] = symbol;
    (*i)++;
  }
  return padding - minus_flag - 1;
}

void add_spaces(char *str, int *i, s21_size_t padding, int accuracy) {
  while (padding > accuracy) {
    str[*i] = ' ';
    (*i)++;
    padding--;
  }
}

