#include "calculate.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "draw.h"
#include "my_stack.h"

int addFuncForGraph(char **graph, int height, int width, char *out, HEAD *head) {
    int success = 1;
    for (int y = 0; success && y < height; y++) {
        for (int x = 0; success && x < width; x++) {
            int y_coord = HEIGHT;
            double value = counter(out, head, (M_PI * x) / 20);
            if (value != INFINITY) {
                y_coord = round(12 + 12 * value);
                if (y_coord >= 0 && y_coord < HEIGHT) graph[y_coord][x] = STAR;
            } else
                success = 0;
        }
    }
    return success;
}

double counter(char *output_str, HEAD *head, double x) {
    int n = strlen(output_str), shift = 0;
    double out = INFINITY;
    for (int i = 0; shift >= 0 && i < n; i++) {
        if (output_str[i] != ' ') {
            shift = firstConditions(output_str, head, i, x);
            i += shift - 1;
        }
    }
    if (shift >= 0) out = pop_calc(head);
    return out;
}

int popTwo(double *num1, double *num2, HEAD *head) {
    int shift = 1;
    *num2 = pop_calc(head);
    *num1 = pop_calc(head);
    if (*num1 == INFINITY || *num2 == INFINITY) shift = -1;
    return shift;
}

int firstConditions(char *output_str, HEAD *head, int i, double x) {
    double num1, num2;
    int shift = 1;
    switch (output_str[i]) {
        case 'x':
            pushingCalc(x, head);
            break;
        case '+':
            shift = popTwo(&num2, &num1, head);
            if (shift > 0) pushingCalc(num1 + num2, head);
            break;
        case '-':
            shift = popTwo(&num2, &num1, head);
            if (shift > 0) pushingCalc(num1 - num2, head);
            break;
        default:
            shift = secondConditions(output_str, head, i);
            break;
    }
    return shift;
}

int secondConditions(char *output_str, HEAD *head, int i) {
    double num1, num2;
    int shift = 1;
    switch (output_str[i]) {
        case '*':
            shift = popTwo(&num2, &num1, head);
            if (shift > 0) pushingCalc((double)num1 * (double)num2, head);
            break;
        case '/':
            shift = popTwo(&num2, &num1, head);
            if (shift > 0) {
                if (num2 != 0)
                    pushingCalc(num1 / num2, head);
                else
                    pushingCalc(1000, head);
            }
            break;
        case '^':
            shift = popTwo(&num2, &num1, head);
            if (shift > 0) pushingCalc(pow(num1, num2), head);
            break;
        default:
            shift = thirdConditions(output_str, head, i);
            break;
    }
    return shift;
}

int thirdConditions(char *output_str, HEAD *head, int i) {
    double num1;
    int shift = 1;
    switch (output_str[i]) {
        case SIN:
            num1 = pop_calc(head);
            if (num1 == INFINITY) shift = -1;
            if (shift > 0) pushingCalc(sin(num1), head);
            break;
        case COS:
            num1 = pop_calc(head);
            if (num1 == INFINITY) shift = -1;
            if (shift > 0) pushingCalc(cos(num1), head);
            break;
        case TG:
            num1 = pop_calc(head);
            if (num1 == INFINITY) shift = -1;
            if (shift > 0) pushingCalc(tan(num1), head);
            break;
        case CTG:
            num1 = pop_calc(head);
            if (num1 == INFINITY) shift = -1;
            if (shift > 0) pushingCalc(1 / tan(num1), head);
            break;
        case SQRT:
            num1 = pop_calc(head);
            if (num1 == INFINITY || num1 < 0)
                shift = -1;
            else
                pushingCalc(sqrt(num1), head);
            break;
        case LN:
            num1 = pop_calc(head);
            if (num1 == INFINITY) shift = -1;
            if (shift > 0) pushingCalc(log(num1), head);
            break;
        case '~':
            num1 = pop_calc(head);
            if (num1 == INFINITY) shift = -1;
            if (shift > 0) pushingCalc(-num1, head);
            break;
        default:
            if (output_str[i] >= '0' && output_str[i] <= '9') {
                int length = numberLength(&output_str[i]);
                char str[3 * MAX_STRING];
                if (str != NULL) {
                    subString(&output_str[i], str, length);
                    double number = convertToDouble(str);
                    pushingCalc(number, head);
                    shift = length;
                }
            }
            break;
    }
    return shift;
}

int numberLength(const char *string) {
    int i = 0;
    while ((*string >= '0' && *string <= '9') || *string == '.') {
        i++;
        string++;
    }
    return i++;
}

void subString(const char *string, char *target, int length) {
    for (int i = 0; i < length; i++) {
        target[i] = string[i];
    }
    target[length] = '\0';
}

int isDigit(char c) {
    int flag = 0;
    if (c >= '0' && c <= '9') {
        flag = 1;
    }
    return flag;
}

double convertToDouble(const char *string) {
    double result = 0;
    double decimal = 10.0;
    int pos = 0;
    int isDecimal = -1;

    while (isDigit(string[pos]) || string[pos] == '.') {
        if (string[pos] == '.') {
            isDecimal = 1;
        } else {
            if (isDecimal != 1) {
                result = result * 10 + (string[pos] - '0');
            } else {
                result += (string[pos] - '0') / decimal;
                decimal *= 10;
            }
        }
        pos++;
    }

    return result;
}