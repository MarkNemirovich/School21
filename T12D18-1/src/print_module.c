#include "print_module.h"

#include <stdio.h>
#include <time.h>

char print_char(char ch) { return putchar(ch); }

void print_log(char (*print)(char), char* message) {
    int hours, minutes, seconds;
    time_t now = time(NULL);
    struct tm* local = localtime(&now);
    hours = local->tm_hour;   // получаем часы с полуночи (0-23)
    minutes = local->tm_min;  // получить минуты, прошедшие после часа (0-59)
    seconds = local->tm_sec;  // получаем секунды, прошедшие через минуту (0-59)

    printf("%s ", Log_prefix);
    printf("%d%d:%d%d:%d%d ", print(hours / 10), (hours % 10), print(minutes / 10), print(minutes % 10),
           print(seconds / 10), print(seconds % 10));
    printf("%s", message);
}