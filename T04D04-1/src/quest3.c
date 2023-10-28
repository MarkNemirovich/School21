#include <stdio.h>

int fibonacci(int a);

int main() {
    int n, fib;
    char check;
    if (scanf("%d%c", &n, &check) == 2 && check == '\n') {
        fib = fibonacci((int)n);
        printf("%d", fib);
    } else {
        printf("n/a");
    }
    return 0;
}

int fibonacci(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}