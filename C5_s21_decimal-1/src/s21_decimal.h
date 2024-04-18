#ifndef __S21_DECIMAL_H__
#define __S21_DECIMAL_H__

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINUS_MASK 0x80000000     // 10000000 00000000 00000000 00000000
#define POWER_MASK 0x00ff0000     // 00000000 11111111 00000000 00000000
#define MAX4BITE 0xffffffff  // 11111111 11111111 11111111 11111111
#define e1 65536
#define s21_isnan(X) ((X) != (X))
#define s21_isinf(X) ((X) == (1.0 / 0.0))
#define START_INFO 96

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

int s21_align_pows(s21_decimal *value_1, s21_decimal *value_2);
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
int s21_long_is_less_or_equal(s21_long_decimal value_1,
                              s21_long_decimal value_2);
int s21_long_is_greater(s21_long_decimal value_1, s21_long_decimal value_2);
int s21_long_is_greater_or_equal(s21_long_decimal value_1,
                                 s21_long_decimal value_2);
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
enum conversions { CONV_ERROR = 1 };

// Other

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int s21_long_floor(s21_long_decimal value, s21_long_decimal *result);
int s21_long_round(s21_long_decimal value, s21_long_decimal *result);
int s21_long_truncate(s21_long_decimal value, s21_long_decimal *result);
int s21_long_negate(s21_long_decimal value, s21_long_decimal *result);
enum others { CALC_ERROR = 1 };

// Support

int s21_is_empty_decimal(s21_decimal value);
int s21_is_reserved_bits_ok(s21_decimal value);
void s21_clear_decimal(s21_decimal *value);
int s21_get_sign(s21_decimal value);
void s21_set_sign(s21_decimal *value, int sign);
int s21_get_bit(unsigned int x, int i);
void s21_set_bit(unsigned int *x, int i, int bit);
int s21_get_pow(s21_decimal value);
void s21_set_pow(s21_decimal *value, int pow);

int s21_multiply_by_ten(s21_decimal value, s21_decimal *result);
void s21_divide_by_ten(s21_decimal value, s21_decimal *result);
void s21_shift_left(s21_decimal *value, int shift);
void s21_shift_right(s21_decimal *value, int shift);
void s21_decimal_pow_shift(s21_decimal value, s21_decimal *result, int pow);
int s21_bit_sum(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_bit_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_copy_decimal(s21_decimal *value_1, s21_decimal value_2);

// Comparison

void s21_comparison_reverse(int *flag);
int s21_comparison_bits(s21_decimal value_1, s21_decimal value_2);
int s21_greater_num(int a, int b);
int s21_comparison(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);

#endif