#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);

int main() {
    int n, data[NMAX];
    int success = input(data, &n);
    if (success == 1) {
        squaring(data, n);
        output(data, n);
    } else
        printf("n/a");
    return 0;
}

int input(int *a, int *n) {
    int count;
    count = scanf("%d", n);
    if (count != 1) return 0;
    for (int *p = a; p - a < *n; p++) {
        count = scanf("%d", p);
        if (count != 1) return 0;
    }
    return 1;
}

void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        printf("%d ", *p);
    }
}

void squaring(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        *p *= *p;
    }
}