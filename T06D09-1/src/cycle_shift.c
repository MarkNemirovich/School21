#include <stdio.h>
#define NMAX 10

int input(int *buffer, int *length, int *shift);
void output(int *buffer, int length);
void shift(int *buffer, int length, int step);
void swap(int *a, int *b);

int main() {
    int n, s, data[NMAX];
    input(data, &n, &s);
    if (n > -1) {
        shift(data, n, s);
        output(data, n);
    } else
        printf("n/a");
    return 0;
}

int input(int *buffer, int *n, int *shift) {
    int out = 0;
    if ((scanf("%d", n)) != 1 || *n > NMAX || *n < 0) {
        out = -1;
    }
    fflush(stdin);
    for (int *p = buffer; out > -1 && p - buffer < *n; p++) {
        if (scanf("%d", p) != 1) {
            out = -1;
        }
    }
    fflush(stdin);
    if (out > -1)
        if (scanf("%d", shift) != 1) out = -1;
    return out;
}

void output(int *buffer, int n) {
    for (int *p = buffer; p - buffer < n; p++) {
        printf("%d ", *p);
    }
    printf("\n");
}

void shift(int *buffer, int length, int step) {
    if (step > 0) {
        for (int i = 0; i < step; i++) {
            int temp = buffer[0];
            for (int j = 0; j < length; j++) {
                buffer[j] = buffer[j + 1];
            }
            buffer[length - 1] = temp;
        }
    } else {
        for (int i = 0; i < -step; i++) {
            int temp = buffer[length - 1];
            for (int j = length - 1; j > 0; j--) {
                buffer[j] = buffer[j - 1];
            }
            buffer[0] = temp;
        }
    }
}