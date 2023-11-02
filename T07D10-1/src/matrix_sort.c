#include <stdio.h>
#include <stdlib.h>
#define FALL -1
#define MODES 3

int selectMode(int* n);
int inputSize(int* n, int* m);
int segmentalMode(int n, int m, int** arr);
int multiArraysMode(int n, int m, int** arr);
int singleArrayMode(int n, int m, int** arr, int* values);
int fillDynamicMatrix(int n, int m, int** matrix);
void output(int n, int m, int** matrix);
void sort(int n, int m, int** matrix);
void swap(int row, int otherRow, int m, int** matrix);
int rawSum(int row, int m, int** matrix);

int main() {
    int mode, n, m;
    printf("Choose the type of array:\n1 - segmental\n2 - multiline\n3 - key-value\n");
    int success = 0;
    int* values;
    int** matrix;
    if (selectMode(&mode) < 0) {
        success = FALL;
        mode = 0;
    }
    if (success > FALL && inputSize(&n, &m) < 0) {
        success = FALL;
        mode = 0;
    }
    if (success > FALL && mode == 1) {
        matrix = (int**)malloc(n * m * sizeof(int) + n * sizeof(int*));
        success = segmentalMode(n, m, matrix);
    }
    if (success > FALL && mode == 2) {
        matrix = malloc(n * sizeof(int*));
        success = multiArraysMode(n, m, matrix);
    }
    if (success > FALL && mode == 3) {
        matrix = malloc(n * sizeof(int*));
        values = malloc(n * m * sizeof(int));
        success = singleArrayMode(n, m, matrix, values);
    }
    if (success > FALL) {
        sort(n, m, matrix);
        output(n, m, matrix);
    } else
        printf("n/a");
    if (mode == 1) {
        free(matrix);
    } else if (mode == 2) {
        for (int i = 0; i < n; i++) free(matrix[i]);
        free(matrix);
    } else if (mode == 3) {
        free(values);
        free(matrix);
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

int multiArraysMode(int n, int m, int** arr) {
    int out = 0;
    for (int i = 0; i < n; i++) arr[i] = malloc(m * sizeof(int));
    out = fillDynamicMatrix(n, m, arr);
    return out;
}

int singleArrayMode(int n, int m, int** arr, int* values) {
    int out = 0;
    for (int i = 0; i < n; i++) arr[i] = values + m * i;
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

void output(int n, int m, int** matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", matrix[i][j]);
            if (j < m - 1) printf(" ");
        }
        if (i < n - 1) printf("\n");
    }
}

void sort(int n, int m, int** matrix) {
    for (int i = 0; i < n - 1; i++) {
        int maxI = i, maxSum = 0;
        for (int j = i; j < n; j++) {
            int sum = rawSum(j, m, matrix);
            if (sum > maxSum) {
                maxSum = sum;
                maxI = j;
            }
            swap(i, maxI, m, matrix);
        }
    }
}

int rawSum(int row, int m, int** matrix) {
    int sum = 0;
    for (int j = 0; j < m; j++) {
        sum += matrix[row][j];
    }
    return sum;
}
void swap(int row, int otherRow, int m, int** matrix) {
    for (int j = 0; j < m; j++) {
        int temp = matrix[row][j];
        matrix[row][j] = matrix[otherRow][j];
        matrix[otherRow][j] = temp;
    }
}