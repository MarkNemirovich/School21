#include <math.h>
#include <stdio.h>

#define LEFT 0
#define RIGHT 42

double agnesi(double x);
double bernoulli(double x);
double hyperbole(double x);
void drowAgnesi();
void drowBernoulli();
void drowHyperbole();

int main() {
    FILE *fp = fopen("door_data.txt", "w");
    if (fp) {
        double a = -M_PI;
        double x, step = M_PI / 20.5;
        int i = 0;
        double agn, ber, hyp;
        for (; i < 42; i++) {
            x = a + i * step;
            agn = agnesi(x);
            ber = bernoulli(x);
            hyp = hyperbole(x);
            fprintf(fp, "%lf | ", x);
            if (agn != INFINITY)
                fprintf(fp, "%lf | ", agn);
            else
                fprintf(fp, "- | ");
            if (ber != INFINITY)
                fprintf(fp, "%lf | ", ber);
            else
                fprintf(fp, "- | ");
            if (hyp != INFINITY)
                fprintf(fp, "%lf | ", hyp);
            else
                fprintf(fp, "- | ");
            fprintf(fp, "\n");
        }
        fclose(fp);
    } else
        printf("n/a");
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
    for (int i = LEFT; i < 42; i++) {
        x = a + i * step;
        hyp = agnesi(x);
        if (hyp > max && hyp != INFINITY) max = hyp;
        if (hyp < min && hyp != -INFINITY) min = hyp;
    }
    h = (max - min) / 21;
    for (int i = 0; i <= 22; i++) {
        for (int j = LEFT; j <= 42; j++) {
            if (j == LEFT) {
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
    for (int i = LEFT; i < 42; i++) {
        x = a + i * step;
        hyp = bernoulli(x);
        if (hyp > max && hyp != INFINITY) max = hyp;
        if (hyp < min && hyp != -INFINITY) min = hyp;
    }
    h = (max - min) / 21;
    for (int i = 0; i <= 22; i++) {
        for (int j = LEFT; j <= 42; j++) {
            if (j == LEFT) {
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
        for (int j = LEFT; j <= 42; j++) {
            if (j == LEFT) {
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
