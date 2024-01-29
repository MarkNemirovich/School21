#ifndef S21_GREP_H
#define S21_GREP_H

#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int regex_flag, invert, count, files_match, number_line, headers_suppress,
      suppress, file_pattern, overlap, regex_file, incorrect_place;
  char* pattern;
  size_t pattern_size;
} Flags;

char** get_file_names(int argc, char** argv, int* file_count, Flags* flags);
void parse_flags(int argc, char** argv, Flags* flags);
void parse_flags_Mac(int argc, char** argv, Flags* flags);
void get_inline_pattern(const char* expression, Flags* flags);
void get_inline_pattern_from_file(const char* filename, Flags* flags);
void grep(int argc, char** argv, char** file_names, int file_count,
          Flags flags);
void grep_file_name(FILE* file, Flags flags, regex_t* preg, char* filename);
void grep_file_inverted(FILE* file, Flags flags, regex_t* preg, char* filename);
void grep_file_overlaped(char* line, Flags flags, regex_t* preg, char* filename,
                         int line_count);
void grep_file(FILE* file, Flags flags, regex_t* preg, char* filename);
void grep_count(FILE* file, char const* filename, Flags flags, regex_t* preg);
void free_files(char** lines, int line_count);
void invert(char* line);

#endif