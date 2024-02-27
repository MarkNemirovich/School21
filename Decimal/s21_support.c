#include "s21_decimal.h"

/// @brief Check for existing
/// @param value 4-byte value 
/// @return result
int s21_is_empty_decimal(s21_decimal value) {
    return (value.bits[0] || value.bits[1] || value.bits[2]) ? 0 : 1;
}

/// @brief Clean decimal number
/// @param value Decimal number 
void s21_clean_decimal(s21_decimal *value) {
    for (int i = 0; i < 4; i++) value->bits[i] = 0;
}

/// @brief Get sign from decimal number
/// @param value Decimal number 
/// @return sign
int s21_get_sign(s21_decimal value) { return s21_get_bit(value.bits[3], 31); }

/// @brief Get sign from decimal number
/// @param value Decimal number 
/// @param sign sign: 0 = + and 1 = -
void s21_set_sign(s21_decimal *value, int sign) { s21_set_bit(value->bits[3], 31, sign); }

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

/// @brief Get scale: bits 16 - 23 from last 4-byte
/// @param value Decimal number 
/// @return Scale
int s21_get_pow(s21_decimal value) { return (value.bits[3] << 1) >> 17; }

/// @brief Set scale: bits 16 - 23 from last 4-byte
/// @param value Decimal number 
/// @param scale Scale
void s21_set_pow(s21_decimal *value, int scale) {
    value->bits[3] &= MINUS;
    value->bits[3] |= scale << 16;
}

/// @brief Check for existing
/// @param value 7-byte value 
/// @return result
int s21_is_empty_long_decimal(s21_long_decimal value) {
    return (value.bits[3] + value.bits[4] + value.bits[5] + value.bits[6]) ? 0
                                                                           : 1;
}

/// @brief Clean long decimal number
/// @param value Long decimal number 
void s21_clean_long_decimal(s21_long_decimal *value) {
    for (int i = 0; i < 7; i++) {
        value->bits[i] = 0;
    }
}