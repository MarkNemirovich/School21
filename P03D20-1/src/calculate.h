#ifndef CALCULATE_H
#define CALCULATE_H

#define SIN 's'
#define COS 'c'
#define TG 't'
#define CTG 'g'
#define SQRT 'q'
#define LN 'l'

typedef struct OPERATIONS {
    double oper;
    struct OPERATIONS *point;
} OPERATIONS;

typedef struct HEAD {
    struct OPERATIONS *point;
} HEAD;

double counter(char *output_str, HEAD *head, double x);
int addFuncForGraph(char **graph, int height, int width, char *out, HEAD *head);
int firstConditions(char *output_str, HEAD *head, int i, double x);
int secondConditions(char *output_str, HEAD *head, int i);
int thirdConditions(char *output_str, HEAD *head, int i);
int numberLength(const char *string);
void subString(const char *string, char *target, int length);
int isDigit(char c);
double convertToDouble(const char *string);
int popTwo(double *num1, double *num2, HEAD *head);

#endif