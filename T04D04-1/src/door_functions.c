#include <math.h>
#include <stdio.h>

double agnesi(double x);
double bernoulli(double x);
double hyperbole(double x);

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
