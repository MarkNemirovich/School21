#include "my_stack.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "calculate.h"

char delete (struct st **HEAD) {
    char symbol = '\0';
    if (*HEAD != NULL) {
        struct st *upper = *HEAD;
        symbol = upper->c;
        *HEAD = upper->next;
        free(upper);
    }
    return symbol;
}

struct st *push(struct st *HEAD, char symbol) {
    struct st *upper = malloc(sizeof(struct st));
    if (upper == NULL) {
        puts("no memory");
    } else {
        upper->c = symbol;
        upper->next = HEAD;
    }
    return upper;
}

void init(HEAD *head) { head->point = NULL; }

void pushingCalc(double sym, HEAD *head) {
    OPERATIONS *tmp = head->point;
    OPERATIONS *new_node = malloc(sizeof(OPERATIONS));
    if (new_node == NULL) {
        puts("no memory");
    } else {
        new_node->oper = sym;
        new_node->point = tmp;
        head->point = new_node;
    }
}

double pop_calc(HEAD *head) {
    double x = INFINITY;
    OPERATIONS *tmp = head->point;
    if (tmp != NULL) {
        x = tmp->oper;
        head->point = tmp->point;
        free(tmp);
    }
    return x;
}

int priority(char symbol) {
    int priorityValue = 0;

    if (symbol == '~') {
        priorityValue = 5;
    } else if (symbol == COS || symbol == SIN || symbol == TG || symbol == CTG || symbol == SQRT ||
               symbol == LN) {
        priorityValue = 4;
    } else if (symbol == '*' || symbol == '/' || symbol == '^') {
        priorityValue = 3;
    } else if (symbol == '-' || symbol == '+') {
        priorityValue = 2;
    } else if (symbol == '(') {
        priorityValue = 1;
    }

    return priorityValue;
}
