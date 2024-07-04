#include "s21_matrix.h"
/// @brief Сравнение матриц
/// @param A Структура первой матрицы с размерностями
/// @param B Структура второй матрицы с размерностями
/// @return результат выполнения
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  double a, b, power = pow(10, 7);
  if (!s21_is_Empty(A) && !s21_is_Empty(B) && A->rows == B->rows &&
      A->columns == B->columns) {
    for (int i = 0; i < A->rows && result; i++) {
      for (int j = 0; j < A->columns && result; j++) {
        a = round(A->matrix[i][j] * power);
        b = round(B->matrix[i][j] * power);
        if (a != b) result = FAILURE;
      }
    }
  } else {
    result = FAILURE;
  }
  return result;
}