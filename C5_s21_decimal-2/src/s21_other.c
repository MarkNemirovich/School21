#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (&value == NULL || result == NULL) return CALCULATE_ERROR;
  s21_initialize(result);
  exponent inf_val = {0};
  s21_decimal pow = {{10, 0, 0, 0}};
  s21_get_exp(&inf_val, &value);
  value.bits[e] = 0;

  if (inf_val.exponent > 28) {
    return CALCULATE_ERROR;
  }
  if (inf_val.exponent == 0) {
    *result = value;
  } else {
    while (inf_val.exponent > 0) {
      s21_div(value, pow, result);
      value = *result;
      inf_val.exponent--;
    }
  }
  s21_set_info(result, inf_val.sign, 0);
  return OK;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (&value == NULL || result == NULL) return CALCULATE_ERROR;
  int sign = s21_get_sign(value);
  s21_copy(value, result);
  s21_set_sign(result, 1 - sign);
  return OK;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (&value == NULL || result == NULL) return CALCULATE_ERROR;
  s21_initialize(result);
  if (!s21_is_empty_mantissa(value)) {
    exponent ssign = {0};
    s21_get_exp(&ssign, &value);
    if (ssign.sign == 1) {
      s21_negate(value, &value);
    }
    s21_truncate(value, result);
    s21_decimal one = {{1, 0, 0, 0}};
    if (ssign.sign == 1 && !s21_is_equal(value, *result)) {
      s21_add(*result, one, result);
    }
    s21_set_exp(result, 0);
    if (ssign.sign == 1) {
      s21_negate(*result, result);
    }
  }
  return 0;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  if (&value == NULL || result == NULL) return CALCULATE_ERROR;
  s21_initialize(result);
  if (!s21_is_empty_mantissa(value) && !s21_is_incorrect_exponent(value)) {
    s21_decimal ostatok = {{5, 0, 0, 0}};
    s21_decimal mod_res = {0};
    s21_decimal one = {{1, 0, 0, 0}};
    exponent ssign = {0};
    s21_get_exp(&ssign, &value);
    if (ssign.sign == 1) {
      s21_negate(value, &value);
    }
    s21_truncate(value, result);
    s21_sub(value, *result, &mod_res);
    s21_set_exp(&ostatok, 1);
    if (s21_is_greater_or_equal(mod_res, ostatok)) {
      s21_add(*result, one, result);
    }
    exponent res = {0};
    s21_get_exp(&res, result);
    res.exponent = 0;
    s21_set_exp(result, res.exponent);
    if (ssign.sign) {
      s21_negate(*result, result);
    }
  }
  return 0;
}

void s21_bank_round(s21_decimal value, s21_decimal *result) {
  s21_initialize(result);
  if (!s21_is_empty_mantissa(value) && !s21_is_incorrect_exponent(value)) {
    s21_decimal left = {{5, 0, 0, 0}};
    s21_decimal right = {{6, 0, 0, 0}};
    s21_decimal mod_res = {0};
    s21_decimal one = {{1, 0, 0, 0}};
    exponent ssign = {0};
    s21_get_exp(&ssign, &value);
    if (ssign.sign == 1) {
      s21_negate(value, &value);
    }
    s21_truncate(value, result);
    s21_sub(value, *result, &mod_res);
    s21_set_exp(&right, 1);
    s21_set_exp(&left, 1);
    if (s21_is_greater_or_equal(mod_res, right) ||
        (s21_is_greater_or_equal(mod_res, left) &&
         s21_get_bit(*result, 0))) {  // нечетное
      s21_add(*result, one, result);
    }
    exponent res = {0};
    s21_get_exp(&res, result);
    res.exponent = 0;
    s21_set_exp(result, res.exponent);
    if (ssign.sign) {
      s21_negate(*result, result);
    }
  }
}
