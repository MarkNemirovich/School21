#include <math.h>
#include <stdio.h>

#define LEN 100

int input(int *buffer, int *length);
void output(int *buffer, int length);
void reverse(int *buffer, int n);
void cutZeros(int *buffer, int *n);
void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);

/*
    Беззнаковая целочисленная длинная арифметика
    с использованием массивов.
    Ввод:
     * 2 длинных числа в виде массивов до 100 элементов
     * В один элемент массива нельзя вводить число > 9
    Вывод:
     * Результат сложения и разности чисел-массивов
    Пример:
     * 1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 6 1
       2 9

       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 9 0
       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 3 2
*/
int main() {
    int n, m, k, in1, in2, first[LEN], second[LEN], summa[LEN], residue[LEN];
    in1 = input(first, &n);
    in2 = input(second, &m);
    if (in1 != -1 && in2 != -1) {
        if (n > -1 && m > -1) {
            sum(first, n, second, m, summa, &k);
            reverse(summa, k);
            cutZeros(summa, &k);
            output(summa, k);
            sub(first, n, second, m, residue, &k);
            if (k > -1) {
                reverse(residue, k);
                cutZeros(residue, &k);
                output(residue, k);
            } else
                printf("n/a");
        } else
            printf("n/a");
    } else
        printf("n/a");
    return 0;
}
int input(int *buffer, int *n) {
    int out = 0;
    int *p = buffer;
    int i = 0;
    char symb;
    *n = 0;
    while ((symb = getchar()) != '\n' && (out != -1)) {
        if (i % 2 == 1) {
            if (symb != ' ' && symb != '\0') {
                out = -1;
            }
        } else {
            if (symb >= '0' && symb <= '9') {
                *p = (int)(symb - '0');
                *n += 1;
                p++;
                if (*n > LEN) {
                    out = -1;
                }
            } else {
                out = -1;
            }
        }
        i++;
    }
    return out;
}

void output(int *buffer, int n) {
    for (int *p = buffer; p - buffer < n; p++) {
        printf("%d ", *p);
    }
    printf("\n");
}

void reverse(int *buffer, int n) {
    int temp;
    for (int *start = buffer, *end = buffer + n - 1; start < end; start++, end--) {
        temp = *start;
        *start = *end;
        *end = temp;
    }
}

void cutZeros(int *buffer, int *n) {
    int first = *buffer;
    while (first == 0 && *n > 1) {
        for (int i = 0; i < *n; i++) {
            buffer[i] = buffer[i + 1];
        }
        *n -= 1;
        first = *buffer;
    }
}

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    int sum = 0, count = 0;
    int *p = buff1 + len1 - 1;
    int *q = buff2 + len2 - 1;
    for (; p >= buff1 && q >= buff2; p--, q--, count++) {
        sum += *p + *q;
        result[count] = sum % 10;
        sum = sum / 10;
    }
    for (; p >= buff1; p--, count++) {
        sum += *p;
        result[count] = sum % 10;
        sum = sum / 10;
    }
    for (; q >= buff2; q--, count++) {
        sum += *q;
        result[count] = sum % 10;
        sum = sum / 10;
    }
    if (sum > 0) {
        result[count] = sum;
        count++;
    }
    *result_length = count;
}

void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    int dif = 0, count = 0;
    int *p = buff1 + len1 - 1;
    int *q = buff2 + len2 - 1;
    if (len1 < len2) {
        count = -1;
    } else {
        for (; p >= buff1 && q >= buff2; p--, q--, count++) {
            dif += (*p - *q);
            if (dif < 0) {
                result[count] = 10 + dif;
                dif = -1;
            } else {
                result[count] = dif;
                dif = 0;
            }
        }
        for (; p >= buff1; p--, count++) {
            dif += *p;
            result[count] = dif;
            dif = 0;
        }
    }
    if (dif == -1) {
        count = -1;
    }
    *result_length = count;
}