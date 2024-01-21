#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>  // for getopt_long - converter long GNU flags to the short
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 256

typedef struct {
  int b, e, v, n, s, t;
} Flags;

Flags parse_flags(int argc, char** argv);
int read_file(char** argv, Flags* flags);
int v_transform(int ch);

#endif