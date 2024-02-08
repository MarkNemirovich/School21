#ifndef __S21_SPRINTF__
#define __S21_SPRINTF__

#include <limits.h>
#include <stdarg.h>

#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...);
void modificate_specificator(char **format, int *minus_flag,
                             s21_size_t *padding);
s21_size_t get_num(char **format);
int c_specific(char *str, int *i, char symbol, int minus_flag,
               s21_size_t padding);
void add_spaces(char *str, int *i, s21_size_t padding, int accuracy);

#endif