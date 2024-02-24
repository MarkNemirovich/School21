#ifndef __S21_MATRIX_H__
#define __S21_MATRIX_H__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

enum { OK = 0, INCORRECT_MATRIX = 1, CALC_ERROR = 2, MALLOC_FAILED = 3 };

#define SUCCESS 1
#define FAILURE 0

//                                                              INITIALIZE
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

//                                                              COMPARISON
int s21_eq_matrix(matrix_t *A, matrix_t *B);

//                                                              ARITHMETICS
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

//                                                                LINEAR ALGEBRA
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

//                                                                SUPPORT
int s21_is_Empty(matrix_t *A);
void s21_free_matrix(matrix_t *A, int rows);
double s21_get_determinant(matrix_t *A);
void s21_get_matrix(int row, int col, matrix_t *A, matrix_t *result);

#endif