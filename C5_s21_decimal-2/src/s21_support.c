#include "s21_decimal.h"

void s21_get_exp(exponent *bits, s21_decimal *src) {
  int j = 0;
  for (int i = 16; i <= 23; i++) {
    s21_set_bits((unsigned *)&bits->exponent, s21_get_bits(src->bits[3], i), j);
    j++;
  }
  bits->sign = ((src->bits[3] >> 31) & 1);
}

void s21_set_exp(s21_decimal *result, int exp) {
  int i = 16;
  int k = 0;
  while (i < 23) {
    s21_set_bits(&result->bits[e], s21_get_bits(exp, k), i);
    i++;
    k++;
  }
}

int s21_get_sign(s21_decimal decimal) { return decimal.bits[3] >> 31; }

void s21_set_sign(s21_decimal *result, int flag) {
  if (flag == 1) {
    s21_set_bits(&result->bits[e], 1, 31);
  } else {
    s21_set_bits(&result->bits[e], 0, 31);
  }
}

void s21_set_info(s21_decimal *result, int sign, int exp) {
  s21_set_bits(&result->bits[e], sign, 31);
  s21_set_exp(result, exp);
}

int s21_get_bit(s21_decimal num, int pos) {
  int result = (num.bits[pos / 32] >> (pos % 32)) & 1;
  return result;
}

void s21_set_bit(s21_decimal *val, int bit, int pos) {
  if (bit != 0) {
    val->bits[pos / 32] = val->bits[pos / 32] | (bit << pos);
  } else {
    val->bits[pos / 32] = val->bits[pos / 32] & ~((bit + 1) << pos);
  }
}

int s21_get_bits(unsigned int num, int pos) {
  int result = (num >> (pos % 32)) & 1;
  return result;
}

void s21_set_bits(unsigned int *val, int bit, int pos) {
  if (bit != 0 && s21_get_bits(*val, pos) == 0) {
    *val = *val | (bit << pos);
  } else if (bit == 0 && s21_get_bits(*val, pos) == 1) {
    *val = *val & ~((bit + 1) << pos);
  }
}

int s21_bits_eq(const unsigned bits_a[4], const unsigned bits_b[4]) {
  return bits_a[low] == bits_b[low] && bits_a[mid] == bits_b[mid] &&
         bits_a[top] == bits_b[top] && bits_a[e] == bits_b[e];
}

void s21_swap(s21_decimal *val_1, s21_decimal *val_2) {
  s21_decimal x = *val_1;
  *val_1 = *val_2;
  *val_2 = x;
}

void s21_copy(s21_decimal src, s21_decimal *res) { *res = src; }

void s21_shift_left(s21_decimal *val) {
  int bit_1 = 0;
  int bit_2 = 0;
  if (s21_get_bits(val->bits[low], 31) == 1) bit_1 = 1;
  if (s21_get_bits(val->bits[mid], 31) == 1) bit_2 = 1;
  val->bits[low] <<= 1;
  val->bits[mid] <<= 1;
  val->bits[top] <<= 1;
  if (bit_1 == 1) s21_set_bits(&val->bits[mid], 1, 0);
  if (bit_2 == 1) s21_set_bits(&val->bits[top], 1, 0);
}

void s21_shift_right(s21_decimal *val) {
  int bit_1 = 0;
  int bit_2 = 0;
  if (s21_get_bits(val->bits[mid], 0) == 1) bit_1 = 1;
  if (s21_get_bits(val->bits[top], 0) == 1) bit_2 = 1;
  val->bits[low] >>= 1;
  val->bits[mid] >>= 1;
  val->bits[top] >>= 1;
  if (bit_1 == 1) s21_set_bits(&val->bits[low], 1, 31);
  if (bit_2 == 1) s21_set_bits(&val->bits[mid], 1, 31);
}

int s21_is_empty_mantissa(s21_decimal result) {
  return result.bits[0] == 0 && result.bits[1] == 0 && result.bits[2] == 0;
}

int s21_is_incorrect_exponent(s21_decimal result) {
  int bits = 0;
  for (int i = 0; i < 16; i++) bits += s21_get_bit(result, 96 + i);
  for (int i = 24; i < 31; i++) bits += s21_get_bit(result, 96 + i);
  return bits;
}

void s21_initialize(s21_decimal *result) { *result = (s21_decimal){0}; }

int s21_pre_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_initialize(result);
  int flag = 0;
  int i = 0;
  int n = s21_get_bit(value_1, i);
  int m = s21_get_bit(value_2, i);
  int res = n ^ m;

  if (n == 1 && m == 1) flag = 1;
  s21_set_bit(result, res, i);
  i++;

  while (i <= MANTISSA_MAX) {
    n = s21_get_bit(value_1, i);
    m = s21_get_bit(value_2, i);
    res = n ^ m;
    if (res == 1 && flag == 1) {
      res = res ^ flag;
    } else if (flag == 1) {
      res = res ^ flag;
      flag = 0;
    }
    if (n == 1 && m == 1) flag = 1;
    s21_set_bit(result, res, i);
    i++;
  }
  return flag;
}

int s21_pre_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = OK;
  int i = 0;
  while (i <= MANTISSA_MAX) {
    int a = s21_get_bit(value_1, i);
    int b = s21_get_bit(value_2, i);
    if (b && !a) {
      int j;
      for (j = i + 1; !s21_get_bit(value_1, j) && j <= MANTISSA_MAX;) j++;
      s21_set_bits(&value_1.bits[j / 32], low, j);
      j--;
      while (j != i) {
        s21_set_bits(&value_1.bits[j / 32], mid, j);
        j--;
      }
      s21_set_bits(&result->bits[i / 32], mid, i);
    } else {
      s21_set_bits(&result->bits[i / 32], a ^ b, i);
    }
    i++;
  }
  return res;
}

int s21_mul10(s21_decimal *value_1, int exp) {
  if (value_1->bits[top] >= 429496730) {
    return TOO_LARGE_OR_INF;
  }
  s21_decimal ten = {10, 0, 0, 0};
  while (exp > 0) {
    s21_mul(*value_1, ten, value_1);
    exp--;
  }
  return OK;
}