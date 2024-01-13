#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 256
#define FILE_BUFFER 10001

typedef struct flag {
  int e, i, v, c, l, n, h, s, f, o;
} flags;

int parse_flags(int argc, char** argv, flags* flags, char (*templates)[BUFFER],
                int* templates_amount, char (*files)[BUFFER], int* files_amount,
                char (*file_templates)[BUFFER], int* file_templates_amount);

int e_flag_parse(char** argv, int* check_f, int argc, char (*templates)[BUFFER],
                 int** templates_amount, int* template_file);

int f_flag_parse(char** argv, int* check_f, int count,
                 char (*file_templates)[BUFFER], int** file_templates_amount,
                 int* template_file);

void merge_templates(char (*templates)[BUFFER], int* templates_amount,
                     char (*file_templates)[BUFFER],
                     int* file_templates_amount);

void grep(char (*t_arr)[BUFFER], int count_t, char (*arr_f)[BUFFER],
          int count_f, flags* flag);

void prepare_for_search(int success, char* text, int* match, int* line_check,
                        flags* flags);

void o_flag_print(int match, int* o_repeater, int line_number, flags* flags,
                  regmatch_t* pmatch, char* text, char (*files)[BUFFER],
                  int files_amount, int i);

void print_n_flag(int match, flags* flags, int line_number, char* text,
                  char (*files)[BUFFER], int files_amount, int i);

void print_f_flag(flags* flags, char (*files)[BUFFER], int files_amount,
                  int line_matches, int i);

void print_matches(flags* flags, char (*files)[BUFFER], int files_amount,
                   int line_matches, int i);
#endif