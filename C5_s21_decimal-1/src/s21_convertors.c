#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  // 1999 -> 19,99 -> 1999,
  // dst->value = (src << 16);
  // return 0;
  if (dst == NULL) {
  } else {
    s21_clear_decimal(dst);
    if (src < 0) {
      dst->bits[3] |= MINUS_MASK;
      src *= -1;
    }
  }
  dst->bits[0] = src;
  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;
  if (dst == NULL) {
  } else {
    *dst = 0;
    if (src.bits[1] == 0 && src.bits[2] == 0) {
      int sign = 0;  // sign - знак
      if (src.bits[3] & MINUS_MASK) {
        sign = 1;  // приравниваем 1 если число отрицательное
      }
      src.bits[3] &= POWER_MASK;  // занулили наш минус
      src.bits[3] =
          src.bits[3] >> 16;  // сдвинули наш блок вправо и превратили наш
                              // условный в скейл в реальное число от 0 до 28
      *dst =
          (int)(src.bits[0] / pow(10, src.bits[3]));  // явное приведение типа
      // 2342134,34... -> 2342134
      // pow(10, src.bits[3]); // избавляемся от дробной части
      if (sign == 1) {
        *dst = -*dst;
      }
    } else {
      error = 1;
    }
  }
  return error;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = 0;
  if (dst == NULL) {
  } else if (isinf(src) || isnan(src)) {
    error = 1;
  } else if (src >= pow(2, 96) || src <= -pow(2, 96)) {
    error = 1;
  } else {
    int sign = 0;
    s21_clear_decimal(dst);
    if (src < 0) {
      sign = 1;
      src *= -1;
    }
    char string[15];
    char exp[3];
    char mant[8];

    sprintf(string, "%E", src);
    int len = strlen(string);  // мы знаем длину напечатанно строки. там должно
                               // быть 11 символов. Точно известно, что
                               // последние 2 символа это экспонента
    strcpy(exp, &string[len - 2]);
    int exponent = atoi(exp);  // функция читает целое число и строки
    if (string[len - 3] == '-') {
      exponent = -exponent;
    }

    for (int i = 0, j = 0; i < len - 4;
         i++) {  // послежние 4 символа это экспонента, их читать не надо [е+05]
      if (string[i] == '.') {
        continue;
      } else {
        mant[j] = string[i];
        j++;
      }
    }
    int mantissa = atoi(mant);
    exponent -= 6;  // сдвинули знак
    while (exponent < -28) {
      mantissa /= 10;
      exponent++;
    }
    s21_from_int_to_decimal(mantissa, dst);
    while (exponent > 0) {
      //   наша функция умножения мантиссы на 10, которой нужно передать
      s21_multiply_by_ten(*dst, dst);
      exponent--;
    }
    exponent = -exponent;
    dst->bits[3] = exponent;
    dst->bits[3] = dst->bits[3] << 16;
    if (sign == 1) {
      dst->bits[3] |= MINUS_MASK;
    }
  }

  return 0;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == NULL) {
  } else {
    *dst = 0.0f;
    int sign = 0;
    if (src.bits[3] & MINUS_MASK) {
      sign = 1;
    }
    src.bits[3] &= POWER_MASK;
    src.bits[3] = src.bits[3] >> 16;
    for (int i = 0; i < 3; i++) {  // тут считаем по блокам
      for (int j = 0; j < 32; j++) {  // тут уже считаем по битам
        *dst +=
            s21_get_bit(src.bits[i], j) *
            pow(2,
                j + (32 *
                     i));  // будет возвращать нам 0 или 1 * на знавение разряда
      }
    }
    *dst /= pow(10, src.bits[3]);
    if (sign == 1) {
      *dst = -*dst;
    }
  }
  return 0;
}