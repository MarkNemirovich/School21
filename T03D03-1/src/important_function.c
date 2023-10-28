#include <math.h>
#include <stdio.h>

double myFunc(double x);

int main() {
    double x;
    if (scanf("%lf", &x) != 1) {
        printf("n/a");
    } else {
        double y = myFunc(x);
        printf("%.1lf", y);
    }
    return 0;
}

double myFunc(double x) {
    return 7e-3 * pow(x, 4.0) + ((22.8 * pow(x, 1.0 / 3.0) - 1000.0) * x + 3.0) / (x * x / 2.0) -
           x * pow((10.0 + x), (2.0 / x)) - 1.01;
}