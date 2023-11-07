#include "data_io.h"

#include <stdio.h>

void input(double *data, int n) {
    for (int i = 0; data != NULL && i < n; i++) {
        scanf("%lf", &data[i]);
    }
}

void output(double *data, int n) {
    for (int i = 0; i < n - 1; i++) {
        printf("%.2lf ", data[i]);
    }
    printf("%.2lf", data[n - 1]);
}