#include <stdio.h>
#include <stdlib.h>
#define MODES 4
#define FALL -1
#define STATIC_SIZE 100

int selectMode(int* n);
int inputSize(int* n, int* m);
int segmentalMode(int n, int m, int** arr);
int multiArraysMode(int n, int m, int** arr);
int singleArrayMode(int n, int m, int** arr, int* values);
int fillDynamicMatrix(int n, int m, int** matrix);
void output(int n, int m, int** matrix);
int staticMode(int n, int m, int arr[n][m]);
void staticOutput(int n, int m, int arr[n][m]);
void maximumsArray(int n, int m, int** matrix);
void minimumsArray(int n, int m, int** matrix);
void printArray(int n, int* array);

int main() {
    int mode, n, m;
    printf(
        "Choose the type of array:\n1 - static\n2 - segmental\n3 - "
        "multiline\n4 - key-value\n");
    int success = 0;
    int arr[STATIC_SIZE][STATIC_SIZE];
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
        success = staticMode(n, m, arr);
    }
    if (success > FALL && mode == 2) {
        matrix = (int**)malloc(n * m * sizeof(int) + n * sizeof(int*));
        success = segmentalMode(n, m, matrix);
    }
    if (success > FALL && mode == 3) {
        matrix = malloc(n * sizeof(int*));
        success = multiArraysMode(n, m, matrix);
    }
    if (success > FALL && mode == 4) {
        matrix = malloc(n * sizeof(int*));
        values = malloc(n * m * sizeof(int));
        success = singleArrayMode(n, m, matrix, values);
    }
    if (success > FALL && mode == 1) {
        staticOutput(n, m, arr);
    } else if (success > FALL && mode > 1) {
        output(n, m, matrix);
        printf("\n");
        maximumsArray(n, m, matrix);
        printf("\n");
        minimumsArray(n, m, matrix);
    } else
        printf("n/a");
    if (mode == 2) {
        free(matrix);
    } else if (mode == 3) {
        for (int i = 0; i < n; i++) free(matrix[i]);
        free(matrix);
    } else if (mode == 4) {
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

int staticMode(int n, int m, int arr[n][m]) {
    int out = 0;
    if (n > STATIC_SIZE || m > STATIC_SIZE) out = -1;
    for (int i = 0; out > -1 && i < n; i++) {
        for (int j = 0; out > -1 && j < m; j++) {
            if (scanf("%d", &arr[i][j]) != 1) {
                out = -1;
            }
        }
    }
    return out;
}

void staticOutput(int n, int m, int arr[n][m]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", arr[i][j]);
            if (j < m - 1) printf(" ");
        }
        if (i < n - 1) printf("\n");
    }
}

void printArray(int n, int* array) {
    for (int i = 0; i < n; i++) {
        printf("%d", array[i]);
        if (i < n - 1) printf(" ");
    }
}

void maximumsArray(int n, int m, int** matrix) {
    int* array = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        int max = matrix[i][0];
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] > max) max = matrix[i][j];
        }
        array[i] = max;
    }
    printArray(n, array);
    free(array);
}

void minimumsArray(int n, int m, int** matrix) {
    int* array = malloc(m * sizeof(int));
    for (int j = 0; j < m; j++) {
        int min = matrix[0][j];
        for (int i = 0; i < n; i++) {
            if (matrix[i][j] < min) min = matrix[i][j];
        }
        array[j] = min;
    }
    printArray(n, array);
    free(array);
}