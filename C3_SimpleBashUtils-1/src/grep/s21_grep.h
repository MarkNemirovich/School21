#ifndef S21_GREP_H
#define S21_GREP_H

#include <errno.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10240
#define LITTLE_SIZE 256

typedef struct {
  int regex_flag, invert, count, files_match, number_line, headers_suppress,
      suppress, file_pattern, overlap, regex_file;
  char* pattern;
  size_t pattern_size;
} Flags;

enum error_codes {
  OK = 0,
  NO_MATCHES_FOUND = 1,
  ERROR = 2,
};

Flags parse_flags(int argc, char** argv);
void grep(int argc, char** argv, Flags flags);
void grep_file_name(FILE* file, Flags flags, regex_t* preg, char* filename);
void grep_file_inverted(FILE* file, Flags flags, regex_t* preg, char* filename);
void grep_file_overlaped(char* line, Flags flags, regex_t* preg, char* filename,
                         int line_count);
void grep_file(FILE* file, Flags flags, regex_t* preg, char* filename);
void invert(char* line);
void grep_count(FILE* file, char const* filename, Flags flags, regex_t* preg);

#endif