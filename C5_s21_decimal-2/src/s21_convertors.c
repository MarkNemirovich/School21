#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == NULL) return CONVERT_ERROR;
  *dst = 0;
  s21_decimal ten = {{10, 0, 0, 0}};

  if (src.bits[top] != 0) return CONVERT_ERROR;

  exponent getinfo = {0};
  s21_get_exp(&getinfo, &src);

  while (getinfo.exponent > 0) {
    s21_div(src, ten, &src);
    getinfo.exponent--;
  }

  if (src.bits[mid] != 0) return CONVERT_ERROR;
  if (getinfo.sign == 1 && src.bits[low] > 2147483648) return CONVERT_ERROR;
  if (getinfo.sign == 0 && src.bits[low] > 2147483647) return CONVERT_ERROR;

  *dst = src.bits[0];

  if (getinfo.sign == 1) {
    *dst *= -1;
  }
  return OK;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) return CONVERT_ERROR;
  s21_initialize(dst);
  if (src == INFINITY || src == -INFINITY) {
    return CONVERT_ERROR;
  }
  if (src < 0) {
    s21_set_info(dst, 1, 0);
    src *= -1;
  }
  dst->bits[0] = src;
  return OK;
}

int s21_from_float_to_decimal(float f, s21_decimal *dst) {
  if (dst == NULL || isnan(f) || isinf(f) || -isinf(f)) return CONVERT_ERROR;
  s21_initialize(dst);
  s21_fu fu = {f};
  int counter = 7;
  int new_dec_exp = 0;
  int i = 31;
  float_info Float_info = {0};
  Float_info.sign = (fu.u >> i) & 1;
  i--;
  while (i >= 23) {
    s21_set_bits((unsigned *)&Float_info.exponent, ((fu.u >> i) & 1), counter);
    counter--;
    i--;
  }
  Float_info.exponent = Float_info.exponent - 127;
  counter = 22;
  while (i > -1) {
    s21_set_bits((unsigned *)&Float_info.mantissa, ((fu.u >> i) & 1), counter);
    counter--;
    i--;
  }
  int fl_exponent = 23 - Float_info.exponent;
  dst->bits[0] = Float_info.mantissa;
  s21_set_bit(dst, 1, 23);
  if (fl_exponent > 0) {
    while (fl_exponent--) {
      if ((s21_get_bit(*dst, 0)) == 1) {
        s21_mul10(dst, 1);
        new_dec_exp += 1;
      }
      s21_shift_right(dst);
    }
  } else {
    while (fl_exponent < 0) {
      s21_shift_left(dst);
      fl_exponent++;
      if (s21_get_bits(dst->bits[2], 31) == 1) return CONVERT_ERROR;
    }
  }
  s21_decimal small = {{1, 0, 0, 1835008}};
  s21_set_info(dst, Float_info.sign, new_dec_exp);
  if (s21_is_less_abs(*dst, small)) {
    return CONVERT_ERROR;
  }
  return 0;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == NULL) return CONVERT_ERROR;
  *dst = 0;
  int minus = 1;
  long double result = 0, two = 1;
  exponent Info = {0};
  s21_get_exp(&Info, &src);
  if (Info.sign == 1) minus = -1;
  for (int k = 0; k < 96; k++) {
    if (s21_get_bit(src, k)) {
      result += two;
    }
    two *= 2;
  }
  for (int k = 0; k < Info.exponent; k++) {
    result /= 10;
  }
  *dst = minus * result;
  return 0;
}
