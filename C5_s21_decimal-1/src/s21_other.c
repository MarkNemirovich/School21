#include "s21_decimal.h"

/// @brief Округляет указанное Decimal число до ближайшего целого числа в
/// сторону отрицательной бесконечности.
/// @param dec структура которую хотим изменить
/// @param result стркутра для записи нового числа
/// @return 1 или 0, в зависимости от успешности выполнения
int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_clear_decimal(result);
  s21_truncate(value, result);
  if (s21_get_sign(value) && !s21_is_equal(*result, value)) {
    s21_sub(*result, ((s21_decimal){{1, 0, 0, 0}}), result);
  }
  return 0;
}

/// @brief Rounds a decimal value to the nearest integer
/// @param dec структура которую хотим изменить
/// @param result стркутра для записи нового числа
/// @return 1 или 0, в зависимости от успешности выполнения
int s21_round(s21_decimal value, s21_decimal *result) {
  s21_clear_decimal(result);
  float fl_to_round = 0.0;
  float difference = 0;
  s21_from_decimal_to_float(value, &fl_to_round);
  fl_to_round = round(fl_to_round);
  if (fl_to_round < 0.0) {
    s21_set_bit(&result->bits[3], 31, 1);

    fl_to_round *= -1;
  }
  for (int i = 0; fl_to_round >= 1 && i < START_INFO; i++) {
    fl_to_round = floor(fl_to_round) / 2;
    difference = fl_to_round - floor(fl_to_round);
    if (difference > 0.0) {
      s21_set_bit(&result->bits[i / 32], i % 32, 1);
    } else {
      s21_set_bit(&result->bits[i / 32], i % 32, 0);
    }
  }
  s21_set_pow(result, 0);
  return 0;
}

/// @brief Возвращает целове число, отбрасывая дробную часть
/// @param dec структура которую хотим изменить
/// @param result стркутра для записи нового числа
/// @return 1 или 0, в зависимости от успешности выполнения
int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_clear_decimal(result);
  float difference = 0;
  if (s21_get_pow(value)) {
    float fl_to_int = 0.0;
    s21_from_decimal_to_float(value, &fl_to_int);
    fl_to_int = trunc(fl_to_int);
    if (fl_to_int < 0.0) {
      s21_set_bit(&result->bits[3], 31, 1);

      fl_to_int *= -1;
    }
    for (int i = 0; fl_to_int >= 1 && i < START_INFO; i++) {
      fl_to_int = floor(fl_to_int) / 2;
      difference = fl_to_int - floor(fl_to_int);
      if (difference > 0.0) {
        s21_set_bit(&result->bits[i / 32], i % 32, 1);
      } else {
        s21_set_bit(&result->bits[i / 32], i % 32, 0);
      }
    }
    s21_set_pow(result, 0);
  } else {
    for (int i = 0; i < 4; ++i) {
      result->bits[i] = value.bits[i];
    }
  }
  return 0;
}

/// @brief Перевод числа в его fabs состояние
/// @param dec структура которую хотим изменить
/// @param result  стркутра для записи нового числа
/// @return 1 или 0, в зависимости от успешности выполнения
int s21_negate(s21_decimal dec, s21_decimal *result) {
  s21_clear_decimal(result);
  int sign = s21_get_sign(dec);
  *result = dec;
  if (sign == 1) {
    s21_set_bit(&result->bits[3], 31, 0);

  } else {
    s21_set_bit(&result->bits[3], 31, 1);
  }
  return 0;
}