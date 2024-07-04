#include "s21_matrix.h"
/// @brief Нахождение суммы матриц
/// @param A Структура первой матрицы с размерностями
/// @param B Структура второй матрицы с размерностями
/// @param result Результатирующая структура
/// @return error
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = s21_is_Empty(A) || s21_is_Empty(B);
  if (!error) error = 2 * ((A->rows != B->rows) || (A->columns != B->columns));
  if (!error) error = s21_create_matrix(A->rows, A->columns, result);
  if (!error) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return error;
}
/// @brief Нахождение разницы матриц
/// @param A Структура первой матрицы с размерностями
/// @param B Структура второй матрицы с размерностями
/// @param result Результатирующая структура
/// @return error
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = s21_is_Empty(A) || s21_is_Empty(B);
  if (!error) error = 2 * ((A->rows != B->rows) || (A->columns != B->columns));
  if (!error) error = s21_create_matrix(A->rows, A->columns, result);
  if (!error) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return error;
}
/// @brief Нахождение произведения матриц
/// @param A Структура первой матрицы с размерностями
/// @param B Структура второй матрицы с размерностями
/// @param result Результатирующая структура
/// @return error
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = s21_is_Empty(A) || s21_is_Empty(B);
  if (!error) error = 2 * (A->columns != B->rows);
  if (!error) error = s21_create_matrix(A->rows, B->columns, result);
  if (!error) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < B->rows; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return error;
}
/// @brief Умножение матрицы на число
/// @param A Структура матрицы с размерностями
/// @param double Число
/// @param result Результатирующая структура
/// @return error
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = s21_is_Empty(A);
  if (!error) error = s21_create_matrix(A->rows, A->columns, result);
  if (!error) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return error;
}