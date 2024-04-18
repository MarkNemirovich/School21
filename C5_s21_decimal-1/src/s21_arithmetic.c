#include "s21_decimal.h"

/// Set equal pow for both decimals
/// @param value_1 First decimal
/// @param value_2 Second decimal
/// @return is can't be shifted
int s21_align_pows(s21_decimal *value_1, s21_decimal *value_2) {
  int error = 0;
  int exp_1 = s21_get_pow(*value_1);
  int exp_2 = s21_get_pow(*value_2);
  // set equal (max) power for both decimal numbers and for result
  int diff = exp_1 - exp_2;
  if (diff > 0) {
    while (diff-- > 0 && s21_get_pow(*value_1) > 0 &&
           !s21_get_bit(value_1->bits[2], 31) && !error)
      error = s21_multiply_by_ten(*value_1, value_1);
    while (diff-- > 0 &&
           (s21_get_pow(*value_2) < 28 || !s21_is_empty_decimal(*value_2)))
      s21_divide_by_ten(*value_2, value_2);
  } else {
    while (diff++ < 0 && s21_get_pow(*value_2) > 0 &&
           !s21_get_bit(value_2->bits[2], 31) && !error)
      error = s21_multiply_by_ten(*value_2, value_2);
    while (diff++ < 0 &&
           (s21_get_pow(*value_1) < 28 || !s21_is_empty_decimal(*value_1)))
      s21_divide_by_ten(*value_1, value_1);
  }
  return error;
}

/// Compare manteeses
/// @param value_1 First decimal
/// @param value_2 Second decimal
/// @return bigger first = 1, second = -1, equal = 0
int s21_compare_manteeses(s21_decimal value_1, s21_decimal value_2) {
  s21_align_pows(&value_1, &value_2);
  int normal = 0;
  for (int i = 95; i >= 0 && normal == 0; i--) {
    normal = s21_get_bit(value_1.bits[i / 32], i % 32) -
             s21_get_bit(value_2.bits[i / 32], i % 32);
  }
  return normal;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  // get signes (both positives or negative, add abs values and set sign)
  int abs = s21_compare_manteeses(value_1, value_2);
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  // from positive sub negative number
  if (sign_1 > sign_2) {  // 1 - negative
    s21_set_sign(&value_1, 0);
    error = s21_sub(value_2, value_1, result);
  } else if (sign_1 < sign_2) {
    s21_set_sign(&value_2, 0);
    error = s21_sub(value_1, value_2, result);
  } else {
    // set equal pow for both decimals
    error = (1 + sign_1) * s21_align_pows(&value_1, &value_2);
    s21_set_pow(result, s21_get_pow(value_1));
    // sum manteeses
    if (!error) error = (1 + sign_1) * s21_bit_sum(value_1, value_2, result);
    //  s21_copy_decimal(result, value_1);
  }
  if (abs >= 0) {
    s21_set_sign(result, sign_1);
  } else {
    s21_set_sign(result, sign_2);
  }
  if (error != 0) s21_clear_decimal(result);
  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  // get signes (both positives or negative, add abs values and set sign)
  int abs = s21_compare_manteeses(value_1, value_2);
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  // -f-s == -(f+s) and f-(-s)= f+s
  if ((!sign_1 && sign_2) || (sign_1 && !sign_2)) {
    s21_set_sign(&value_1, sign_1);  // set first number sign
    s21_set_sign(&value_2, sign_1);  // set first number sign too
    error =
        (1 + sign_1) * s21_add(value_1, value_2, result);  // too big or small
  } else {
    error = s21_align_pows(&value_1, &value_2);
    if (abs >= 0) {
      error = 2 * s21_bit_sub(value_1, value_2, result);
      s21_set_pow(result, s21_get_pow(value_1));
      s21_set_sign(result, sign_1);
    } else {
      error = 2 * s21_bit_sub(value_2, value_1, result);
      s21_set_pow(result, s21_get_pow(value_2));
      s21_set_sign(result, !sign_2);
    }
    //   s21_copy_decimal(result, value_2);
  }
  if (error != 0) s21_clear_decimal(result);
  return error;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  // get signes (both positives or negative, add abs values and set sign)
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  error = s21_align_pows(&value_1, &value_2);
  int abs = s21_compare_manteeses(value_1, value_2);
  int edge_1, edge_2;
  if (!error) {
    // find max shift we can allow
    for (int i = 95; i >= 0 && (!edge_1 || !edge_2); i--) {
      if (!edge_1 && s21_get_bit(value_1.bits[i / 32], i % 32)) edge_1 = i;
      if (!edge_2 && s21_get_bit(value_2.bits[i / 32], i % 32)) edge_2 = i;
    }
    // divide till shift will be suitable
    while (edge_1 + edge_2 > 95 && s21_get_pow(value_1) < 28) {
      s21_divide_by_ten(value_1, &value_1);
      s21_divide_by_ten(value_2, &value_2);
      edge_1--;
      edge_2--;
    }
    if (abs >= 0) {
      s21_set_pow(result, s21_get_pow(value_1));
      s21_decimal shifted = {0};
      for (int i = 0; i < 96; i++) {
        s21_copy_decimal(&shifted, value_1);
        s21_shift_right(&shifted, i);
        if (s21_get_bit(value_2.bits[i / 32], i % 32)) {
          s21_bit_sum(value_1, shifted, result);
        }
      }
    } else {
      s21_set_pow(result, s21_get_pow(value_2));
      s21_decimal shifted = {0};
      for (int i = 0; i < 96; i++) {
        s21_copy_decimal(&shifted, value_2);
        s21_shift_right(&shifted, i);
        if (s21_get_bit(value_1.bits[i / 32], i % 32)) {
          s21_bit_sum(value_2, shifted, result);
        }
      }
    }
    s21_set_sign(result, sign_1 != sign_2);
  }
  return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  // get signes (both positives or negative, add abs values and set sign)
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  s21_align_pows(&value_1, &value_2);
  // exclude division by 0
  error = 3 * s21_is_empty_decimal(value_2);
  if (!error) {
    int abs = s21_compare_manteeses(value_1, value_2);
    // result will be < 0
    if (abs < 0)
      s21_clear_decimal(result);
    else {
      s21_decimal one = {{1, 0, 0, 0}};
      while (s21_bit_sub(value_1, value_2, &value_1) == 0) {
        s21_bit_sum(*result, one, result);  // add 1 every successfull sub
        s21_shift_left(result, 1);
      }
      s21_shift_right(result, 1);
    }
  }
  return error;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  // get signes (both positives or negative, add abs values and set sign)
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  error = s21_align_pows(&value_1, &value_2);
  // exclude division by 0
  error = 3 * s21_is_empty_decimal(value_2);
  if (!error) {
    int abs = s21_compare_manteeses(value_1, value_2);
    // result will be < 0
    if (abs < 0)
      s21_clear_decimal(result);
    else {
      s21_decimal one = {{1, 0, 0, 0}};
      while (s21_bit_sub(value_1, value_2, &value_1) == 0) {
        s21_copy_decimal(result, value_1);  // save rest
      }
    }
  }
  return error;
}