#include <stdio.h>
#define NMAX 10

int input(int *a, int n);
void output(int *a, int n);
void gnomeSort(int *a, int n);
void swap(int *a, int *b);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n = NMAX, data[NMAX];
    int success = input(data, n);
    if (success > -1) {
        gnomeSort(data, n);
        output(data, n);
    } else
        printf("n/a");
    return 0;
}

int input(int *a, int n) {
    int out = 0;
    for (int *p = a; out > -1 && p - a < n; p++) {
        if (scanf("%d", p) != 1) out = -1;
    }
    return out;
}

void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        printf("%d ", *p);
    }
}

void gnomeSort(int *a, int n) {
    int *p = a;
    while (p < a + n) {
        if (p == a || *(p - 1) <= *p)
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