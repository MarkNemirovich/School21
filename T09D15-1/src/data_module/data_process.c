#include "data_process.h"

#include <math.h>

#include "../data_libs/data_stat.h"

int normalization(double *data, int n) {
    int result = 1;
    double max_value = max(data, n);
    double min_value = min(data, n);
    double size = max_value - min_value;

    if (fabs(size) > EPS) {
        for (int i = 0; i < n; i++) {
            data[i] = data[i] / size - min_value / size;
        }
    } else {
        result = 0;
    }

    return result;
}

void sort(double *a, int n) {
    double *p = a;
    while (p < a + n) {
        if (p == a || *(p - 1) <= *p)
            p++;
        else {
            swap(p - 1, p);
            p--;
        }
    }
}

void swap(double *a, double *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
