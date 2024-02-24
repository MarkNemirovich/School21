#include "s21_matrix.h"

/// @brief Проверка матрицы на ее существование
/// @param A Структура матрицы с размерностям
/// @return успешность выполнения
int s21_is_Empty(matrix_t *A) {
  int res = 0;
  if (A == NULL || A->matrix == NULL || A->rows <= 0 ||
      A->columns <= 0) {
    res = 1;
  } else {
    res = 0;
  }
  return res;
}
/// @brief Освобождение памяти из под матрицы
/// @param A Структура матрицы с размерностям
/// @param rows Количество строк, которые нужно освободить
void s21_free_matrix(matrix_t *A, int rows) {
  for (int i = 0; i < rows; i++) free(A->matrix[i]);
  free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}
/// @brief Нахождение детерминанта матрицы
/// @param A Структура матрицы с размерностями
/// @return Детерминант
double s21_get_determinant(matrix_t *A) {
  double det = 0.0;
  if (A->rows == 1) {  // если матрица 1x1
    det = A->matrix[0][0];
  } else {
    matrix_t tmp = {0};
    s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);
    for (int i = 0; i < A->columns; i++) {
      s21_get_matrix(0, i, A, &tmp);
      if (i % 2) {
        det -= A->matrix[0][i] * s21_get_determinant(&tmp);
      } else {
        det += A->matrix[0][i] * s21_get_determinant(&tmp);
      }
    }
    s21_remove_matrix(&tmp);
  }
  return det;
}
/// @brief Получение подматрицы, исключая указанные строку и столбец
/// @param row строка, которую не нужно помещать в подматрицу
/// @param col столбец, который не нужно помещать в подматрицу
/// @param A Структура матрицы с размерностями
/// @param result Результатирующая структура
void s21_get_matrix(int row, int col, matrix_t *A, matrix_t *result) {
  int m_row = 0, m_col = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i != row) {
      m_col = 0;
      for (int j = 0; j < A->columns; j++) {
        if (j != col) {
          result->matrix[m_row][m_col] = A->matrix[i][j];
          m_col++;
        }
      }
      m_row++;
    }
  }
}