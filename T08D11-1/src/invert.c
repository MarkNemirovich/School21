#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define FAIL -1
#define EPS 1E-9

void invert(double **matrix, int n, int m);
void input(double **matrix, int *n, int *m);
void output(double **matrix, int n, int m);
int inputSize(int *n, int *m);
double det(double **matrix, int n, int m);
void swap(double **matrix, int row, int otherRow, int m);
void gauss(double **matrix, int n, int m);
void clone(double **matrix, double **reversed, int n, int m);

int main() {
    double **matrix = NULL;
    double **reversed = NULL;
    int n, m;
    double determinal = 0;

    int out = inputSize(&n, &m);
    if (out > FAIL) {
        matrix = (double **)malloc(n * m * sizeof(double) + n * sizeof(double *));
        input(matrix, &n, &m);
    }
    if (out > FAIL && n > FAIL && m > FAIL) {
        reversed = (double **)malloc(n * m * sizeof(double) + n * sizeof(double *));
        clone(matrix, reversed, n, m);
        determinal = det(matrix, n, m);
    }
    if (out > FAIL && fabs(determinal) > EPS) {
        // gauss(reversed, n, m);
        output(reversed, n, m);
    } else
        printf("n/a");
    if (matrix != NULL) free(matrix);
    if (reversed != NULL) free(reversed);
    return 0;
}

int inputSize(int *n, int *m) {
    int out = 0;
    if (scanf("%d %d", n, m) != 2 || *n <= 0 || *m <= 0 || *n != *m) {
        out = FAIL;
    }
    return out;
}

void input(double **matrix, int *n, int *m) {
    int out = 0;
    double *ptr = (double *)(matrix + *n);
    for (int i = 0; i < *n; i++) matrix[i] = ptr + *m * i;

    for (int i = 0; out > FAIL && i < *n; i++)
        for (int j = 0; out > FAIL && j < *m; j++)
            if (scanf("%lf", &matrix[i][j]) != 1) {
                out = FAIL;
            }
    if (out == FAIL) {
        *n = FAIL;
        *m = FAIL;
    }
}

double det(double **matrix, int n, int m) {
    double det = 1;
    int finish = 0;
    for (int i = 0; finish != FAIL && i < n; i++) {
        int k = i;
        for (int j = i + 1; finish != FAIL && j < m; j++) {
            if (fabs(matrix[j][i]) > fabs(matrix[k][i])) k = j;
        }
        if (fabs(matrix[k][i]) < EPS) {
            det = 0;
            finish = FAIL;
        }
        if (finish != FAIL) {
            swap(matrix, i, k, m);
            if (i != k) det *= -1;
            det *= matrix[i][i];
        }
        for (int j = i + 1; finish != FAIL && j < m; j++) {
            matrix[i][j] /= matrix[i][i];
        }

        for (int j = 0; finish != FAIL && j < m; j++) {
            if ((i != j) && fabs(matrix[j][i]) > EPS) {
                for (k = i + 1; finish != FAIL && k < n; k++) {
                    matrix[j][k] -= matrix[i][k] * matrix[j][i];
                }
            }
        }
    }
    return det;
}

void swap(double **matrix, int row, int otherRow, int m) {
    for (int j = 0; j < m; j++) {
        double temp = matrix[row][j];
        matrix[row][j] = matrix[otherRow][j];
        matrix[otherRow][j] = temp;
    }
}

void clone(double **matrix, double **reversed, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            reversed[i][j] = matrix[i][j];
        }
    }
}
void output(double **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%.6lf", matrix[i][j]);
            if (j < m - 1) printf(" ");
        }
        if (i < n - 1) printf("\n");
    }
}