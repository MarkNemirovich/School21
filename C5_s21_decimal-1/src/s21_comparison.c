#include "s21_decimal.h"

void s21_comparison_reverse(int *flag) {
  if (*flag == 1) {
    *flag = 2;
  } else if (*flag == 2) {
    *flag = 1;
  }
}

int s21_comparison_bits(s21_decimal value_1, s21_decimal value_2) {
  int bit1 = 0;
  int bit2 = 0;
  int flag = 0;
  for (int j = 2; j >= 0 && !flag; j--) {
    for (int i = 31; i >= 0 && !flag; --i) {
      bit1 = s21_get_bit(value_1.bits[j], i);
      bit2 = s21_get_bit(value_2.bits[j], i);
      if (bit1 > bit2) {
        flag = 1;
      } else if (bit1 < bit2) {
        flag = 2;
      }
    }
  }
  return flag;
}

int s21_greater_num(int a, int b) {
  int flag = 0;
  if (a > b) {
    flag = 1;
  } else if (a < b) {
    flag = 2;
  } else if (a == b) {
    flag = 0;
  }
  return flag;
}

int s21_comparison(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0;
  int scale_dif = (s21_get_pow(value_1) - s21_get_pow(value_2));
  s21_align_pows(&value_1, &value_2);
  flag = s21_greater_num(!s21_get_sign(value_1), !s21_get_sign(value_2));
  if (flag == 0) {
    if (scale_dif >= 0) {
      flag = s21_comparison_bits(value_1, value_2);
    } else {
      scale_dif = -scale_dif;
      flag = s21_comparison_bits(value_1, value_2);
      s21_comparison_reverse(&flag);
    }
    if (s21_get_sign(value_1) && s21_get_sign(value_2)) {
      s21_comparison_reverse(&flag);
    }
  } else {
    if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0 &&
        value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
      flag = 0;
    }
  }
  return flag;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  return (s21_comparison(value_1, value_2) == 0) ? 1 : 0;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return (s21_comparison(value_1, value_2) == 0) ? 0 : 1;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  return (s21_comparison(value_1, value_2) == 2) ? 1 : 0;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return (s21_comparison(value_1, value_2) == 2) ||
                 (s21_comparison(value_1, value_2) == 0)
             ? 1
             : 0;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return (s21_comparison(value_1, value_2) == 1) ? 1 : 0;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return (s21_comparison(value_1, value_2) == 1) ||
                 (s21_comparison(value_1, value_2) == 0)
             ? 1
             : 0;
}