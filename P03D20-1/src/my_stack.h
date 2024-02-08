#ifndef MY_STACK_H
#define MY_STACK_H

#include "calculate.h"

#define MAX_STRING 100

struct st {
    char c;
    struct st *next;
};
struct st *push(struct st *, char);
char delete (struct st **);
int priority(char);
int parseToPolish(struct st *operations, char *input_str, char *output_str);
void init(HEAD *head);
void pushingCalc(double sym, HEAD *head);
double pop_calc(HEAD *head);

#endif