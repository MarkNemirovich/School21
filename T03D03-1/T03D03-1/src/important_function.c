#include <math.h>
#include <stdio.h>

float y(float x);

int main() {
    float x;
    if (scanf("%f", &x) == 1) {
        printf("%.1f", y(x));
    } else {
        printf("n/a");
    }
    return 0;
}

float y(float x) {
    return (7 * pow(10, -3) * pow(x, 4) + ((22.8 * pow(x, 1 / 3) - 1 * pow(10, 3)) * x + 3) / (x * x / 2) -
            x * pow(10 + x, 2 / x) - 1.01);
}