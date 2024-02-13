#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>  // temprorarys delete after finish!!!

#include "s21_string.h"

typedef struct flag {
  int minus, plus, space, point, shorter, longer, longest;
} flag;

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

void modificate_flags(char **format, flag *flags, int *padding, int *accuracy) {
  if (**format == '-') {
    flags->minus = 1;
    (*format)++;
  } else if (**format == '+') {
    flags->plus = 1;
    (*format)++;
  } else if (**format == ' ') {
    flags->space = 1;
    (*format)++;
  }
  if (**format >= '0' && **format <= '9') {
    *padding = get_num(format);
  }
  if (**format == '.') {
    flags->point = 1;
    (*format)++;
    *accuracy = get_num(format);
  }
}

void modificate_size(char **format, flag *flags, int *padding, int *accuracy) {
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

void add_spaces(char *str, int *i, int padding) {
  for (; padding > 0; padding--) {
    str[(*i)++] = ' ';
  }
}

void print(char *str, int *i, char *number, int length, flag flags, int padding,
           int sign) {
  int shift = padding - length - (flags.plus || flags.space || !sign);
  if (length < padding && !flags.minus) {
    add_spaces(str, i, shift);
  }
  if (!sign) {
    str[(*i)++] = '-';
  } else if (flags.plus) {
    str[(*i)++] = '+';
  } else if (flags.space) {
    str[(*i)++] = ' ';
  }
  for (; length > 0; (*i)++, number++, length--) {
    str[*i] = *number;
  }
  if (length < padding && flags.minus) {
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
int int_to_str(long long unsigned number, char *str, int length, int base,
               char modificator) {
  int i = 0;
  while (number) {  // fill from end to start
    int val = (number % base);
    str[i++] = val < 10 ? val + '0' : val - 10 + modificator;
    number = number / base;
  }
  // If number of digits required is more, add 0
  while (i < length) {
    str[i++] = '0';
  }
  reverse(str, i);
  str[i] = '\0';
  return i;
}

int int_to_x_str(long long unsigned number, char *str, int length,
                 char modificator) {
  int i = 0;
  while (number) {  // fill from end to start
    int val = (number % 16);
    str[i++] = val < 10 ? val + '0' : val - 10 + modificator;
    number = number / 16;
  }
  // If number of digits required is more, add 0
  while (i < length) {
    str[i++] = '0';
  }
  reverse(str, i);
  str[i] = '\0';
  return i;
}

int s21_itoa(long long int n, char *res, int accuracy) {
  return int_to_str(n, res, accuracy, 10, '\0');
}

int s21_utoa(unsigned long long int n, char *res, int accuracy) {
  return int_to_str(n, res, accuracy, 10, '\0');
}

int s21_xtoa(unsigned long long int n, char *res, int accuracy,
             char modificator) {
  return int_to_str(n, res, accuracy, 16, modificator);
}

int s21_otoa(unsigned long long int n, char *res, int accuracy) {
  return int_to_str(n, res, accuracy, 8, '\0');
}

int s21_ptoa(unsigned long long int n, char *res, int accuracy) {
  int i = 0;
  res[i++] = '0';
  res[i++] = 'x';
  return i + int_to_str(n, res+i, accuracy, 16, 'a');
}

int s21_ftoa(long double n, char *res, int accuracy) {
  long double ipart;                     // Extract integer part
  long double fpart = modfl(n, &ipart);  // Extract floating part
  int i = int_to_str(ipart, res, 0, 10, '\0');
  if (accuracy > 0) {
    res[i++] = '.';
    // Get the value of fraction part upto given by points after dot
    fpart = round(fpart * pow(10, accuracy));
    // convert floating part to string
    i += int_to_str((long long int)fpart, res + i, accuracy, 10, '\0');
  }
  return i;
}

int s21_etoa(long double n, char *res, int accuracy, char modificator) {
  int power = 0;
  for (; n > 10; power++) {  // shift 123.456 number to 1.23456e+2
    n /= 10;
  }
  if (power == 0) {  // shift 0.000123 number to 1.23...e-4
    for (; n < 1; power--) n *= 10;
  }
  int i = int_to_str((long long int)n, res, 0, 10, '\0');
  if (accuracy > 0) {
    res[i++] = '.';
    // Get the value of fraction part upto given by points after dot
    n = roundl((n - (long long int)n) * pow(10, accuracy));
    // convert floating part to string
    i += int_to_str((long long int)n, res + i, accuracy, 10, '\0');
  }
  res[i++] = modificator;             // add e or E
  res[i++] = power >= 0 ? '+' : '-';  // add power sign
  i += int_to_str((long long int)power, res + i, 2, 10,
                  '\0');  // add power in format at least 00
  return i;
}

int c_specific(char *str, int *i, char symbol, flag flags, int padding) {
  if (flags.minus) {
    str[(*i)++] = symbol;
    add_spaces(str, i, padding - 1);
  } else {
    add_spaces(str, i, padding - 1);
    str[(*i)++] = symbol;
  }
  return 1;
}

int s_specific(char *str, int *i, char *text, flag flags, int padding,
               int accuracy) {
  int length = (int)s21_strlen(text);
  if (accuracy < length) length = accuracy;
  print(str, i, text, length, flags, padding, 1);
  return length;
}

int d_specific(char *str, int *i, long long int number, flag flags, int padding,
               int accuracy) {
  // cast to neccessary type
  if (flags.longer)
    number = (long int)number;
  else if (flags.shorter)
    number = (short int)number;
  else if (flags.longest)
    ;
  else
    number = (int)number;

  int sign = number >= 0;
  if (number < 0) number = -number;
  char num[S21_TEXTMAX];
  int length = s21_itoa(number, num, accuracy);
  print(str, i, num, length, flags, padding, sign);
  return length;
}

int u_specific(char *str, int *i, long long unsigned int number, flag flags,
               int padding, int accuracy) {
  // cast to neccessary type
  if (flags.longer)
    number = (unsigned long int)number;
  else if (flags.shorter)
    number = (unsigned short int)number;
  else if (flags.longest)
    ;
  else
    number = (unsigned int)number;

  char num[S21_TEXTMAX];
  int length = s21_utoa(number, num, accuracy);
  print(str, i, num, length, flags, padding, 1);
  return length;
}

int x_specific(char *str, int *i, long long unsigned int number, flag flags,
               int padding, int accuracy, char modificator) {
  // cast to neccessary type
  if (flags.longer)
    number = (unsigned long int)number;
  else if (flags.shorter)
    number = (unsigned short int)number;
  else if (flags.longest)
    ;
  else
    number = (unsigned int)number;
  char num[S21_TEXTMAX];
  int length =
      s21_xtoa(number, num, accuracy, modificator - 23);  // -23: x->a & X->A
  print(str, i, num, length, flags, padding, 1);
  return length;
}

int o_specific(char *str, int *i, long long unsigned int number, flag flags,
               int padding, int accuracy) {
  // cast to neccessary type
  if (flags.longer)
    number = (unsigned long int)number;
  else if (flags.shorter)
    number = (unsigned short int)number;
  else if (flags.longest)
    ;
  else
    number = (unsigned int)number;

  char num[S21_TEXTMAX];
  int length = s21_otoa(number, num, accuracy);
  print(str, i, num, length, flags, padding, 1);
  return length;
}

int f_specific(char *str, int *i, long double number, flag flags, int padding,
               int accuracy) {
  // cast to neccessary type
  if (flags.longer)
    number = (double)number;
  else if (flags.longest)
    ;
  else
    number = (float)number;
  int sign = number >= 0;
  if (number < 0) number = -number;
  char num[S21_TEXTMAX];
  int length = s21_ftoa(number, num, accuracy);
  print(str, i, num, length, flags, padding, sign);
  return length;
}

int e_specific(char *str, int *i, long double number, flag flags, int padding,
               int accuracy, char modificator) {
  // cast to neccessary type
  if (flags.longest)
    ;
  else
    number = (double)number;
  int sign = number >= 0;
  if (number < 0) number = -number;
  char num[S21_TEXTMAX];
  int length = s21_etoa(number, num, accuracy, modificator);
  print(str, i, num, length, flags, padding, sign);
  return length;
}

int g_specific(char *str, int *i, long double number, flag flags, int padding,
               int accuracy, char modificator) {
  if (accuracy == 0) accuracy = 1;
  if (!flags.point) accuracy = 6;
  long long int ipart = (long long int)floorl(number);  // Extract integer part
  long double fpart = number - (long double)ipart;      // Extract floating part
  int epow = 0;
  while (ipart > 0) {
    epow++;
    ipart /= 10;
  }
  if (epow == 0)
    while (fpart > 0) {
      epow--;
      fpart /= 10;
    }
  if (accuracy > epow && epow >= -4)
    accuracy -= (epow);
  else
    accuracy--;
  // cast to neccessary type
  if (flags.longest)
    ;
  else
    number = (double)number;
  int length;
  int f_length = f_specific(str, i, number, flags, padding, accuracy);
  *i -= f_length > padding ? f_length : padding;
  int e_length =
      e_specific(str, i, number, flags, padding, accuracy, modificator - 2);
  printf("%d\t%d\t%d\t%d\n", f_length, e_length, accuracy, epow);
  if (f_length < e_length) {
    *i -= e_length > padding ? e_length : padding;
    length = f_specific(str, i, number, flags, padding, accuracy);
  } else
    length = e_length;
  return length;
}

int p_specific(char *str, int *i, void *p, flag flags, int padding,
               int accuracy) {
  accuracy = 12;
  long long unsigned int number = (long long unsigned int)p;
  char num[S21_TEXTMAX];
  int length = s21_ptoa(number, num, accuracy);
  print(str, i, num, length, flags, padding, 1);
  return length;
}

int percent_specific(char *str, int *i) {
  s21_memset(&str[*i], '%', 1);
  *i += 1;
  return 1;
}

int transform_specificator(char *str, int *i, va_list list, char **format,
                           flag flags, int padding, int accuracy) {
  int length_change = 0;
  switch (**format) {
    case 'c':
      length_change = c_specific(str, i, va_arg(list, int), flags, padding);
      break;
    case 'd':
      length_change = d_specific(str, i, va_arg(list, long long int), flags,
                                 padding, accuracy);
      break;
    case 'f':
      if (!flags.point) accuracy = 6;
      if (flags.longest)
        length_change =
            f_specific(str, i, (long double)va_arg(list, long double), flags,
                       padding, accuracy);
      else
        length_change = f_specific(str, i, (long double)va_arg(list, double),
                                   flags, padding, accuracy);
      break;
    case 's':
      length_change =
          s_specific(str, i, va_arg(list, char *), flags, padding, accuracy);
      break;
    case 'u':
      length_change = u_specific(str, i, va_arg(list, long long unsigned int),
                                 flags, padding, accuracy);
      break;
    case '%':
      length_change = percent_specific(str, i);
      break;
    case 'e':
    case 'E':
      if (!flags.point) accuracy = 6;
      if (flags.longest)
        length_change =
            e_specific(str, i, (long double)va_arg(list, long double), flags,
                       padding, accuracy, **format);
      else
        length_change = e_specific(str, i, (long double)va_arg(list, double),
                                   flags, padding, accuracy, **format);
      break;
    case 'g':
    case 'G':
      if (flags.longest)
        length_change =
            g_specific(str, i, (long double)va_arg(list, long double), flags,
                       padding, accuracy, **format);
      else
        length_change = g_specific(str, i, (long double)va_arg(list, double),
                                   flags, padding, accuracy, **format);
      break;
    case 'x':
    case 'X':
      length_change = x_specific(str, i, va_arg(list, long long unsigned int),
                                 flags, padding, accuracy, **format);
      break;
    case 'o':
      length_change = o_specific(str, i, va_arg(list, long long unsigned int),
                                 flags, padding, accuracy);
    default:
    case 'p':
      length_change =
          p_specific(str, i, va_arg(list, void *), flags, padding, accuracy);
      break;
  }
  (*format)++;
  if (accuracy > length_change) length_change = accuracy;
  if (padding > length_change) length_change = padding;
  length_change = length_change - flags.minus;
  return length_change;
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list list;
  va_start(list, format);
  int size = (int)s21_strlen(format);
  int i = 0;
  flag flags = {0};
  while (*format != 0 && i < size) {
    if (*format++ == '%') {
      flags = (flag){0};
      int padding = 0;
      int accuracy = 0;
      modificate_flags((char **)&format, &flags, &padding, &accuracy);
      modificate_size((char **)&format, &flags, &padding, &accuracy);
      size += transform_specificator(str, &i, list, (char **)&format, flags,
                                     padding, accuracy);
    } else {
      str[i++] = *(format - 1);
      str[i] = '\0';
    }
  }
  va_end(list);
  return 0;
}

void print_int(char *buffer) {
  long long int integer = -7379234545437652;
  s21_sprintf(buffer, "sum of %20hd and 20 is 30\n", (short int)integer);
  printf("%s", buffer);
  sprintf(buffer, "sum of %20hd and 20 is 30\n", (short int)integer);
  printf("%s", buffer);
  s21_sprintf(buffer, "sum of %20d and 20 is 30\n", (int)integer);
  printf("%s", buffer);
  sprintf(buffer, "sum of %20d and 20 is 30\n", (int)integer);
  printf("%s", buffer);
  s21_sprintf(buffer, "sum of %20ld and 20 is 30\n", (long int)integer);
  printf("%s", buffer);
  sprintf(buffer, "sum of %20ld and 20 is 30\n", (long int)integer);
  printf("%s", buffer);
  s21_sprintf(buffer, "sum of %20lld and 20 is 30\n", (long long int)integer);
  printf("%s", buffer);
  sprintf(buffer, "sum of %20lld and 20 is 30\n", (long long int)integer);
  printf("%s", buffer);
}

void print_unsigned(char *buffer) {
  long long unsigned int integer = 7379234547652;
  s21_sprintf(buffer, "sum of %20ho and 20 is 30\n",
              (short unsigned int)integer);
  printf("%s", buffer);
  sprintf(buffer, "sum of %20ho and 20 is 30\n", (short unsigned int)integer);
  printf("%s", buffer);
  s21_sprintf(buffer, "sum of %20o and 20 is 30\n", (unsigned int)integer);
  printf("%s", buffer);
  sprintf(buffer, "sum of %20o and 20 is 30\n", (unsigned int)integer);
  printf("%s", buffer);
  s21_sprintf(buffer, "sum of %20lo and 20 is 30\n",
              (long unsigned int)integer);
  printf("%s", buffer);
  sprintf(buffer, "sum of %20lo and 20 is 30\n", (long unsigned int)integer);
  printf("%s", buffer);
  s21_sprintf(buffer, "sum of %20llo and 20 is 30\n",
              (long long unsigned int)integer);
  printf("%s", buffer);
  sprintf(buffer, "sum of %20llo and 20 is 30\n",
          (long long unsigned int)integer);
  printf("%s", buffer);
}

void print_fractal(char *buffer) {
  double fractal = 73.7213;
  s21_sprintf(buffer, "sum of %10.5e and 20 is 30\n", (float)fractal);
  printf("MY:\t%s", buffer);
  sprintf(buffer, "sum of %10.5e and 20 is 30\n", (float)fractal);
  printf("BASE:\t%s", buffer);

  s21_sprintf(buffer, "sum of %10.0le and 20 is 30\n", (double)fractal);
  printf("MY:\t%s", buffer);
  sprintf(buffer, "sum of %10.0le and 20 is 30\n", (double)fractal);
  printf("BASE:\t%s", buffer);

  s21_sprintf(buffer, "sum of %le and 20 is 30\n", (double)fractal);
  printf("MY:\t%s", buffer);
  sprintf(buffer, "sum of %le and 20 is 30\n", (double)fractal);
  printf("BASE:\t%s", buffer);

  s21_sprintf(buffer, "sum of %e and 20 is 30\n", (float)(fractal * fractal));
  printf("MY:\t%s", buffer);
  sprintf(buffer, "sum of %e and 20 is 30\n", (float)(fractal * fractal));
  printf("BASE:\t%s", buffer);

  s21_sprintf(buffer, "sum of %Le and 20 is 30\n",
              (long double)(fractal * fractal));
  printf("MY:\t%s", buffer);
  sprintf(buffer, "sum of %Le and 20 is 30\n",
          (long double)(fractal * fractal));
  printf("BASE:\t%s", buffer);
}

int main() {
  char buffer[100];
  //  print_int(buffer);
  print_unsigned(buffer);
  // print_fractal(buffer);

  long long unsigned int integer = 100;
  s21_sprintf(buffer, "sum of %6p and 20 is 30\n", &integer);
  printf("%s", buffer);
  sprintf(buffer, "sum of %6p and 20 is 30\n", &integer);
  printf("%s", buffer);
  return 0;
}
