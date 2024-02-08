#include <stdio.h>
#include <stdlib.h>
#ifdef DYNAMIC
#include <dlfcn.h>
#endif

#include "../data_libs/data_io.h"
#include "../data_module/data_process.h"
#include "../yet_another_decision_module/decision.h"

void copy(double *a, double *b, int n);

int main() {
    double *data, *raw_data;
    int n, error = 0;

    if (scanf("%d", &n) == 1 && n > 0) {
        raw_data = (double *)malloc(n * sizeof(double));
        if (raw_data != NULL) {
            printf("LOAD DATA...\n");
            input(raw_data, n);

            printf("RAW DATA:\n\t");
            output(raw_data, n);
            data = (double *)malloc(n * sizeof(double));
            copy(raw_data, data, n);

            int (*normalizer)(double *, int) = NULL;
            void (*sorter)(double *, int) = NULL;
#ifdef DYNAMIC
            void *ext_library = dlopen("data_process.so", RTLD_LAZY);
            if (!ext_library)
                error = 1;
            else {
                normalizer = dlsym(ext_library, "normalization");
                error += !dlerror();
                sorter = dlsym(ext_library, "sort");
                error += !dlerror();
            }
#else
            normalizer = normalization;
            sorter = sort;
#endif

            if (normalizer(data, n)) {
                printf("\nNORMALIZED DATA:\n\t");
                output(data, n);

                printf("\nSORTED NORMALIZED DATA:\n\t");
                sorter(data, n);
                output(data, n);

                printf("\nFINAL DECISION:\n\t");
                printf(make_decision(raw_data, n) == 1 ? "\nYes" : "\nNo");
            } else
                printf("\nERROR");

            free(data);
#ifdef DYNAMIC
            dlclose(ext_library);
#endif
        }
        free(raw_data);
    }

    return error;
}

void copy(double *a, double *b, int n) {
    for (int i = 0; i < n; i++) {
        b[i] = a[i];
    }
}