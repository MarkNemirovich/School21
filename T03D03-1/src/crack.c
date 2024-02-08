#include <stdio.h>

int main() {
    double x, y;
    if (scanf("%lf %lf", &x, &y) != 2) {
        printf("n/a");
    } else {
        if (x * x + y * y < 25)
            printf("GOTCHA");
        else
            printf("MISS");
    }
    return 0;
}