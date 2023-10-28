#include <stdio.h>

int sum(int x, int y);
int razn(int x, int y);
int proi(int x, int y);
int del(int x, int y);

int main() {
    int a, b;
    char u;
    if (scanf("%d %d%c", &a, &b, &u) != 3 || u != '\n') {
        printf("n/a");
    } else {
        printf("%d %d %d", sum(a, b), razn(a, b), proi(a, b));
    }
    if (b == 0) {
        printf("n/a");
    } else {
        printf(" %d", del(a, b));
    }
    return 0;
}

int sum(int x, int y) { return (x + y); }
int razn(int x, int y) { return (x - y); }
int proi(int x, int y) { return (x * y); }
int del(int x, int y) { return (x / y); }
