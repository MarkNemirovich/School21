#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "data_process.h"

int main() {
    double *data;
    int n;

    if (scanf("%d", &n) == 1 && n > 0) {
        data = (double *)malloc(n * sizeof(double));
        if (data != NULL) {
            input(data, n);
            if (normalization(data, n))
                output(data, n);
            else
                printf("ERROR");
        } else
            printf("n/a");
        free(data);
    } else
        printf("n/a");
    return 0;
}
