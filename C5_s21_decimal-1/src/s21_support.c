#include "s21_decimal.h"

/// @brief Check for existing
/// @param value 4-byte value
/// @return result
int s21_is_empty_decimal(s21_decimal value) {
  return (value.bits[0] || value.bits[1] || value.bits[2]) ? 0 : 1;
}

/// @brief Check is all reserved bits zeros
/// @param value Decimal value
/// @return Is all zeros than 1
int s21_is_reserved_bits_ok(s21_decimal value) {
  int bits, i;
  for (i = 0; i < 16; i++) {
    bits += s21_get_bit(value.bits[3], i);
  }
  for (i = 24; i < 31; i++) {
    bits += s21_get_bit(value.bits[3], i);
  }
  return bits == 0;
}

/// @brief Clear decimal number
/// @param value Decimal number
void s21_clear_decimal(s21_decimal *value) {
  for (int i = 0; i < 4; i++) value->bits[i] = 0;
}

/// @brief Get sign from decimal number
/// @param value Decimal number
/// @return sign
int s21_get_sign(s21_decimal value) { return s21_get_bit(value.bits[3], 31); }

/// @brief Get sign from decimal number
/// @param value Decimal number
/// @param sign sign: 0 = + and 1 = -
void s21_set_sign(s21_decimal *value, int sign) {
  s21_set_bit(&(value->bits[3]), 31, sign);
}

/// @brief Get bit from 4-byte number
/// @param x 4-byte
/// @param i Bit index (0-31)
/// @return Bit value
int s21_get_bit(unsigned int x, int i) {
  unsigned int mask = 1u << i;
  return (x & mask) ? 1 : 0;
}

/// @brief Set bit in 4-byte number
/// @param x 4-byte
/// @param i Bit index
/// @param bit Bit value
void s21_set_bit(unsigned int *x, int i, int bit) {
  int y = 1u << i;
  *x = bit ? *x | y : *x & (~y);
}

/// @brief Get power: bits 16 - 23 from last 4-byte
/// @param value Decimal number
/// @return Power
int s21_get_pow(s21_decimal value) { 
  int pow = (POWER_MASK & value.bits[3]) >> 16;
  return pow;
  }

/// @brief Set power: bits 16 - 23 from last 4-byte
/// @param value Decimal number
/// @param pow Power
void s21_set_pow(s21_decimal *value, int pow) {
  int sign = s21_get_sign(*value);
  value->bits[3] = 0;
  pow <<= 16;
  value->bits[3] = pow | sign;
}

/// @brief Shift mantees to the left
/// @param value Decimal number will be changed
/// @param shift Shift bits amount
void s21_shift_left(s21_decimal *value, int shift) {
  int i = 95;
  for (; i > shift; i--) {
    s21_set_bit(&(value->bits[i / 32]), i % 32,
                s21_get_bit(value->bits[(i - shift) / 32], (i - shift) % 32));
  }
  for (; i >= 0; i--) s21_set_bit(&(value->bits[i / 32]), i % 32, 0);
}

/// @brief Shift mantees to the right
/// @param value Decimal number will be changed
/// @param shift Shift bits amount
void s21_shift_right(s21_decimal *value, int shift) {
  int i = 0;
  for (; i < 96 - shift; i++) {
    s21_set_bit(&(value->bits[i / 32]), i % 32,
                s21_get_bit(value->bits[(i + shift) / 32], (i + shift) % 32));
  }
  for (; i < 96; i++) s21_set_bit(&(value->bits[i / 32]), i % 32, 0);
}

int s21_multiply_by_ten(s21_decimal value, s21_decimal *result) {
  int error = 0;
  s21_set_pow(result, s21_get_pow(*result) - 1);
  if (s21_get_bit(value.bits[2], 31) || s21_get_bit(value.bits[2], 30) ||
      s21_get_bit(value.bits[2], 29))
    error = 1;
  else {
    s21_decimal small = {{value.bits[0] << 1, value.bits[1] << 1,
                          value.bits[2] << 1, value.bits[3]}};
    s21_decimal big = {{value.bits[0] << 3, value.bits[1] << 3,
                        value.bits[2] << 3, value.bits[3]}};
    error = s21_bit_sum(small, big, result);
  }
  return error;
}

/// @brief Shift mantees to the right
/// @param value Decimal number will be changed
/// @param shift Shift bits amount
void s21_divide_by_ten(s21_decimal value, s21_decimal *result) {
  s21_decimal quotient = {0};
  s21_set_pow(&quotient, s21_get_pow(value) + 1);
  int k = 0;
  // division by 10 (1010 in binary) from highest to lowest bits
  // save rest in the value, but quotient in the answer
  for (int i = 95; i >= 3; i--) {
    int a = s21_get_bit(value.bits[(i - 0) / 32], (i - 0) % 32);
    int b = s21_get_bit(value.bits[(i - 1) / 32], (i - 1) % 32);
    int c = s21_get_bit(value.bits[(i - 2) / 32], (i - 2) % 32);
    int d = s21_get_bit(value.bits[(i - 3) / 32], (i - 3) % 32);
    int e = 0;
    if (a * 8 + b * 4 + c + 2 + d >=
        10)  // when 1100 or 1010 or 1101 or 1011 or 1110 or 1111
    {
      s21_set_bit(&(value.bits[(i - 0) / 32]), (i - 0) % 32, 0);
      s21_set_bit(&(value.bits[(i - 1) / 32]), (i - 1) % 32, b + c - 1);
      s21_set_bit(&(value.bits[(i - 2) / 32]), (i - 2) % 32, b > c);
      s21_set_bit(&(value.bits[(i - 3) / 32]), (i - 3) % 32, d);
      i -= 3;  // 1 at any time, 3 if succeess
      quotient.bits[0] |= 1;
    } else if (i > 3)  // when 1000 or 1001 become 10000 and 10001
    {
      e = s21_get_bit(value.bits[(i - 4) / 32], (i - 4) % 32);
      s21_set_bit(&(value.bits[(i - 0) / 32]), (i - 0) % 32, 0);
      s21_set_bit(&(value.bits[(i - 1) / 32]), (i - 1) % 32, 1);
      s21_set_bit(&(value.bits[(i - 2) / 32]), (i - 2) % 32, 1);
      s21_set_bit(&(value.bits[(i - 3) / 32]), (i - 3) % 32, 1 - d);
      s21_set_bit(&(value.bits[(i - 4) / 32]), (i - 4) % 32, e);
      i -= 4;  // 1 at any time, 3 next, 1 addictive
      s21_shift_left(&quotient, 1);
      quotient.bits[0] |= 1;
    }
    if (i >= 3)
      s21_shift_left(&quotient, 1);
    else
      s21_shift_left(&quotient, i);
    k++;
  }
  s21_copy_decimal(result, quotient);
}

/// @brief Sum bits one by one from two decimals
/// @param value_1 First decimal
/// @param value_2 Second decimal
/// @param result Result decimal changes only if success
/// @return is surplus
int s21_bit_sum(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int reminded = 0;
  int i = 0;
  s21_decimal new_decimal = {0};
  s21_set_pow(&new_decimal, s21_get_pow(*result));
  s21_set_sign(&new_decimal, s21_get_sign(*result));
  for (; i < 96; i++) {
    int first = s21_get_bit(value_1.bits[i / 32], i % 32) + reminded;
    int second = s21_get_bit(value_2.bits[i / 32], i % 32);
    // set current bit 1+0=1    1+1=0    0+0=0
    s21_set_bit(&(new_decimal.bits[i / 32]), i % 32, (first + second) % 2);
    // set next bit 1+0=0    1+1=1    0+0=0
    reminded = (first + second) / 2;
  }
  if (reminded != 0 && s21_get_pow(new_decimal) < 28) {
    s21_divide_by_ten(new_decimal, &new_decimal);
    s21_decimal over = {{429496729, 642949672, 964294967, 0}};
    s21_bit_sum(new_decimal, over, &new_decimal);
    reminded = 0;
  }
  if (reminded == 0) s21_copy_decimal(result, new_decimal);
  return reminded;
}

/// @brief Sum bits one by one from two decimals
/// @param value_1 First decimal
/// @param value_2 Second decimal
/// @param result Result decimal changes only if success
/// @return is lack
int s21_bit_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int debt = 0;
  s21_decimal new_decimal = {0};
  for (int i = 0; i < 96; i++) {
    int first = s21_get_bit(value_1.bits[i / 32], i % 32) - debt;
    int second = s21_get_bit(value_2.bits[i / 32], i % 32);
    if (second > first) {
      first += 2;
      debt = 1;
    } else
      debt = 0;
    // set current bit 1-0=1    1-1=0    0-0=0 0-1=1 (debt = 2)
    s21_set_bit(&(new_decimal.bits[i / 32]), i % 32, first - second);
    // set next bit 1-0=0    1-1=0    0-0=0 0-1=-1
  }
  if (debt == 0) s21_copy_decimal(result, new_decimal);
  return debt;
}

/// @brief Copy one decimal to another
/// @param value_1 Where we copy
/// @param value_2 What we copy
void s21_copy_decimal(s21_decimal *value_1, s21_decimal value_2) {
  for (int i = 0; i < 128; i++) {
    s21_set_bit(&(value_1->bits[i / 32]), i % 32,
                s21_get_bit(value_2.bits[i / 32], i % 32));
  }
}