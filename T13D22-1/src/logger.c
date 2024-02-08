#include "logger.h"

#define MAX_LENGTH 1000
#define LETTERS 26
#define C ".c"
#define H ".h"
#define D "../src/ai_modules"

FILE* log_init(char* filename) {
    FILE* fs = NULL;
    fs = fopen(filename, "w+");
    return fs;
}
int logcat(FILE* log_file, char* message, log_level level) {
    int success = 1;
    if (log_file == NULL) success = 0;
    char flag[];
    fprintf(log_file, "%s ", level->name);
    fprintf(log_file, " %s  ", get_time());
    fprintf(log_file, "%s\n", message);
}

int log_close(FILE* log_file) { fclose(log_file); }

char* get_time() {
    int minutes, seconds, hours;
    time_t now;
    time(&now);
    struct tm* local = localtime(&now);
    hours = local->tm_hour;
    minutes = local->tm_min;
    seconds = local->tm_sec;
    char str[8];
    sprintf(str, "%02d:%02d:%02d", hours, minutes, seconds);
    return str;
}
