#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list list;
  va_start(list, format);
  int size = (int)s21_strlen(format);
  int i = 0;
  flag flags = {0};
  while (*format != 0 && i < size) {
    if (*format++ == '%') {
      flags = (flag){0};
      s21_get_flags((char **)&format, list, &flags);
      s21_read_size((char **)&format, &flags);
      size += s21_get_type(str, &i, list, (char **)&format, flags);
    } else {
      str[i++] = *(format - 1);
    }
    str[i] = '\0';
  }
  va_end(list);
  return s21_strlen(str);
}

void s21_get_flags(char **format, va_list list, flag *flags) {
  int modificator, error;
  do {
    modificator = 0;
    if (**format == '-') {
      flags->minus = 1;
      (*format)++;
      modificator = 1;
    }
    if (**format == '+') {
      flags->plus = 1;
      (*format)++;
      modificator = 1;
    } else if (**format == ' ') {
      flags->space = 1;
      (*format)++;
      modificator = 1;
    }
    if (**format == '#') {
      if (!flags->plus && !flags->space) flags->hash = 1;
      (*format)++;
      modificator = 1;
    }
    if (**format == '0') {
      if (!flags->minus) flags->zeros = 1;
      (*format)++;
      modificator = 1;
    }

  } while (modificator);
  if (**format == '*') {
    flags->width = va_arg(list, int);
    (*format)++;
  } else if (**format >= '0' && **format <= '9') {
    flags->width = s21_get_num(format, 0, &error);
  }
  if (**format == '.') {
    flags->point = 1;
    flags->zeros = 0;
    (*format)++;
    if (**format == '*') {
      flags->accuracy = va_arg(list, int);
      (*format)++;
    } else
      flags->accuracy = s21_get_num(format, 0, &error);
  }
}

int s21_get_type(char *str, int *i, va_list list, char **format, flag flags) {
  int length = 0;
  if (**format == 'c')
    length = s21_get_c(str, i, va_arg(list, int), flags);
  else if (**format == 's')
    length = s21_get_s(str, i, va_arg(list, char *), flags);
  else if (**format == 'd' || **format == 'i')
    length = s21_get_d(str, i, va_arg(list, long long int), flags);
  else if (**format == 'u')
    length = s21_get_u(str, i, va_arg(list, long long unsigned int), flags);
  else if (**format == 'x' || **format == 'X') {
    length = s21_get_x(str, i, va_arg(list, long long unsigned int), flags,
                       **format);
  } else if (**format == 'o')
    length = s21_get_o(str, i, va_arg(list, long long unsigned int), flags);
  else if (**format == 'f') {
    if (!flags.point) flags.accuracy = 6;
    if (flags.longest)
      length = s21_get_f(str, i, (long double)va_arg(list, long double), flags);
    else
      length = s21_get_f(str, i, (long double)va_arg(list, double), flags);
  } else if (**format == 'e' || **format == 'E') {
    if (!flags.point) flags.accuracy = 6;
    if (flags.longest)
      length = s21_get_e(str, i, (long double)va_arg(list, long double), flags,
                         **format);
    else
      length =
          s21_get_e(str, i, (long double)va_arg(list, double), flags, **format);
  } else if (**format == 'g' || **format == 'G') {
    if (flags.longest)
      length = s21_get_g(str, i, (long double)va_arg(list, long double), flags,
                         **format);
    else
      length =
          s21_get_g(str, i, (long double)va_arg(list, double), flags, **format);
  } else if (**format == 'p')
    length = s21_get_p(str, i, va_arg(list, void *), flags);
  else if (**format == '%')
    length = s21_get_perc(str, i);
  else if (**format == 'n')
    *va_arg(list, long int *) = *i;
  (*format)++;
  if (flags.accuracy > length) length = flags.accuracy;
  if (flags.width > length) length = flags.width;
  length = length - flags.minus;
  return length;
}

int s21_get_c(char *str, int *i, char symbol, flag flags) {
  flags.width--;
  if (flags.minus) {
    str[(*i)++] = symbol;
    s21_add_spaces(str, i, flags, 'c');
  } else {
    s21_add_spaces(str, i, flags, 'c');
    str[(*i)++] = symbol;
  }
  return 1;
}

int s21_get_s(char *str, int *i, char *text, flag flags) {
  int length = (int)s21_strlen(text);
  if (flags.width > 0 && flags.width < length) length = flags.accuracy;
  s21_print(str, i, text, length, flags, 1, 's');
  return length;
}

int s21_get_d(char *str, int *i, long long int number, flag flags) {
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
  int length = 0;
  if (!(!number && !flags.width && flags.point && !flags.accuracy)) {
    char num[S21_TEXTMAX];
    length = s21_itoa(number, num, flags);
    s21_print(str, i, num, length, flags, sign, 'd');
  }
  return length;
}

int s21_get_u(char *str, int *i, long long unsigned int number, flag flags) {
  // cast to neccessary type
  if (flags.longer)
    number = (unsigned long int)number;
  else if (flags.shorter)
    number = (unsigned short int)number;
  else if (flags.longest)
    ;
  else
    number = (unsigned int)number;
  flags.plus = 0;
  flags.space = 0;
  char num[S21_TEXTMAX];
  int length = s21_utoa(number, num, flags);
  s21_print(str, i, num, length, flags, 1, 'u');
  return length;
}

int s21_get_x(char *str, int *i, long long unsigned int number, flag flags,
              char mode) {
  // cast to neccessary type
  if (flags.longer)
    number = (unsigned long int)number;
  else if (flags.shorter)
    number = (unsigned short int)number;
  else if (flags.longest)
    ;
  else
    number = (unsigned int)number;
  if (!number) flags.hash = 0;
  char num[S21_TEXTMAX];  // -23: x->a & X->A
  int length = s21_xtoa(number, num, flags, mode - 23);
  s21_print(str, i, num, length, flags, 1, mode);
  return length;
}

int s21_get_o(char *str, int *i, long long unsigned int number, flag flags) {
  // cast to neccessary type
  if (flags.longer)
    number = (unsigned long int)number;
  else if (flags.shorter)
    number = (unsigned short int)number;
  else if (flags.longest)
    ;
  else
    number = (unsigned int)number;
  if (!number) flags.hash = 0;
  char num[S21_TEXTMAX];
  int length = s21_otoa(number, num, flags);
  s21_print(str, i, num, length, flags, 1, 'o');
  return length;
}

int s21_get_f(char *str, int *i, long double number, flag flags) {
  int sign = number >= 0;
  if (number < 0) number = -number;
  char num[S21_TEXTMAX];
  int length = s21_ftoa(number, num, flags);
  s21_print(str, i, num, length, flags, sign, 'f');
  return length;
}

int s21_get_e(char *str, int *i, long double number, flag flags, char mode) {
  int sign = number >= 0;
  if (number < 0) number = -number;
  char num[S21_TEXTMAX];
  int length = s21_etoa(number, num, flags, mode);
  s21_print(str, i, num, length, flags, sign, 'e');
  return length;
}

int s21_get_g(char *str, int *i, long double number, flag flags, char mode) {
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
  int f_length = s21_get_f(str, i, number, flags);
  *i -= f_length > flags.width ? f_length : flags.width;
  int e_length = s21_get_e(str, i, number, flags, mode - 2);
  if (f_length < e_length) {
    *i -= e_length > flags.width ? e_length : flags.width;
    length = s21_get_f(str, i, number, flags);
  } else
    length = e_length;
  return length;
}

int s21_get_p(char *str, int *i, void *p, flag flags) {
  flags.accuracy = 12;
  long long unsigned int number = (long long unsigned int)p;
  char num[S21_TEXTMAX];
  int length = s21_ptoa(number, num, flags);
  s21_print(str, i, num, length, flags, 1, 'p');
  return length;
}

int s21_get_perc(char *str, int *i) {
  s21_memset(&str[*i], '%', 1);
  *i += 1;
  return 1;
}

int s21_add_mode(char *str, int *i, flag flags, char mode) {
  int p = 0;
  if (flags.hash && mode == 'o') {
    str[(*i)++] = '0';  // если #, то добавляем 0 перед всем числом
    p++;
  }
  if (flags.hash && (mode == 'x' || mode == 'X')) {
    str[(*i)++] = '0';  // если #, то добавляем 0x / 0X перед всем числом
    str[(*i)++] = mode;
    p += 2;
  }
  return p;
}

void s21_add_spaces(char *str, int *i, flag flags, char mode) {
  for (int p = flags.width; p > 0; p--) {
    str[(*i)++] = flags.zeros ? '0' : ' ';  // заполняем нулями или пробелами
  }
}

void s21_print(char *str, int *i, char *number, int length, flag flags,
               int sign, char mode) {
  flags.width -= length;
  int prefex = !sign || flags.plus || flags.space;
  if (prefex) flags.width--;
  if (flags.hash) flags.width--;
  if (flags.hash && (mode == 'x' || mode == 'X')) flags.width--;
  if (flags.width > 0 && !flags.minus && prefex) {
    s21_add_spaces(str, i, flags, mode);  // добавляем пробелы перед знаком
  }
  if (prefex) flags.width -= s21_add_mode(str, i, flags, mode);
  if (!sign) {
    str[(*i)++] = '-';
  } else if (flags.plus) {
    str[(*i)++] = '+';
  } else if (flags.space) {
    str[(*i)++] = ' ';
  }
  // добавляем пробелы или нули перед числом
  if (flags.width > 0 && !flags.minus && !prefex) {
    s21_add_spaces(str, i, flags, mode);  // добавляем пробелы перед знаком
  }
  if (!prefex) flags.width -= s21_add_mode(str, i, flags, mode);
  for (; length > 0; (*i)++, number++, length--) {
    str[*i] = *number;
  }
  // добавляем пробелы или нули после числа
  if (length < flags.width && flags.minus && !flags.zeros) {
    s21_add_spaces(str, i, flags, mode);
  }
}

int s21_itoa(long long int n, char *res, flag flags) {
  return s21_int_to_str(n, res, flags.accuracy, 10, '\0');
}

int s21_utoa(unsigned long long int n, char *res, flag flags) {
  return s21_int_to_str(n, res, flags.accuracy, 10, '\0');
}

int s21_xtoa(unsigned long long int n, char *res, flag flags, char mode) {
  return s21_int_to_str(n, res, flags.accuracy, 16, mode);
}

int s21_otoa(unsigned long long int n, char *res, flag flags) {
  return s21_int_to_str(n, res, flags.accuracy, 8, '\0');
}

int s21_ptoa(unsigned long long int n, char *res, flag flags) {
  int i = 0;
  res[i++] = '0';
  res[i++] = 'x';
  return i + s21_int_to_str(n, res + i, flags.accuracy, 16, 'a');
}

int s21_ftoa(long double n, char *res, flag flags) {
  long double ipart;                     // Extract integer part
  long double fpart = modfl(n, &ipart);  // Extract floating part
  fpart += 1 / LLONG_MAX;
  int i = s21_int_to_str(ipart, res, 0, 10, '\0');
  if (flags.accuracy > 0) {
    res[i++] = '.';
    // Get the value of fraction part upto given by points after dot
    fpart = round(fpart * pow(10, flags.accuracy));
    // convert floating part to string
    i +=
        s21_int_to_str((long long int)fpart, res + i, flags.accuracy, 10, '\0');
  }
  // while (flags.accuracy-- > 0) res[i++] = '0';
  // end float part
  res[i] = '\0';

  return i;
}

int s21_etoa(long double n, char *res, flag flags, char mode) {
  int power = 0;
  for (; n > 10; power++) {  // shift 123.456 number to 1.23456e+2
    n /= 10;
  }
  if (power == 0) {  // shift 0.000123 number to 1.23...e-4
    for (; n < 1; power--) n *= 10;
  }
  int i = s21_int_to_str((long long int)n, res, 0, 10, '\0');
  if (flags.accuracy > 0) {
    res[i++] = '.';
    // Get the value of fraction part upto given by points after dot
    n = roundl((n - (long long int)n) * pow(10, flags.accuracy));
    // convert floating part to string
    i += s21_int_to_str((long long int)n, res + i, flags.accuracy, 10, '\0');
  }
  res[i++] = mode;                    // add e or E
  res[i++] = power >= 0 ? '+' : '-';  // add power sign
  i += s21_int_to_str((long long int)power, res + i, 2, 10,
                      '\0');  // add power in format at least 00
  return i;
}

// Converts a given integer to string
int s21_int_to_str(long long unsigned number, char *str, int length, int base,
                   char mode) {
  int i = 0;
  do {                          // fill from end to start
    int val = (number % base);  // base is 8, 10, 16 system notation
    str[i++] = val < 10 ? val + '0' : val - 10 + mode;  // mode is a shift A-F
    number = number / base;
  } while (number);
  // If number of digits required is more, add 0
  while (i < length) {
    str[i++] = '0';
  }
  s21_reverse(str, i);
  str[i] = '\0';
  return i;
}

// Reverses a string 'str' of length 'len'
void s21_reverse(char *str, int len) {
  char temp;
  for (int i = 0, j = len - 1; i < j; i++, j--) {
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
  }
}
