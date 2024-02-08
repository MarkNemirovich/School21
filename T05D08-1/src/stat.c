#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    int success = input(data, &n);
    if (success == 1) {
        output(data, n);
        output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));
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
    printf("\n");
}

int max(int *a, int n) {
    int max = *a;
    for (int *p = a; p - a < n; p++) {
        if (*p > max) max = *p;
    }
    return max;
}

int min(int *a, int n) {
    int min = *a;
    for (int *p = a; p - a < n; p++) {
        if (*p < min) min = *p;
    }
    return min;
}

double mean(int *a, int n) {
    double sum = 0;
    for (int *p = a; p - a < n; p++) {
        sum += *p;
    }
    return sum / n;
}

double variance(int *a, int n) {
    double sum = 0;
    double avg = mean(a, n);
    for (int *p = a; p - a < n; p++) {
        sum += (*p - avg) * (*p - avg);
    }
    return sum / n;
}

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6f %.6f", max_v, min_v, mean_v, variance_v);
}