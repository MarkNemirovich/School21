#include <stdio.h>

int max(int x, int y);

int main() {
    int a, b;
    if (scanf("%d %d", &a, &b) == 2) {
        printf("%d", max(a, b));
    } else {
        printf("n/a");
    }
    return 0;
}

int max(int x, int y) {
    if (x > y) {
        return x;
    } else {
        return y;
    }
}