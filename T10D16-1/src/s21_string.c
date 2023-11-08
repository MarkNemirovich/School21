#include "s21_string.h"

#include <stdio.h>  // FOR NULL

char* s21_strtok_r(char* string, const char* delim, char** last);

SIZE_T s21_strlen(const char* str) {
    SIZE_T length = 0;
    for (; *(str + length); length++)
        ;
    return length++;
}

int s21_strcmp(const char* str1, const char* str2) {
    int result = 0;
    SIZE_T l1 = 0, l2 = 0;
    for (; str1[l1] != '\0' && str2[l2] != '\0'; l1++, l2++) {
        if (str1[l1] > str2[l2])
            result = 1;
        else if (str1[l1] < str2[l2])
            result = -1;
        else
            result = 0;
    }
    if (str1[l1] > str2[l2])
        result = 1;
    else if (str1[l1] < str2[l2])
        result = -1;
    else
        result = 0;
    return result;
}

char* s21_strcpy(char* destptr, const char* srcptr) {
    SIZE_T l1 = 0, l2 = 0;
    for (; srcptr[l2] != '\0'; l1++, l2++) {
        destptr[l1] = srcptr[l2];
    }
    destptr[l1] = srcptr[l2];
    return destptr;
}

char* s21_strcat(char* destination, const char* append) {
    char* ptr = destination + s21_strlen(destination);
    while (*append != '\0') {
        *ptr++ = *append++;
    }
    *ptr = '\0';
    return destination;
}

const char* s21_strchr(const char* string, int symbol) {
    char* ans = NULL;
    for (; *string != symbol && *string != '\0'; string++)
        ;
    if (*string != '\0') ans = (char*)string;
    return ans;
}

char* s21_strstr(const char* str1, const char* str2) {
    char *a = NULL, *b;
    if (*str2 == '\0')
        a = (char*)str1;
    else {
        b = (char*)str2;
        for (; a == NULL && *str1 != '\0'; str1++) {
            if (*b == '\0') {
                a = (char*)(str1 - s21_strlen(str2));
            } else if (*str1 == *b) {
                b++;
            } else {
                b = (char*)str2;
            }
        }
    }
    return a;
}

char* s21_strtok(char* string, const char* delim) {
    static char* last;
    return s21_strtok_r(string, delim, &last);
}
char* s21_strtok_r(char* string, const char* delim, char** last) {
    char* spanp;
    int c, sc;
    char* tok = string;
    if (string == NULL && (string = *last) == NULL) {
        tok = NULL;
    }
    char flag = 1;
    while (tok != NULL && flag == 1) {
        flag = 0;
        c = *string++;
        for (spanp = (char*)delim; (sc = *spanp++) != 0;) {
            if (c == sc) flag = 1;
        }
    }

    if (tok != NULL && c == 0) { /* no non-delimiter characters */
        *last = NULL;
        tok = NULL;
    }
    if (tok != NULL) tok = string - 1;
    /*
     * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
     * Note that delim must have one NUL; we stop if we see that, too.
     */
    flag = 1;
    for (; tok != NULL && flag == 1;) {
        c = *string++;
        spanp = (char*)delim;
        do {
            if ((sc = *spanp++) == c) {
                if (c == 0)
                    string = NULL;
                else
                    string[-1] = 0;
                *last = string;
                flag = 0;
            }
        } while (sc != 0);
    }
    return tok;
}