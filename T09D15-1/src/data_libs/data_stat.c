#include "data_stat.h"

double max(double *data, int n) {
    double max = data[0];
    for (int i = 0; i < n; i++) {
        if (data[i] > max) max = data[i];
    }
    return max;
}
double min(double *data, int n) {
    double min = data[0];
    for (int i = 0; i < n; i++) {
        if (data[i] < min) min = data[i];
    }
    return min;
}
double mean(double *data, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}
double variance(double *data, int n) {
    double sum = 0;
    double avg = mean(data, n);
    for (int i = 0; i < n; i++) {
        sum += (data[i] - avg) * (data[i] - avg);
    }
    return sum / n;
}
