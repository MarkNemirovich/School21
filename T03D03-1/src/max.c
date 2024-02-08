#include <stdio.h>

int max(int a, int b);

int main() {
    int a, b;
    if (scanf("%d %d", &a, &b) != 2) {
        printf("n/a");
    } else {
        int m = max(a, b);
        printf("%d", m);
    }
    return 0;
}

int max(int a, int b) {
    int m = a;
    if (b > a) m = b;
    return m;
}