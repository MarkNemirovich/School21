#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>  // for getopt_long - converter long GNU flags to the short
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct flag {
  int b, e, v, n, s, t;
} flags;

int parse_flags(int argc, char** argv, flags* flags);
int read_file(char** argv, flags* flags);

#endif