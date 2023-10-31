#include <stdio.h>

#define NMAX 10
#define root i + sh
#define left 2 * i + 1 + sh
#define right 2 * i + 2 + sh

int input(int *a, int n);
void output(int *a, int n);
void copyArray(int *a, int *b, int n);
void pyramidalSort(int *a, int n);
int partition(int *a, int low, int high);
void quickSort(int *a, int low, int high);
void swap(int *a, int *b);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n = NMAX, data[NMAX], first[NMAX], second[NMAX];
    int success = input(data, n);
    if (success > -1) {
        copyArray(data, first, n);
        copyArray(data, second, n);
        pyramidalSort(first, n);
        quickSort(second, 0, n - 1);
        output(first, n);
        printf("\n");
        output(second, n);
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

void copyArray(int *a, int *b, int n) {
    for (int *p = a, *q = b; p - a < n && q - b < n; p++, q++) {
        *q = *p;
    }
}

void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        printf("%d ", *p);
    }
}

void pyramidalSort(int *a, int n) {
    int i, sh = 0, b;
    while (sh + 2 != n) {
        b = 0;
        for (i = 0; i < n; i++) {
            if (right < n && (a[root] > a[left] || a[root] > a[right])) {
                if (a[left] < a[right]) {
                    int temp = a[root];
                    a[root] = a[left];
                    a[left] = temp;
                    b = 1;
                } else if (a[right] < a[left]) {
                    int temp = a[root];
                    a[root] = a[left];
                    a[left] = temp;
                    b = 1;
                }
            } else if (left < n) {
                if (a[root] > a[left]) {
                    swap(&a[root], &a[left]);
                    b = 1;
                }
            }
        }
        if (!b) sh++;
    }
}

int partition(int *a, int low, int high) {
    int pivot = a[high];
    int i = low - 1;
    for (int j = low; j <= high; j++) {
        if (a[j] < pivot) {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[high]);
    return (i + 1);
}

void quickSort(int *a, int low, int high) {
    if (low < high) {
        int part = partition(a, low, high);
        quickSort(a, low, part - 1);
        quickSort(a, part + 1, high);
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}