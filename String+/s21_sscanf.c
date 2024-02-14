#include <string.h>  // temprorarys delete after finish!!!

#include "s21_string.h"

s21_size_t get_num(const char *format) {
  s21_size_t num = 0;
  int power = 1;
  for (; *format >= '0' && *format <= '9'; format++) {
    num *= power;
    num += (*format - '0');
    power *= 10;
  }
  return num;
}

void read_flags(const char *format, va_list list, flag *flags) {
  if (*format == '*') {
    flags->width = va_arg(list, int);
    format++;
  } else if (*format >= '0' && *format <= '9') {
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

void read_types(char *str, int *i, va_list list, const char *format,
               flag flags) {
                
               }

int s21_sscanf(const char *str, const char *format, ...) {
  va_list list;
  va_start(list, format);
  int size = (int)s21_strlen(format);
  int i = 0;
  flag flags = {0};
  while (*format != 0 && i < size) {
    if (*format++ == '%') {
      flags = (flag){0};
      read_flags(format, list, &flags);
      read_size(format, &flags);
      read_types(str, &i, list, format, flags);
    }
  }
  va_end(list);
  return 0;
}

int main() {
  int day, year;
  char weekday[20], month[20], dtm[100];

  strcpy(dtm, "Saturday March 25 1989");

  //   s21_sscanf(dtm, "%s %s %d %d", weekday, month, &day, &year);
  //   printf("MY:\t%s %d, %d = %s\n", month, day, year, weekday);

  sscanf(dtm, "%s %s %d %d", weekday, month, &day, &year);
  printf("BASE:\t%s %d, %d = %s\n", month, day, year, weekday);

  return (0);
}