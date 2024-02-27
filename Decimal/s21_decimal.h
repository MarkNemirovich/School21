#ifndef __S21_DECIMAL_H__
#define __S21_DECIMAL_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

#define MINUS 0x80000000 // 10000000 00000000 00000000 00000000
#define SCALE 0x00ff0000 // 00000000 11111111 00000000 00000000
#define MAX4BITE 0xffffffff  // 11111111 11111111 11111111 11111111
#define e1 65536
#define s21_isnan(X) ((X) != (X))
#define s21_isinf(X) ((X) == (1.0 / 0.0))

typedef struct {
    unsigned int bits[4];
} s21_decimal;

typedef struct {
    unsigned int bits[7];
} s21_long_decimal;

// Arithmetic

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_long_add(s21_long_decimal value_1, s21_long_decimal value_2, s21_long_decimal *result);
int s21_long_sub(s21_long_decimal value_1, s21_long_decimal value_2, s21_long_decimal *result);
int s21_long_mul(s21_long_decimal value_1, s21_long_decimal value_2, s21_long_decimal *result);
int s21_long_div(s21_long_decimal value_1, s21_long_decimal value_2, s21_long_decimal *result);
int s21_long_mod(s21_long_decimal value_1, s21_long_decimal value_2, s21_long_decimal *result);
enum errors { OK = 0, TOO_BIG = 1, TOO_SMALL = 2, DIVISION_BY_ZERO = 3 };

// Comparison

int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);

int s21_long_is_equal(s21_long_decimal value_1, s21_long_decimal value_2);
int s21_long_is_not_equal(s21_long_decimal value_1, s21_long_decimal value_2);
int s21_long_is_less(s21_long_decimal value_1, s21_long_decimal value_2);
int s21_long_is_less_or_equal(s21_long_decimal value_1, s21_long_decimal value_2);
int s21_long_is_greater(s21_long_decimal value_1, s21_long_decimal value_2);
int s21_long_is_greater_or_equal(s21_long_decimal value_1, s21_long_decimal value_2);
enum comparisons { TRUE = 0, FALSE = 1 };

// Conversion

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_long_from_int_to_decimal(int src, s21_long_decimal *dst);
int s21_long_from_float_to_decimal(float src, s21_long_decimal *dst);
int s21_long_from_decimal_to_int(s21_long_decimal src, int *dst);
int s21_long_from_decimal_to_float(s21_long_decimal src, float *dst);
enum conversions { OK = 0, CONV_ERROR = 1 };

// Other

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int s21_long_floor(s21_long_decimal value, s21_long_decimal *result);
int s21_long_round(s21_long_decimal value, s21_long_decimal *result);
int s21_long_truncate(s21_long_decimal value, s21_long_decimal *result);
int s21_long_negate(s21_long_decimal value, s21_long_decimal *result);
enum others { OK = 0, CALC_ERROR = 1 };


// Support

int s21_is_empty_decimal(s21_decimal value);
void s21_clean_decimal(s21_decimal *value);
int s21_get_sign(s21_decimal value);
void s21_set_sign(s21_decimal *value, int sign);
int s21_get_bit(unsigned int x, int i);
void s21_set_bit(unsigned int *x, int i, int bit);
int s21_get_pow(s21_decimal value);
void s21_set_pow(s21_decimal *value, int scale);

// Long 

int s21_is_empty_long_decimal(s21_long_decimal value);
void s21_clean_long_decimal(s21_long_decimal *value);

#endif