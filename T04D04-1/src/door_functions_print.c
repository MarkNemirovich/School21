#include <math.h>
#include <stdio.h>

double agnesi(double x);
double bernoulli(double x);
double hyperbole(double x);
void drowAgnesi();
void drowBernoulli();
void drowHyperbole();

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
        printf("\n");
    drowAgnesi();
        printf("\n");
    drowBernoulli();
        printf("\n");
    drowHyperbole();
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

void drowAgnesi() {
    double a = -M_PI;
    double x, step = M_PI / 20.5;
    double max = -INFINITY, min = INFINITY, h, hyp;
    for (int i = 0; i < 42; i++) {
        x = a + i * step;
        hyp = agnesi(x);
        if (hyp > max && hyp != INFINITY) max = hyp;
        if (hyp < min && hyp != -INFINITY) min = hyp;
    }
    h = (max - min) / 21;
    for (int i = 0; i <= 22; i++) {
        for (int j = 0; j <= 42; j++) {
            if (j == 0) {
                printf("| ");
                continue;
            }
            if (i == 22) {
                printf("_ ");
                continue;
            }
            x = a + j * step;
            hyp = agnesi(x);
            if ((hyp <= max - i * h + h / 2) && (hyp > max - i * h - h / 2))
                printf("* ");
            else
                printf("  ");
        }
        printf("\n");
    }
}

void drowBernoulli() {
    double a = -M_PI;
    double x, step = M_PI / 20.5;
    double max = -INFINITY, min = INFINITY, h, hyp;
    for (int i = 0; i < 42; i++) {
        x = a + i * step;
        hyp = bernoulli(x);
        if (hyp > max && hyp != INFINITY) max = hyp;
        if (hyp < min && hyp != -INFINITY) min = hyp;
    }
    h = (max - min) / 21;
    for (int i = 0; i <= 22; i++) {
        for (int j = 0; j <= 42; j++) {
            if (j == 0) {
                printf("| ");
                continue;
            }
            if (i == 22) {
                printf("_ ");
                continue;
            }
            x = a + j * step;
            hyp = bernoulli(x);
            if ((hyp <= max - i * h + h / 2) && (hyp > max - i * h - h / 2))
                printf("* ");
            else
                printf("  ");
        }
        printf("\n");
    }
}

void drowHyperbole() {
    double a = -M_PI;
    double x, step = M_PI / 20.5;
    double max = -INFINITY, min = INFINITY, h, hyp;
    for (int i = 0; i < 42; i++) {
        x = a + i * step;
        hyp = hyperbole(x);
        if (hyp > max && hyp != INFINITY) max = hyp;
        if (hyp < min && hyp != -INFINITY) min = hyp;
    }
    h = (max - min) / 21;
    for (int i = 0; i <= 22; i++) {
        for (int j = 0; j <= 42; j++) {
            if (j == 0) {
                printf("| ");
                continue;
            }
            if (i == 22) {
                printf("_ ");
                continue;
            }
            x = a + j * step;
            hyp = hyperbole(x);
            if ((hyp <= max - i * h + h / 2) && (hyp > max - i * h - h / 2))
                printf("* ");
            else
                printf("  ");
        }
        printf("\n");
    }
}