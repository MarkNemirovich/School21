#include <stdio.h>
#include <stdlib.h>
#define FALL -1
#define MODES 3

int selectMode(int* n);
int inputSize(int* n, int* m);
int segmentalMode(int n, int m, int** arr);
int fillDynamicMatrix(int n, int m, int** matrix);

int input(int** matrix, int* n, int* m);
void output(int** matrix, int n, int m);
int sum(int** matrix_first, int n_first, int m_first, int** matrix_second, int n_second, int m_second,
        int** matrix_result, int* n_result, int* m_result);
int transpose(int** matrix, int n, int m);
int mul(int** matrix_first, int n_first, int m_first, int** matrix_second, int n_second, int m_second,
        int** matrix_result, int* n_result, int* m_result);

int main() {
    int mode = 0, n1 = 0, m1 = 0, n2 = 0, m2 = 0, n3 = 0, m3 = 0;
    printf("Choose the type of array:\n1 - sum\n2 - multiply\n3 - transponse\n");
    int success;
    int **matrix1, **matrix2, **matrix3;
    if (selectMode(&mode) < 0) {
        success = FALL;
        mode = 0;
    }
    if (success > FALL && inputSize(&n1, &m1) < 0) {
        success = FALL;
        mode = 0;
    }
    if (success > FALL) {
        matrix1 = (int**)malloc(n1 * m1 * sizeof(int) + n1 * sizeof(int*));
        success = segmentalMode(n1, m1, matrix1);
    }
    if (success > FALL && (mode == 1 || mode == 2) && inputSize(&n2, &m2) < 0) {
        success = FALL;
        mode = 0;
    }
    if (success > FALL && (mode == 1 || mode == 2)) {
        matrix2 = (int**)malloc(n2 * m2 * sizeof(int) + n2 * sizeof(int*));
        success = segmentalMode(n2, m2, matrix2);
    }
    if (success > FALL && mode == 1) {
        matrix3 = (int**)malloc(n1 * m1 * sizeof(int) + n1 * sizeof(int*));
        sum(matrix1, n1, m1, matrix2, n2, m2, matrix3, &n3, &m3);
        output(matrix3, n3, m3);
    } else if (success > FALL && mode == 2) {
        matrix3 = (int**)malloc(n1 * m1 * sizeof(int) + n1 * sizeof(int*));
        mul(matrix1, n1, m1, matrix2, n2, m2, matrix3, &n3, &m3);
        output(matrix1, n1, m1);
    } else if (success > FALL && mode == 3) {
        transpose(matrix1, n1, m1);
        output(matrix1, n1, m1);
    } else
        printf("n/a");
    if (mode > 0) free(matrix1);
    if (mode == 1 || mode == 2) {
        free(matrix2);
        free(matrix3);
    }
    return 0;
}
int selectMode(int* n) {
    int out = 0;
    if ((scanf("%d", n)) != 1 || *n > MODES || *n <= 0) {
        out = -1;
    }
    return out;
}

int inputSize(int* n, int* m) {
    int out = 0;
    if (scanf("%d %d", n, m) != 2 || *n <= 0 || *m <= 0) {
        out = -1;
    }
    return out;
}

int segmentalMode(int n, int m, int** arr) {
    int out = 0;
    int* ptr = (int*)(arr + n);
    for (int i = 0; i < n; i++) arr[i] = ptr + m * i;
    out = fillDynamicMatrix(n, m, arr);
    return out;
}

int fillDynamicMatrix(int n, int m, int** matrix) {
    int out = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (scanf("%d", &matrix[i][j]) != 1) {
                out = -1;
            }
    return out;
}

void output(int** matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", matrix[i][j]);
            if (j < m - 1) printf(" ");
        }
        if (i < n - 1) printf("\n");
    }
}

int sum(int** matrix_first, int n_first, int m_first, int** matrix_second, int n_second, int m_second,
        int** matrix_result, int* n_result, int* m_result) {
    int out = 0;
    if (n_first != n_second || m_first != m_second) {
        out = FALL;
    }
    *n_result = n_first;
    *m_result = m_first;
    for (int i = 0; i < *n_result; i++)
        for (int j = 0; j < *m_result; j++) {
            matrix_result[i][j] = matrix_first[i][j] + matrix_second[i][j];
        }
    return out;
}


int mul(int** matrix_first, int n_first, int m_first, int** matrix_second, int n_second, int m_second,
        int** matrix_result, int* n_result, int* m_result) {
    int out = 0;
    if (n_first != n_second || m_first != m_second) {
        out = FALL;
    }
    *n_result = n_first;
    *m_result = m_first;
    for (int i = 0; i < *n_result; i++)
        for (int j = 0; j < *m_result; j++) {
            matrix_result[i][j] = matrix_first[i][j] * matrix_second[i][j];
        }
    return out;
}

int transpose(int** matrix, int n, int m) {
    int** temp = (int**)malloc(m * n * sizeof(int) + m * sizeof(int*));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            temp[i][j] = matrix[j][i];
        }
    matrix = temp;
    return 0;
}