#include <stdio.h>
#include <stdlib.h>
#define FAIL -1

/*
    1 6 7
    2 5 8
    3 4 9
*/
void sort_vertical(int **matrix, int n, int m, int **result_matrix);

/*
    1 2 3
    6 5 4
    7 8 9
*/
void sort_horizontal(int **matrix, int n, int m, int **result_matrix);

int inputSize(int *n, int *m);
void input(int **matrix, int *n, int *m);
void output(int **matrix, int n, int m);

void gnomeSort(int *array, int n);
void swap(int *a, int *b);

int main() {
    int **matrix = NULL, **result = NULL;
    int n, m;

    int out = inputSize(&n, &m);
    if (out > FAIL) {
        matrix = (int **)malloc(n * m * sizeof(int) + n * sizeof(int *));
        input(matrix, &n, &m);
    }
    if (out > FAIL && n > FAIL && m > FAIL) {
        result = (int **)malloc(n * m * sizeof(int) + n * sizeof(int *));
        int *ptr = (int *)(result + n);
        for (int i = 0; i < n; i++) result[i] = ptr + m * i;

        sort_vertical(matrix, n, m, result);
        output(result, n, m);

        printf("\n");
        printf("\n");
        printf("\n");

        sort_horizontal(matrix, n, m, result);
        output(result, n, m);
    } else
        printf("n/a");
    if (matrix != NULL) free(matrix);
    if (result != NULL) free(result);
}

int inputSize(int *n, int *m) {
    int out = 0;
    if (scanf("%d %d", n, m) != 2 || *n <= 0 || *m <= 0) {
        out = FAIL;
    }
    return out;
}

void input(int **matrix, int *n, int *m) {
    int out = 0;
    int *ptr = (int *)(matrix + *n);
    for (int i = 0; i < *n; i++) matrix[i] = ptr + *m * i;

    for (int i = 0; out > FAIL && i < *n; i++)
        for (int j = 0; out > FAIL && j < *m; j++)
            if (scanf("%d", &matrix[i][j]) != 1) {
                out = FAIL;
            }
    if (out == FAIL) {
        *n = FAIL;
        *m = FAIL;
    }
}

void output(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", matrix[i][j]);
            if (j < m - 1) printf(" ");
        }
        if (i < n - 1) printf("\n");
    }
}

void sort_vertical(int **matrix, int n, int m, int **result_matrix) {
    int *array = (int *)malloc(n * m * sizeof(int));
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            array[k] = matrix[i][j];
            k++;
        }
    }
    gnomeSort(array, k);
    k = 0;
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            if (j % 2 == 0)
                result_matrix[i][j] = array[k];
            else
                result_matrix[n - i - 1][j] = array[k];
            k++;
        }
    }
    free(array);
}

void sort_horizontal(int **matrix, int n, int m, int **result_matrix) {
    int *array = (int *)malloc(n * m * sizeof(int));
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            array[k] = matrix[i][j];
            k++;
        }
    }
    gnomeSort(array, k);
    k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i % 2 == 0)
                result_matrix[i][j] = array[k];
            else
                result_matrix[i][m - j - 1] = array[k];
            k++;
        }
    }
    free(array);
}

void gnomeSort(int *array, int n) {
    int *p = array;
    while (p < array + n) {
        if (p == array || *(p - 1) <= *p)
            p++;
        else {
            swap(p - 1, p);
            p--;
        }
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}