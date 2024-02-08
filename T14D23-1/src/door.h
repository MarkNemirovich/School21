#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DOOR_STRUCT_H
#define DOOR_STRUCT_H

typedef struct my_struct {
    int year, month, day, h, m, s, status, code;
} my_struct;

int compare(int a, int b);
int compare_doors(my_struct door_1, my_struct door_2);
void sort_doors(FILE* pfile, my_struct* doors, int n);
void print_doors(my_struct* doors, int n);
my_struct add_door();

#endif