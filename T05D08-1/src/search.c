/*
    Search module for the desired value from data array.

    Returned value must be:
        - "even"
        - ">= mean"
        - "<= mean + 3 * sqrt(variance)"
        - "!= 0"

        OR

        0
*/

#include <math.h>
#include <stdio.h>
#define NMAX 30

int input(int *a, int *n);
double mean(int *a, int n);
double variance(int *a, int n);
int search(int *a, int n, double m, double s);

int main() {
    int n, data[NMAX];
    int success = input(data, &n);
    if (success == 1) {
        int answer = search(data, n, mean(data, n), sqrt(variance(data, n)));
        printf("%d", answer);
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

int search(int *a, int n, double m, double s) {
    for (int *p = a; p - a < n; p++) {
        if (*p != 0 && *p % 2 == 0 && *p >= m && *p <= m + 3 * s) return *p;
    }
    return 0;
}