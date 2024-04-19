#include "s21_decimal.h"

int s21_both_zeroes(s21_decimal value_1, s21_decimal value_2) {
  return (s21_is_empty_mantissa(value_1) && s21_is_empty_mantissa(value_2));
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  if (s21_both_zeroes(value_1, value_2)) return COMPARE_TRUE;
  int result = COMPARE_FALSE;
  exponent getinfo_1 = {0};
  exponent getinfo_2 = {0};
  s21_get_exp(&getinfo_1, &value_1);
  s21_get_exp(&getinfo_2, &value_2);
  if (getinfo_1.sign == getinfo_2.sign) {
    s21_equal_exp(getinfo_1.exponent, getinfo_2.exponent, &value_1, &value_2);
    result = s21_bits_eq(value_1.bits, value_2.bits);
  }
  return result;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  if (s21_both_zeroes(value_1, value_2)) return COMPARE_FALSE;
  int result = COMPARE_TRUE;
  if ((s21_is_less_abs(value_1, value_2) == 1) &&
      (s21_get_bits(value_1.bits[e], 31) == 1) &&
      (s21_get_bits(value_2.bits[e], 31) == 1))
    result = COMPARE_FALSE;
  else if ((s21_is_less_abs(value_1, value_2) == 0) &&
           (s21_get_bits(value_1.bits[e], 31) == 1) &&
           (s21_get_bits(value_2.bits[e], 31) == 1))
    result = COMPARE_TRUE;
  else
    result = s21_is_less_abs(value_1, value_2);
  return result;
}

int s21_is_less_abs(s21_decimal value_1, s21_decimal value_2) {
  int i = MANTISSA_MAX;
  exponent getinfo_1 = {0};
  exponent getinfo_2 = {0};
  s21_get_exp(&getinfo_1, &value_1);
  s21_get_exp(&getinfo_2, &value_2);
  int res = 0;

  if (getinfo_2.sign > getinfo_1.sign) {
    res = 0;
  } else if (getinfo_1.sign > getinfo_2.sign) {
    res = 1;
  } else {
    s21_equal_exp(getinfo_1.exponent, getinfo_2.exponent, &value_1, &value_2);
    while (i >= 0) {
      int n = s21_get_bit(value_1, i);
      int m = s21_get_bit(value_2, i);
      if (n == 0 && m == 1) {
        res = 1;
        break;
      }
      if (n == 1 && m == 0) {
        res = 0;
        break;
      }
      i--;
    }
  }
  return res;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  if (s21_both_zeroes(value_1, value_2))
    return COMPARE_FALSE;
  else
    return s21_is_less(value_2, value_1);
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}
