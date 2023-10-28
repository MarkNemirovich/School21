#include <math.h>
#include <stdio.h>

double agnesi(double x);
double bernoulli(double x);
double hyperbole(double x);

int main() {
    double a = -M_PI;
    double x, step = M_PI / 20.5;
    int i = 0;
    double agn, ber, hyp;
    for (; i < 42; i++) {
        x = a + i * step;
        agn = agnesi(x);
        ber = bernoulli(x);
        hyp = hyperbole(x);
        printf("%lf | ", x);
        if (agn != INFINITY)
            printf("%lf | ", agn);
        else
            printf("- | ");
        if (ber != INFINITY)
            printf("%lf | ", ber);
        else
            printf("- | ");
        if (hyp != INFINITY)
            printf("%lf | ", hyp);
        else
            printf("- | ");
        printf("\n");
    }
    return 0;
}

double agnesi(double x) { return 1 / (1 + x * x); }

double bernoulli(double x) {
    if (1 + 4 * x * x < 0 || sqrt(1 + 4 * x * x) - x * x - 1 < 0) return INFINITY;
    return sqrt(sqrt(1 + 4 * x * x) - x * x - 1);
}
double hyperbole(double x) {
    if (x == 0)
        return INFINITY;
    else
        return 1 / x / x;
}