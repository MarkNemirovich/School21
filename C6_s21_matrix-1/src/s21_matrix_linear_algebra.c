#include "s21_matrix.h"
/// @brief Транспонирование матрицы
/// @param A Структура матрицы с размерностями
/// @param result Результатирующая структура
/// @return error
int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = s21_is_Empty(A);
  if (!error) error = s21_create_matrix(A->columns, A->rows, result);
  if (!error) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return error;
}
/// @brief Детерминант матрицы
/// @param A Структура матрицы с размерностями
/// @param result Результатирующая структура
/// @return error
int s21_determinant(matrix_t *A, double *result) {
  *result = 0.0;
  int error = s21_is_Empty(A);
  if (!error) error = 2 * (A->columns != A->rows);
  if (!error) *result = s21_get_determinant(A);
  return error;
}
/// @brief Минор матрицы
/// @param A Структура матрицы с размерностями
/// @param result Результатирующая структура
/// @return error
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = s21_is_Empty(A);
  if (!error) error = 2 * (A->columns != A->rows);
  if (!error) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t minor = {0};
        double determinant = 0;
        s21_create_matrix(A->columns - 1, A->rows - 1, &minor);
        s21_get_minor(i, j, A, &minor);
        s21_determinant(&minor, &determinant);
        result->matrix[i][j] = pow(-1, (i + j)) * determinant;
        s21_remove_matrix(&minor);
      }
    }
  }
  return error;
}
/// @brief Обратная матрица
/// @param A Структура, которая хранит в себе массив, а также rows and columns
/// @param result Стрктура для записи результата
/// @return успешность выполнения
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = s21_is_Empty(A);
  if (!error) error = 2 * (A->columns != A->rows);
    if (!error) {
        double det;
        error = s21_determinant(A, &det);
        if (!error && det != 0) {
            matrix_t tmp_calc, tmp_trans;
            error = s21_calc_complements(A, &tmp_calc);
            if (!error) {
                error = s21_transpose(&tmp_calc, &tmp_trans);
                if (!error) {
                    error = s21_mult_number(&tmp_trans, 1 / det, result);
                }
                s21_remove_matrix(&tmp_trans);
            }
            s21_remove_matrix(&tmp_calc);
        } else {
            error = CALC_ERROR;
        }
    }
    return error;
}