#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LOG_H
#define LOG_H

typedef struct log_level {
    int level;
    char name[];
} log_level;

FILE* log_init(char* filename);
int logcat(FILE* log_file, char* message, log_level level);
int log_close(FILE* log_file);
char* get_time();

#endif