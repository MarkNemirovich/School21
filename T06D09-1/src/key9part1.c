/*------------------------------------
        Здравствуй, человек!
        Чтобы получить ключ
        поработай с комментариями.
-------------------------------------*/

#include <stdio.h>
#define NMAX 10

int input(int *buffer, int *length);
void output(int *buffer, int length);
int sum_numbers(int *buffer, int length, int *error);
int find_numbers(int *buffer, int length, int number, int *numbers);

/*------------------------------------
        Функция получает массив данных
        через stdin.
        Выдает в stdout особую сумму
        и сформированный массив
        специальных элементов
        (выбранных с помощью найденной суммы):
        это и будет частью ключа
-------------------------------------*/
int main() {
    int n, in, sum, err, amount, data[NMAX], out[NMAX];
    in = input(data, &n);
    if (in > -1) {
        sum = sum_numbers(data, n, &err);
        if (err > -1) {
            amount = find_numbers(data, n, sum, out);
            printf("%d\n", sum);
            output(out, amount);
        } else
            printf("n/a");
    } else
        printf("n/a");
    return 0;
}

int input(int *buffer, int *n) {
    int count, out = -1;
    count = scanf("%d", n);
    if (count != 1 || *n > NMAX) {
        out = -1;
    } else {
        out = 0;
        for (int *p = buffer; out == 0 && p - buffer < *n; p++) {
            count = scanf("%d", p);
            if (count != 1) {
                out = -1;
            }
        }
    }
    return out;
}

void output(int *buffer, int n) {
    for (int *p = buffer; p - buffer < n; p++) {
        printf("%d ", *p);
    }
    printf("\n");
}

/*------------------------------------
        Функция должна находить
        сумму четных элементов
        с 0-й позиции.
-------------------------------------*/
int sum_numbers(int *buffer, int length, int *error) {
    int sum = 0;
    *error = -1;
    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0 && buffer[i] % 2 == 0) {
            sum = sum + buffer[i];
            *error = 0;
        }
    }
    return sum;
}

/*------------------------------------
        Функция должна находить
        все элементы, на которые нацело
        делится переданное число и
        записывает их в выходной массив.
-------------------------------------*/
int find_numbers(int *buffer, int length, int number, int *numbers) {
    int amount = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0 && number % buffer[i] == 0) {
            numbers[amount] = buffer[i];
            amount++;
        }
    }
    return amount;
}