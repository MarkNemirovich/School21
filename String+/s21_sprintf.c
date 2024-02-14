#include "s21_string.h"
#include <string.h>  // temprorarys delete after finish!!!

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

void read_flags(char **format, va_list list, flag *flags) {
  if (**format == '-') {
    flags->minus = 1;
    (*format)++;
  }
  if (**format == '+') {
    flags->plus = 1;
    (*format)++;
  } else if (**format == ' ') {
    flags->space = 1;
    (*format)++;
  }
  if (**format == '0') {
    if (!flags->minus) flags->zeros = 1;
    (*format)++;
  }
  if (**format == '#') {
    if (!flags->plus && !flags->space) flags->hash = 1;
    (*format)++;
  }
  if (**format == '*') {
    flags->width = va_arg(list, int);
    (*format)++;
  } else if (**format >= '0' && **format <= '9') {
    flags->width = get_num(format);
  }
  if (**format == '.') {
    flags->point = 1;
    flags->zeros = 0;
    (*format)++;
    if (**format == '*') {
      flags->accuracy = va_arg(list, int);
      (*format)++;
    } else
      flags->accuracy = get_num(format);
  }
}

void read_size(char **format, flag *flags) {
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

void add_spaces(char *str, int *i, flag flags, char mode) {
  int p = flags.width;
  if (flags.hash && flags.zeros && mode == 'o') {
    str[(*i)++] = '0';
    p--;
  }
  if (flags.hash && flags.zeros && (mode == 'x' || mode == 'X')) {
    str[(*i)++] = '0';
    str[(*i)++] = mode;
    p -= 2;
  }
  for (; p > 0; p--) {
    str[(*i)++] = flags.zeros ? '0' : ' ';
  }
  if (flags.hash && !flags.zeros && mode == 'o') {
    if (flags.width > 0) *i -= 1;
    str[(*i)++] = '0';
  }
  if (flags.hash && !flags.zeros && (mode == 'x' || mode == 'X')) {
    if (flags.width > 0) *i -= 2;
    str[(*i)++] = '0';
    str[(*i)++] = mode;
  }
}

void print(char *str, int *i, char *number, int length, flag flags, int sign,
           char mode) {
  flags.width -= length;
  if (!sign || flags.plus ||flags.space) flags.width--;
  if (flags.width > 0 && !flags.minus && !flags.zeros && !flags.hash) {
    add_spaces(str, i, flags, mode);
  }
  if (!sign) {
    str[(*i)++] = '-';
  } else if (flags.plus) {
    str[(*i)++] = '+';
  } else if (flags.space) {
    str[(*i)++] = ' ';
  }
  if (flags.zeros || flags.hash) {
    add_spaces(str, i, flags, mode);
  }
  for (; length > 0; (*i)++, number++, length--) {
    str[*i] = *number;
  }
  if (length < flags.width && flags.minus && !flags.zeros) {
    add_spaces(str, i, flags, mode);
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

int s21_itoa(long long int n, char *res, flag flags) {
  return int_to_str(n, res, flags.accuracy, 10, '\0');
}

int s21_utoa(unsigned long long int n, char *res, flag flags) {
  return int_to_str(n, res, flags.accuracy, 10, '\0');
}

int s21_xtoa(unsigned long long int n, char *res, flag flags,
             char modificator) {
  return int_to_str(n, res, flags.accuracy, 16, modificator);
}

int s21_otoa(unsigned long long int n, char *res, flag flags) {
  return int_to_str(n, res, flags.accuracy, 8, '\0');
}

int s21_ptoa(unsigned long long int n, char *res, flag flags) {
  int i = 0;
  res[i++] = '0';
  res[i++] = 'x';
  return i + int_to_str(n, res + i, flags.accuracy, 16, 'a');
}

int s21_ftoa(long double n, char *res, flag flags) {
  long double ipart;                     // Extract integer part
  long double fpart = modfl(n, &ipart);  // Extract floating part
  int i = int_to_str(ipart, res, 0, 10, '\0');
  if (flags.accuracy > 0) {
    res[i++] = '.';
    // Get the value of fraction part upto given by points after dot
    fpart = round(fpart * pow(10, flags.accuracy));
    // convert floating part to string
    i += int_to_str((long long int)fpart, res + i, flags.accuracy, 10, '\0');
  }
  return i;
}

int s21_etoa(long double n, char *res, flag flags, char modificator) {
  int power = 0;
  for (; n > 10; power++) {  // shift 123.456 number to 1.23456e+2
    n /= 10;
  }
  if (power == 0) {  // shift 0.000123 number to 1.23...e-4
    for (; n < 1; power--) n *= 10;
  }
  int i = int_to_str((long long int)n, res, 0, 10, '\0');
  if (flags.accuracy > 0) {
    res[i++] = '.';
    // Get the value of fraction part upto given by points after dot
    n = roundl((n - (long long int)n) * pow(10, flags.accuracy));
    // convert floating part to string
    i += int_to_str((long long int)n, res + i, flags.accuracy, 10, '\0');
  }
  res[i++] = modificator;             // add e or E
  res[i++] = power >= 0 ? '+' : '-';  // add power sign
  i += int_to_str((long long int)power, res + i, 2, 10,
                  '\0');  // add power in format at least 00
  return i;
}

int c_specific(char *str, int *i, char symbol, flag flags) {
  if (flags.minus) {
    str[(*i)++] = symbol;
    add_spaces(str, i, flags, 'c');
  } else {
    add_spaces(str, i, flags, 'c');
    str[(*i)++] = symbol;
  }
  return 1;
}

int s_specific(char *str, int *i, char *text, flag flags) {
  int length = (int)s21_strlen(text);
  if (flags.accuracy < length) length = flags.accuracy;
  print(str, i, text, length, flags, 1, 's');
  return length;
}

int d_specific(char *str, int *i, long long int number, flag flags) {
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
  int length = s21_itoa(number, num, flags);
  print(str, i, num, length, flags, sign, 'd');
  return length;
}

int u_specific(char *str, int *i, long long unsigned int number, flag flags) {
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
  int length = s21_utoa(number, num, flags);
  print(str, i, num, length, flags, 1, 'u');
  return length;
}

int x_specific(char *str, int *i, long long unsigned int number, flag flags,
               char modificator) {
  // cast to neccessary type
  if (flags.longer)
    number = (unsigned long int)number;
  else if (flags.shorter)
    number = (unsigned short int)number;
  else if (flags.longest)
    ;
  else
    number = (unsigned int)number;
  char num[S21_TEXTMAX];  // -23: x->a & X->A
  int length = s21_xtoa(number, num, flags, modificator - 23);
  print(str, i, num, length, flags, 1, modificator);
  return length;
}

int o_specific(char *str, int *i, long long unsigned int number, flag flags) {
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
  int length = s21_otoa(number, num, flags);
  print(str, i, num, length, flags, 1, 'o');
  return length;
}

int f_specific(char *str, int *i, long double number, flag flags) {
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
  int length = s21_ftoa(number, num, flags);
  print(str, i, num, length, flags, sign, 'f');
  return length;
}

int e_specific(char *str, int *i, long double number, flag flags,
               char modificator) {
  // cast to neccessary type
  if (flags.longest)
    ;
  else
    number = (double)number;
  int sign = number >= 0;
  if (number < 0) number = -number;
  char num[S21_TEXTMAX];
  int length = s21_etoa(number, num, flags, modificator);
  print(str, i, num, length, flags, sign, 'e');
  return length;
}

int g_specific(char *str, int *i, long double number, flag flags,
               char modificator) {
  if (flags.accuracy == 0) flags.accuracy = 1;
  if (!flags.point) flags.accuracy = 6;
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
  if (flags.accuracy > epow && epow >= -4)
    flags.accuracy -= (epow);
  else
    flags.accuracy--;
  // cast to neccessary type
  if (flags.longest)
    ;
  else
    number = (double)number;
  int length;
  int f_length = f_specific(str, i, number, flags);
  *i -= f_length > flags.width ? f_length : flags.width;
  int e_length = e_specific(str, i, number, flags, modificator - 2);
  printf("%d\t%d\t%d\t%d\n", f_length, e_length, flags.accuracy, epow);
  if (f_length < e_length) {
    *i -= e_length > flags.width ? e_length : flags.width;
    length = f_specific(str, i, number, flags);
  } else
    length = e_length;
  return length;
}

int p_specific(char *str, int *i, void *p, flag flags) {
  flags.accuracy = 12;
  long long unsigned int number = (long long unsigned int)p;
  char num[S21_TEXTMAX];
  int length = s21_ptoa(number, num, flags);
  print(str, i, num, length, flags, 1, 'p');
  return length;
}

int percent_specific(char *str, int *i) {
  s21_memset(&str[*i], '%', 1);
  *i += 1;
  return 1;
}

int get_specificator(char *str, int *i, va_list list, char **format,
                     flag flags) {
  int length = 0;
  switch (**format) {
    case 'c':
      length = c_specific(str, i, va_arg(list, int), flags);
      break;
    case 'd':
      length = d_specific(str, i, va_arg(list, long long int), flags);
      break;
    case 'f':
      if (!flags.point) flags.accuracy = 6;
      if (flags.longest)
        length =
            f_specific(str, i, (long double)va_arg(list, long double), flags);
      else
        length = f_specific(str, i, (long double)va_arg(list, double), flags);
      break;
    case 's':
      length = s_specific(str, i, va_arg(list, char *), flags);
      break;
    case 'u':
      length = u_specific(str, i, va_arg(list, long long unsigned int), flags);
      break;
    case '%':
      length = percent_specific(str, i);
      break;
    case 'e':
    case 'E':
      if (!flags.point) flags.accuracy = 6;
      if (flags.longest)
        length = e_specific(str, i, (long double)va_arg(list, long double),
                            flags, **format);
      else
        length = e_specific(str, i, (long double)va_arg(list, double), flags,
                            **format);
      break;
    case 'g':
    case 'G':
      if (flags.longest)
        length = g_specific(str, i, (long double)va_arg(list, long double),
                            flags, **format);
      else
        length = g_specific(str, i, (long double)va_arg(list, double), flags,
                            **format);
      break;
    case 'x':
    case 'X':
      length = x_specific(str, i, va_arg(list, long long unsigned int), flags,
                          **format);
      break;
    case 'o':
      length = o_specific(str, i, va_arg(list, long long unsigned int), flags);
      break;
    case 'p':
      length = p_specific(str, i, va_arg(list, void *), flags);
      break;
    default:
      break;
  }
  (*format)++;
  if (flags.accuracy > length) length = flags.accuracy;
  if (flags.width > length) length = flags.width;
  length = length - flags.minus;
  return length;
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
      read_flags((char **)&format, list, &flags);
      read_size((char **)&format, &flags);
      size += get_specificator(str, &i, list, (char **)&format, flags);
    } else {
      str[i++] = *(format - 1);
      str[i] = '\0';
    }
  }
  va_end(list);
  return 0;
}

void print_d(char *buffer) {
  long long int integer = -73792344652;
  s21_sprintf(buffer, "sum of %*hd and 20 is 30\n", 20, (short int)integer);
  printf("%s", buffer);
  sprintf(buffer, "sum of %*hd and 20 is 30\n", 20, (short int)integer);
  printf("%s", buffer);
  s21_sprintf(buffer, "sum of %+*.*d and 20 is 30\n",  20, 3, (int)integer);
  printf("%s", buffer);
  sprintf(buffer, "sum of %+*.*d and 20 is 30\n", 20, 3, (int)integer);
  printf("%s", buffer);
  s21_sprintf(buffer, "sum of % 05ld and 20 is 30\n", (long int)integer);
  printf("%s", buffer);
  sprintf(buffer, "sum of % 05ld and 20 is 30\n", (long int)integer);
  printf("%s", buffer);
  s21_sprintf(buffer, "sum of %14.3lld and 20 is 30\n", (long long int)integer);
  printf("%s", buffer);
  sprintf(buffer, "sum of %14.3lld and 20 is 30\n", (long long int)integer);
  printf("%s", buffer);
}

void print_u(char *buffer) {
  long long unsigned int integer = 73792347652;
  s21_sprintf(buffer, "sum of %-hu and 20 is 30\n",
              (short unsigned int)integer);
  printf("MY:\t%s", buffer);
  sprintf(buffer, "sum of %-hu and 20 is 30\n", (short unsigned int)integer);
  printf("BASE:\t%s", buffer);
  s21_sprintf(buffer, "sum of %020u and 20 is 30\n", (unsigned int)integer);
  printf("MY:\t%s", buffer);
  sprintf(buffer, "sum of %020u and 20 is 30\n", (unsigned int)integer);
  printf("BASE:\t%s", buffer);
  s21_sprintf(buffer, "sum of %20.0lu and 20 is 30\n",
              (long unsigned int)integer);
  printf("MY:\t%s", buffer);
  sprintf(buffer, "sum of %20.0lu and 20 is 30\n", (long unsigned int)integer);
  printf("BASE:\t%s", buffer);
  s21_sprintf(buffer, "sum of %20.6llu and 20 is 30\n",
              (long long unsigned int)integer);
  printf("MY:\t%s", buffer);
  sprintf(buffer, "sum of %20.6llu and 20 is 30\n",
          (long long unsigned int)integer);
  printf("BASE:\t%s", buffer);
}

void print_o(char *buffer) {
  long long unsigned int integer = 73792345476;
  s21_sprintf(buffer, "sum of %-#ho and 20 is 30\n",
              (short unsigned int)integer);
  printf("MY:\t%s", buffer);
  sprintf(buffer, "sum of %-#ho and 20 is 30\n", (short unsigned int)integer);
  printf("BASE:\t%s", buffer);
  s21_sprintf(buffer, "sum of %0#20o and 20 is 30\n", (unsigned int)integer);
  printf("MY:\t%s", buffer);
  sprintf(buffer, "sum of %0#20o and 20 is 30\n", (unsigned int)integer);
  printf("BASE:\t%s", buffer);
  s21_sprintf(buffer, "sum of %#20lo and 20 is 30\n",
              (long unsigned int)integer);
  printf("MY:\t%s", buffer);
  sprintf(buffer, "sum of %#20lo and 20 is 30\n", (long unsigned int)integer);
  printf("BASE:\t%s", buffer);
  s21_sprintf(buffer, "sum of %#20llo and 20 is 30\n",
              (long long unsigned int)integer);
  printf("MY:\t%s", buffer);
  sprintf(buffer, "sum of %#20llo and 20 is 30\n",
          (long long unsigned int)integer);
  printf("BASE:\t%s", buffer);
}

void print_x(char *buffer) {
  long long unsigned int integer = 73792345472;
  s21_sprintf(buffer, "sum of %-#hx and %o is %u\n",
              (short unsigned int)integer, (short unsigned int)integer, (short unsigned int)integer);
  printf("MY:\t%s", buffer);
  sprintf(buffer, "sum of %-#hx and 20 is 30\n", (short unsigned int)integer);
  printf("BASE:\t%s", buffer);
  s21_sprintf(buffer, "sum of %0#20x and 20 is 30\n", (unsigned int)integer);
  printf("MY:\t%s", buffer);
  sprintf(buffer, "sum of %0#20x and 20 is 30\n", (unsigned int)integer);
  printf("BASE:\t%s", buffer);
  s21_sprintf(buffer, "sum of %#20lx and 20 is 30\n",
              (long unsigned int)integer);
  printf("MY:\t%s", buffer);
  sprintf(buffer, "sum of %#20lx and 20 is 30\n", (long unsigned int)integer);
  printf("BASE:\t%s", buffer);
  s21_sprintf(buffer, "sum of %#20llx and 20 is 30\n",
              (long long unsigned int)integer);
  printf("MY:\t%s", buffer);
  sprintf(buffer, "sum of %#20llx and 20 is 30\n",
          (long long unsigned int)integer);
  printf("BASE:\t%s", buffer);
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
  char buffer[1000];
  printf("d:\n");
  print_d(buffer);
  printf("x:\n");
  print_u(buffer);
  printf("o:\n");
  print_o(buffer);
  printf("x:\n");
  print_x(buffer);
  printf("f:\n");
  print_fractal(buffer);

  return 0;
}
