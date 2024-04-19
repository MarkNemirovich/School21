#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL) return OK;
  exponent getinfo_1 = {0};
  exponent getinfo_2 = {0};
  s21_get_exp(&getinfo_1, &value_1);
  s21_get_exp(&getinfo_2, &value_2);

  if (getinfo_1.sign == getinfo_2.sign) {
    int max = 0;
    max = s21_equal_exp(getinfo_1.exponent, getinfo_2.exponent, &value_1,
                        &value_2);
    if (s21_pre_add(value_1, value_2, result) == 1) {
      if (getinfo_1.sign == 1 && max == 0) {
        s21_initialize(result);
        return TOO_SMALL_OR_NEG_INF;
      } else if (getinfo_1.sign == 0 && max == 0) {
        s21_initialize(result);
        return TOO_LARGE_OR_INF;
      } else if (max != 0) {
        s21_set_exp(&value_1, 1);
        s21_set_exp(&value_2, 1);
        s21_round(value_1, &value_1);
        s21_round(value_2, &value_2);
        max--;
        s21_pre_add(value_1, value_2, result);
      }
    }
    s21_set_info(result, getinfo_1.sign, max);
  } else if (getinfo_1.sign == 1) {
    s21_set_info(&value_1, 0, getinfo_1.exponent);
    return (s21_sub(value_2, value_1, result));
  } else if (getinfo_2.sign == 1) {
    s21_set_info(&value_2, 0, getinfo_2.exponent);
    return (s21_sub(value_1, value_2, result));
  }
  return OK;
}

int s21_equal_exp(unsigned exp1, unsigned exp2, s21_decimal *value_1,
                  s21_decimal *value_2) {
  int max = exp1;
  int exp_diff = exp1 - exp2;

  if (exp_diff != 0) {
    if (exp_diff > 0) {
      s21_decimal buff;
      int done = 0;
      do {
        buff = *value_2;
        if (s21_mul10(value_2, 1) == 1) {
          *value_2 = buff;
          done = 1;
        } else
          exp_diff--;
      } while (exp_diff > 0 && done == 0);

      if (exp_diff > 0) {
        s21_set_exp(value_1, exp_diff);
        buff = *value_1;
        s21_bank_round(buff, value_1);
      }
    } else {
      max = exp2;
      exp_diff = exp2 - exp1;
      int done = 0;
      s21_decimal buff;
      do {
        buff = *value_1;
        if (s21_mul10(value_1, 1) == 1) {
          *value_1 = buff;
          done = 1;
        } else
          exp_diff--;
      } while (exp_diff > 0 && done == 0);

      if (exp_diff > 0) {
        s21_set_exp(value_2, exp_diff);
        buff = *value_2;
        s21_bank_round(buff, value_2);
      }
    }
  }
  return max - exp_diff;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL) return OK;
  exponent exp_1 = {0}, exp_2 = {0};
  int res = OK, flag = 0, sign = 0;
  if (s21_is_less_abs(value_1, value_2) &&
      s21_get_bits(value_1.bits[e], 31) == s21_get_bits(value_2.bits[e], 31)) {
    s21_swap(&value_1, &value_2);
    flag = 1;
    if (s21_get_bits(value_1.bits[e], 31)) sign = 1;
  }
  s21_get_exp(&exp_1, &value_1);
  s21_get_exp(&exp_2, &value_2);
  if (exp_1.sign == 0 && exp_2.sign == 0) {
    int max = s21_equal_exp(exp_1.exponent, exp_2.exponent, &value_1, &value_2);
    if (s21_pre_sub(value_1, value_2, result) == 2) {
      s21_initialize(result);
      return TOO_SMALL_OR_NEG_INF;
    }
    s21_set_info(result, exp_1.sign, max);
    if (flag == 1) s21_set_sign(result, 1);
  }
  if (exp_1.sign == 0 && exp_2.sign == 1) {
    s21_set_bits(&value_2.bits[e], 0, 31);
    if ((s21_add(value_1, value_2, result)) == 1) {
      s21_initialize(result);
      return TOO_LARGE_OR_INF;
    }
  }
  if (exp_1.sign == 1 && exp_2.sign == 0) {
    s21_set_bits(&value_1.bits[e], 0, 31);
    if ((s21_add(value_1, value_2, result)) == 1) {
      s21_initialize(result);
      return TOO_SMALL_OR_NEG_INF;
    }
    s21_set_sign(result, 1);
  }
  if (exp_1.sign == 1 && exp_2.sign == 1) {
    int max = s21_equal_exp(exp_1.exponent, exp_2.exponent, &value_1, &value_2);
    if (s21_pre_sub(value_1, value_2, result) == 2) {
      s21_initialize(result);
      return TOO_SMALL_OR_NEG_INF;
    }
    s21_set_exp(result, max);
    if (s21_is_less(value_1, value_2) && flag == 0) {
      s21_set_bits(&result->bits[e], 1, 31);
    } else if (s21_is_less(value_2, value_1)) {
      s21_set_bits(&result->bits[e], !sign, 31);
    }
  }
  return res;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL) return OK;
  s21_initialize(result);
  exponent val_1 = {0}, val_2 = {0};
  s21_get_exp(&val_1, &value_1);
  s21_get_exp(&val_2, &value_2);
  if (val_1.exponent + val_2.exponent > 28) {
    s21_initialize(result);
    return TOO_SMALL_OR_NEG_INF;
  }
  s21_decimal tmp = {0};
  for (int i = 0; i <= MANTISSA_MAX; i++) {
    int bit_2 = s21_get_bit(value_2, i);
    for (int k = 0; k < 96; k++) {
      int bit_1 = s21_get_bit(value_1, k);
      s21_set_bits(&tmp.bits[k / 32], bit_1 & bit_2, k);
    }
    if (((s21_get_bits(result->bits[top], 31) == 1 && i != MANTISSA_MAX) ||
         s21_get_bits(tmp.bits[top], 31) == 1) &&
        tmp.bits[low] != 0 && tmp.bits[mid] != 0 && tmp.bits[top] != 0) {
      if (val_1.sign == val_2.sign) {
        s21_initialize(result);
        return TOO_LARGE_OR_INF;
      } else {
        s21_initialize(result);
        return TOO_SMALL_OR_NEG_INF;
      }
    }
    for (int j = 0; i != 0 && j < i; j++) {
      if (s21_get_bits(tmp.bits[top], 31) == 1) {
        s21_initialize(result);
        return 1 + (val_1.sign != val_2.sign);
      }
      s21_shift_left(&tmp);
    }
    s21_pre_add(tmp, *result, result);
    tmp.bits[low] = tmp.bits[mid] = tmp.bits[top] = 0;
    if (val_1.exponent || val_2.exponent) {
      result->bits[e] = val_1.exponent + val_2.exponent;
      result->bits[e] <<= 16;
    }
    if (val_1.sign == val_2.sign)
      s21_set_bits(&result->bits[e], 0, 31);
    else
      s21_set_bits(&result->bits[e], 1, 31);
  }
  return OK;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL) return OK;
  s21_initialize(result);
  if (s21_is_empty_mantissa(value_2)) return DIV_BY_ZERO;
  exponent val_1 = {0}, val_2 = {0};
  s21_get_exp(&val_1, &value_1);
  s21_get_exp(&val_2, &value_2);
  if (val_1.exponent || val_2.exponent) {
    result->bits[e] = val_1.exponent - val_2.exponent;
    result->bits[e] <<= 16;
  }
  if (val_1.sign == val_2.sign) {
    s21_set_bits(&result->bits[e], 0, 31);
  } else {
    s21_set_bits(&result->bits[e], 1, 31);
  }
  if (value_2.bits[e] > 0) {
    for (int k = 0; k < 32; k++) {
      s21_set_bits(&value_2.bits[e], 0, k % 32);
    }
  }
  int i = MANTISSA_MAX;
  while (s21_get_bit(value_1, i) == 0) i--;
  int sub_times = 0;
  s21_decimal tmp = {0};
  for (; i >= 0; i--) {
    s21_shift_left(&tmp);
    s21_set_bit(&tmp, s21_get_bit(value_1, i), 0);
    if (s21_is_greater_or_equal(tmp, value_2)) {
      sub_times += 1;
      s21_shift_left(result);
      s21_set_bit(result, 1, 0);
      s21_sub(tmp, value_2, &tmp);
    } else if (sub_times != 0) {
      s21_shift_left(result);
    }
  }
  return OK;
}