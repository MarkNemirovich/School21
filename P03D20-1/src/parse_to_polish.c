#include "parse_to_polish.h"

int parseToPolish(struct st *operations, char *input_str, char *output_str) {
    int point = 0, bounce = 0, success = 1;
    stringToLow(input_str);
    for (int i = 0; success && input_str[i] != '\0'; i++) {
        if (input_str[i] == 'x') {
            output_str[point++] = ' ';
            output_str[point++] = input_str[i];
            output_str[point++] = ' ';
        } else if ((input_str[i] >= '0' && input_str[i] <= '9') || input_str[i] == '.') {
            output_str[point++] = input_str[i];
        } else if (input_str[i] == ')') {
            while (operations && (operations->c) != '(') {
                output_str[point++] = ' ';
                pushOutput(&operations, output_str, &point);
                output_str[point++] = ' ';
            }
            bounce--;
            delete (&operations);
        } else if (strchr("sctcsl", input_str[i]) != NULL) {
            i = checkTriginometry(input_str, i, &operations, output_str, &point);
        } else if (input_str[i] == '(') {
            operations = push(operations, '(');
            bounce++;
        } else if (input_str[i] == '+' || input_str[i] == '-' || input_str[i] == '/' || input_str[i] == '*' ||
                   input_str[i] == '^') {
            output_str[point++] = ' ';
            if (operations == NULL) {
                if (input_str[i] == '-' && (i == 0 || (i > 0 && input_str[i - 1] == '(')))
                    operations = push(operations, '~');
                else
                    operations = push(operations, input_str[i]);
            } else if (priority(operations->c) < priority(input_str[i])) {
                if (input_str[i] == '-' && (i == 0 || (i > 0 && input_str[i - 1] == '(')))
                    operations = push(operations, '~');
                else
                    operations = push(operations, input_str[i]);
            } else {
                while ((operations != NULL) && (priority(operations->c) >= priority(input_str[i]))) {
                    output_str[point++] = ' ';
                    pushOutput(&operations, output_str, &point);
                    output_str[point++] = ' ';
                }
                if (input_str[i] == '-' && (i == 0 || (i > 0 && input_str[i - 1] == '(')))
                    operations = push(operations, '~');
                else
                    operations = push(operations, input_str[i]);
            }
            output_str[point++] = ' ';
        } else
            success = 0;
    }
    if (operations != NULL) {
        pushOutput(&operations, output_str, &point);
    }
    output_str[point] = '\0';
    return success & (bounce == 0);
}

void stringToLow(char *string) {
    while (*string != '\0') {
        if (*string >= 'A' && *string <= 'Z') *string += 'a' - 'A';
        string++;
    }
}

int checkTriginometry(char *input_str, int i, struct st **operations, char *output_str, int *point) {
    if (input_str[i] == 's' && input_str[i + 1] == 'i' && input_str[i + 2] == 'n') {
        handleTrigonometric(operations, output_str, point, SIN);
        i += 2;
    } else if (input_str[i] == 'c' && input_str[i + 1] == 'o' && input_str[i + 2] == 's') {
        handleTrigonometric(operations, output_str, point, COS);
        i += 2;
    } else if (input_str[i] == 't' && input_str[i + 1] == 'a' && input_str[i + 2] == 'n') {
        handleTrigonometric(operations, output_str, point, TG);
        i += 2;
    } else if (input_str[i] == 'c' && input_str[i + 1] == 't' && input_str[i + 2] == 'g') {
        handleTrigonometric(operations, output_str, point, CTG);
        i += 2;
    } else if (input_str[i] == 's' && input_str[i + 1] == 'q' && input_str[i + 2] == 'r' &&
               input_str[i + 3] == 't') {
        handleTrigonometric(operations, output_str, point, SQRT);
        i += 3;
    } else if (input_str[i] == 'l' && input_str[i + 1] == 'n') {
        handleTrigonometric(operations, output_str, point, LN);
        i += 1;
    }
    return i;
}

void handleTrigonometric(struct st **operations, char *output_str, int *point, char type) {
    if (*operations == NULL) {
        *operations = push(*operations, type);
    } else if (priority((*operations)->c) < priority(type)) {
        *operations = push(*operations, type);
    } else {
        while ((*operations != NULL) && (priority((*operations)->c) >= priority(type))) {
            pushOutput(operations, output_str, point);
        }
        *operations = push(*operations, type);
    }
}

void pushOutput(struct st **operations, char *output_str, int *point) {
    output_str[(*point)++] = delete (operations);
}