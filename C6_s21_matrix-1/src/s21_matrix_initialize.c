#include "s21_matrix.h"

/// @brief Выделение памяти для матрицы
/// @param rows
/// @param columns
/// @param matrix Структура, куда будет помещена матрица (с размерностями)
/// @return error
int s21_create_matrix(int rows, int columns, matrix_t *matrix) {
  int error = 0;
  if (rows <= 0 || columns <= 0) {
    error = 1;
  } else {
    matrix->rows = rows;
    matrix->columns = columns;
    matrix->matrix = (double **)calloc(rows, sizeof(double *));
  }
  if (!error && matrix->matrix != NULL) {
    for (int i = 0; i < rows && !error; i++) {
      matrix->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (!matrix->matrix[i]) {
        s21_free_matrix(matrix, i);
        error = 1;
      }
    }
    error = 0;
  }
  return error;
}

/// @brief Обнуление матрицы
/// @param matrix Структура матрицы с размерностями
void s21_remove_matrix(matrix_t *A) {
  if (!s21_is_Empty(A)) {
    if (A->matrix != NULL) {
      s21_free_matrix(A, A->rows);
    } else {
      A->rows = 0;
      A->columns = 0;
    }
  }
}