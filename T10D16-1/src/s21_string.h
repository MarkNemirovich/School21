#ifndef STRING_H
#define STRING_H

#define SIZE_T unsigned long int

SIZE_T s21_strlen(const char* str);
int s21_strcmp(const char* str1, const char* str2);
char* s21_strcpy(char* destptr, const char* srcptr);
char* s21_strcat(char* destination, const char* append);
const char* s21_strchr(const char* string, int symbol);
char* s21_strstr(const char* str1, const char* str2);
char* s21_strtok(char* string, const char* delim);
#endif