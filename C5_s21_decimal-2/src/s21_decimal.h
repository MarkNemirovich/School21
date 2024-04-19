#ifndef __S21_DECIMAL_H__
#define __S21_DECIMAL_H__

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CALCULATE_ERROR 1
#define CONVERT_ERROR 1
#define COMPARE_TRUE 1
#define COMPARE_FALSE 0
#define TOO_LARGE_OR_INF 1
#define TOO_SMALL_OR_NEG_INF 2
#define DIV_BY_ZERO 3
#define OK 0
#define s21_NAN (__builtin_nanf(""))
#define s21_INF (__builtin_inff())
#define is_nan(x) __builtin_isnan(x)
#define is_inf(x) __builtin_isinf(x)
#define MINUS_MASK 0x80000000  // 10000000 00000000 00000000 00000000
#define SCALE_MASK 0x00ff0000  // 00000000 11111111 00000000 00000000
#define MANTISSA_MAX 95

typedef union {
  float f;
  uint32_t u;
} s21_fu;

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  int exponent;
  int sign;
} exponent;

typedef struct {
  int exponent;
  int sign;
  int mantissa;
} float_info;

enum { low, mid, top, e };

// Вспомогательная.
int s21_equal_exp(unsigned exp1, unsigned exp2, s21_decimal *value_1,
                  s21_decimal *value_2);
int s21_is_less_abs(s21_decimal value_1, s21_decimal value_2);
int s21_both_zeroes(s21_decimal value_1, s21_decimal value_2);
int s21_is_empty_mantissa(s21_decimal value_1);
void s21_copy(s21_decimal src, s21_decimal *res);
int s21_is_incorrect_exponent(s21_decimal result);

// Для знака.
void s21_set_sign(s21_decimal *result, int flag);
int s21_get_sign(s21_decimal decimal);

int s21_bits_eq(const unsigned bits_a[4], const unsigned bits_b[4]);

// Получение нужного бита и вставка нужного бита.
int s21_get_bits(unsigned int num, int pos);
void s21_set_bits(unsigned int *val, int bit, int pos);

// Получение нужного бита и вставка нужного бита.
int s21_get_bit(s21_decimal num, int pos);
void s21_set_bit(s21_decimal *val, int bit, int pos);

// Получение инфы об e и вставка ее.
void s21_get_exp(exponent *bits, s21_decimal *src);
void s21_set_exp(s21_decimal *result, int exp);
void s21_set_info(s21_decimal *result, int sign, int exp);

// Двигаем биты
void s21_shift_left(s21_decimal *val);
void s21_shift_right(s21_decimal *val);

int s21_bits_eq(const unsigned bits_a[4], const unsigned bits_b[4]);

void s21_swap(s21_decimal *val_1, s21_decimal *val_2);
void s21_initialize(s21_decimal *result);

int s21_pre_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_pre_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul10(s21_decimal *value_1, int exp);

// Основные функции.

// Сравнения.
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);

// Математические функции.
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Конвертеры.
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float f, s21_decimal *dst);

// Прочие (По тз).
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);

// для верных окргулений
void s21_bank_round(s21_decimal value, s21_decimal *result);

#endif
