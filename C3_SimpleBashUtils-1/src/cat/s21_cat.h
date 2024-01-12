#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct flag {
  int b, e, v, n, s, t;
} flags;

int parseFlags(int argc, char** argv, flags* flags);
void readFile(char** argv, flags* flags);

#endif