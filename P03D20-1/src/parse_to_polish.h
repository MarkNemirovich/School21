#include <math.h>
#include <stdio.h>
#include <string.h>

#include "my_stack.h"

int parseToPolish(struct st *operations, char *input_str, char *output_str);
void stringToLow(char *string);
int checkTriginometry(char *input_str, int i, struct st **operations, char *output_str, int *point);
void handleTrigonometric(struct st **operations, char *output_str, int *point, char type);
void pushOutput(struct st **operations, char *output_str, int *point);