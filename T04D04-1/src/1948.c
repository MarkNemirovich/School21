#include <stdio.h>

int findMaxDelimeter(int a);
int delete (int a, int b);

int main() {
    int a, del;
    char check;
    if (scanf("%d%c", &a, &check) == 2 && check == '\n') {
        if (a > 1) {
            del = findMaxDelimeter(a);
            printf("%d", del);
        } else if (a < -1) {
            del = findMaxDelimeter(-a);
            printf("%d", del);
        } else {
            printf("n/a");
        }
    } else
        printf("n/a");
    return 0;
}

int findMaxDelimeter(int a) {
    int i, rest, simple;
    for (i = a - 1; i >= 2; i--) {
        rest = delete (a, i);
        if (rest == 0) {
            simple = findMaxDelimeter(i);
            if (simple == i) break;
        }
    }
    if (i == 1) i = a;
    return i;
}

int delete (int a, int b) {
    while (a > 0) a = a - b;
    return a;
}