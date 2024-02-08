#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>  // temprorarys delete after finish!!!

#include "s21_string.h"

typedef struct flags {
  int minus, plus, space, point;
} flags;

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

void modificate_flags(char **format, flags *specificators,
                             int *padding, int *accuracy) {
  if (**format == '-') {
    specificators->minus = 1;
    (*format)++;
  } else if (**format == '+') {
    specificators->plus = 1;
    (*format)++;
  } else if (**format == ' ') {
    specificators->space = 1;
    (*format)++;
  }
  if (**format >= '0' && **format <= '9') {
    *padding = get_num(format);
  }
  if (**format == '.') {
    specificators->point = 1;
    (*format)++;
    *accuracy = get_num(format);
  }
}

void add_spaces(char *str, int *i, int padding) {
  for (; padding > 0; padding--) {
    str[(*i)++] = ' ';
  }
}

void print(char *str, int *i, char *number, int length,
           flags specificators, int padding, int sign) {
  int shift =
      padding - length - (specificators.plus || specificators.space || !sign);
  if (length < padding && !specificators.minus) {
    add_spaces(str, i, shift);
  }
  if (!sign) {
    str[(*i)++] = '-';
  } else if (specificators.plus) {
    str[(*i)++] = '+';
  } else if (specificators.space) {
    str[(*i)++] = ' ';
  }
  for (; length > 0; (*i)++, number++, length--) {
    str[*i] = *number;
  }
  if (length < padding && specificators.minus) {
    add_spaces(str, i, shift);
  }
}
// Reverses a string 'str' of length 'len'
void reverse(char *str, int len) {
  char temp;
  for (int i = 0, j = len - 1; i < j; i++, j--) {
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
  }
}

// Converts a given integer x to string str[].
// n is the number of digits required in the output
int intToStr(long number, char *str, int n) {
  int i = 0;
  while (number) {  // fill from end to start
    str[i++] = (number % 10) + '0';
    number = number / 10;
  }
  // If number of digits required is more, add 0
  while (i < n) {
    str[i++] = '0';
  }
  reverse(str, i);
  str[i] = '\0';
  return i;
}

int s21_itoa(int n, char *res, int accuracy) {
  return intToStr(n, res, accuracy);
}

int s21_ftoa(float n, char *res, int accuracy) {
  int ipart = (int)n;              // Extract integer part
  float fpart = n - (float)ipart;  // Extract floating part
  int i = intToStr(ipart, res, 0);
  if (accuracy != 0) {  // check for display option after point
    res[i++] = '.';
    // Get the value of fraction part upto given by points after dot
    fpart = fpart * pow(10, accuracy);
    // convert floating part to string
    i += intToStr((int)fpart, res + i, accuracy);
  }
  return i;
}

int s21_utoa(unsigned int n, char *res, int accuracy) {
  return intToStr(n, res, accuracy);
}

int c_specific(char *str, int *i, char symbol, flags specificators,
               int padding) {
  if (specificators.minus) {
    str[(*i)++] = symbol;
    add_spaces(str, i, padding - 1);
  } else {
    add_spaces(str, i, padding - 1);
    str[(*i)++] = symbol;
  }
  return padding - specificators.minus - 1;
}

int d_specific(char *str, int *i, int number, flags specificators,
               int padding, int accuracy) {
  int sign = number >= 0;
  if (number < 0) number = -number;
  char num[S21_TEXTMAX];
  int length = s21_itoa(number, num, accuracy);
  print(str, i, num, length, specificators, padding, sign);
  if (accuracy > length) length = accuracy;
  if (padding > length) length = padding;
  return length - specificators.minus;
}

int f_specific(char *str, int *i, float number, flags specificators,
               int padding, int accuracy) {
  if (!specificators.point) accuracy = 6;
  int sign = number >= 0;
  if (number < 0) number = -number;
  char num[S21_TEXTMAX];
  int length = s21_ftoa(number, num, accuracy);
  print(str, i, num, length, specificators, padding, sign);
  if (accuracy > length) length = accuracy;
  if (padding > length) length = padding;
  return length - specificators.minus;
}

int s_specific(char *str, int *i, char *text, flags specificators,
               int padding, int accuracy) {
  int length = (int)s21_strlen(text);
  if (accuracy < length) length = accuracy;
  print(str, i, text, length, specificators, padding, 1);
  if (padding > length) length = padding;
  return length - specificators.minus;
}

int u_specific(char *str, int *i, unsigned int number, flags specificators,
               int padding, int accuracy) {
  char num[S21_TEXTMAX];
  int length = s21_utoa((int)number, num, accuracy);
  print(str, i, num, length, specificators, padding, 1);
  if (accuracy > length) length = accuracy;
  if (padding > length) length = padding;
  return length - specificators.minus;
}

int percent_specific(char *str, int *i) {
  s21_memset(&str[*i], '%', 1);
  *i += 1;
  return 1;
}

int transform_specificator(char *str, int *i, va_list list, char **format,
                           flags specificators, int padding,
                           int accuracy) {
  int length_change = 0;
  switch (**format) {
    case 'c':
      length_change =
          c_specific(str, i, va_arg(list, int), specificators, padding);
      break;
    case 'd':
      length_change = d_specific(str, i, va_arg(list, int), specificators,
                                 padding, accuracy);
      break;
    case 'f':
      length_change = f_specific(str, i, (float)va_arg(list, double),
                                 specificators, padding, accuracy);
      break;
    case 's':
      length_change = s_specific(str, i, va_arg(list, char*),
                                 specificators, padding, accuracy);
      break;
    case 'u':
      length_change = u_specific(str, i, va_arg(list, unsigned int), specificators,
                                 padding, accuracy);
      break;
    case '%':
      length_change = percent_specific(str, i);
      break;
    default:
      break;
  }
  (*format)++;
  return length_change;
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list list;
  va_start(list, format);
  int size = (int)s21_strlen(format);
  int i = 0;
  flags specificators = {0};
  while (*format != 0 && i < size) {
    if (*format++ == '%') {
      specificators = (flags){0};
      int padding = 0;
      int accuracy = 0;
      modificate_flags((char **)&format, &specificators, &padding,
                              &accuracy);
      size += transform_specificator(str, &i, list, (char **)&format,
                                     specificators, padding, accuracy);
    } else {
      str[i++] = *(format - 1);
      str[i] = '\0';
    }
  }
  va_end(list);
  return 0;
}

int main() {
  long number = -123.23;
  char buffer[50];
  s21_sprintf(buffer, "sum of %-20u and 20 is 30\n", number);
  printf("%s", buffer);

  sprintf(buffer, "sum of %-20u and 20 is 30\n", (unsigned int)number);
  printf("%s", buffer);
  sprintf(buffer, "sum of %-20lu and 20 is 30\n", number);
  printf("%s", buffer);
  return 0;
}