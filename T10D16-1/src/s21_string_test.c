#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void s21_strlen_test();
void s21_strcmp_test();
void s21_strcpy_test();
void s21_strcat_test();
void s21_strchr_test();
void s21_strstr_test();
void s21_strtok_test();

int main() {
#ifdef LEN
    s21_strlen_test();
#elif CMP
    s21_strcmp_test();
#elif CPY
    s21_strcpy_test();
#elif CAT
    s21_strcat_test();
#elif CHR
    s21_strchr_test();
#elif STR
    s21_strstr_test();
#elif TOK
    s21_strtok_test();

#endif
    return 0;
}

void s21_strlen_test() {
    // Arrange
    char* good = "abc";
    char* bad = "qwertyuiopasdfghjklzxcvbnm";
    char* empty = "";
    // Act
    SIZE_T g_len = s21_strlen(good);
    SIZE_T b_len = s21_strlen(bad);
    SIZE_T e_len = s21_strlen(empty);
    // Assert
    printf("%s\t%lu\t%s\n", good, g_len, g_len == 3 ? "SUCCESS" : "FAIL");
    printf("%s\t%lu\t%s\n", bad, b_len, b_len == 26 ? "SUCCESS" : "FAIL");
    printf("%s\t%lu\t%s\n", empty, e_len, e_len == 0 ? "SUCCESS" : "FAIL");
}

void s21_strcmp_test() {
    // Arrange
    char* first_good = "abc";
    char* second_good = "abcd";
    char* bad = "qwertyuiopasdfghjklzxcvbnm";
    char* empty = "";
    // Act
    int c_equal = s21_strcmp(first_good, first_good);
    int c_less = s21_strcmp(first_good, second_good);
    int c_more = s21_strcmp(second_good, first_good);
    int c_bad = s21_strcmp(first_good, bad);
    int c_empty = s21_strcmp(empty, empty);
    // Assert
    printf("%s\t%s\t%d\t%s\n", first_good, first_good, c_equal, c_equal == 0 ? "SUCCESS" : "FAIL");
    printf("%s\t%s\t%d\t%s\n", first_good, second_good, c_less, c_less == -1 ? "SUCCESS" : "FAIL");
    printf("%s\t%s\t%d\t%s\n", second_good, first_good, c_more, c_more == 1 ? "SUCCESS" : "FAIL");
    printf("%s\t%s\t%d\t%s\n", first_good, bad, c_bad, c_bad == -1 ? "SUCCESS" : "FAIL");
    printf("%s\t%s\t%d\t%s\n", empty, empty, c_empty, c_empty == 0 ? "SUCCESS" : "FAIL");
}

void s21_strcpy_test() {
    // Arrange
    char source1[1000] = "xxx";
    char source2[1000] = "xxx";
    char source3[1000] = "xxx";
    char target1[1000] = "xxx";
    char target2[1000] = "xxx";
    char target3[1000] = "xxx";
    char* good = "abcd";
    char* bad = "qwertyuiopasdfghjklzxcvbnm";
    char* empty = "";
    // Act
    char* c_good = s21_strcpy(target1, good);
    char* c_bad = s21_strcpy(target2, bad);
    char* c_empty = s21_strcpy(target3, empty);
    // Assert
    printf("%s\t%s\t%s\t%s\n", source1, good, c_good, s21_strcmp(c_good, good) == 0 ? "SUCCESS" : "FAIL");
    printf("%s\t%s\t%s\t%s\n", source2, bad, c_bad, s21_strcmp(c_bad, bad) == 0 ? "SUCCESS" : "FAIL");
    printf("%s\t%s\t%s\t%s\n", source3, empty, c_empty, s21_strcmp(c_empty, empty) == 0 ? "SUCCESS" : "FAIL");
}
void s21_strcat_test() {
    // Arrange
    char source1[1000] = "xxx";
    char source2[1000] = "xxx";
    char source3[1000] = "xxx";
    char target1[1000] = "xxx";
    char target2[1000] = "xxx";
    char target3[1000] = "xxx";
    char* good = "abcd";
    char* bad = "qwertyuiopasdfghjklzxcvbnm";
    char* empty = "";
    // Act
    char* c_good = s21_strcat(target1, good);
    char* c_bad = s21_strcat(target2, bad);
    char* c_empty = s21_strcat(target3, empty);
    // Assert
    printf("%s\t%s\t%s\t%s\n", source1, good, c_good,
           s21_strcmp(c_good, "xxxabcd") == 0 ? "SUCCESS" : "FAIL");
    printf("%s\t%s\t%s\t%s\n", source2, bad, c_bad,
           s21_strcmp(c_bad, "xxxqwertyuiopasdfghjklzxcvbnm") == 0 ? "SUCCESS" : "FAIL");
    printf("%s\t%s\t%s\t%s\n", source3, empty, c_empty,
           s21_strcmp(c_empty, source3) == 0 ? "SUCCESS" : "FAIL");
}
void s21_strchr_test() {
    // Arrange
    char* good = "abc";
    char* bad = "qwertyuiopsdfghjklzxcvbnm";
    char* empty = "";
    int symbol = 'a';
    // Act
    const char* c_good = s21_strchr(good, symbol);
    const char* c_bad = s21_strchr(bad, symbol);
    const char* c_empty = s21_strchr(empty, symbol);
    // Assert
    printf("%s\t%c\t%s\n", good, symbol, *c_good == good[0] ? "SUCCESS" : "FAIL");
    printf("%s\t%c\t%s\n", bad, symbol, c_bad == NULL ? "SUCCESS" : "FAIL");
    printf("%s\t%c\t%s\n", empty, symbol, c_empty == NULL ? "SUCCESS" : "FAIL");
}
void s21_strstr_test() {
    // Arrange
    char target1[1000] = "xxxabcdef";
    char target2[1000] = "xxx";
    char* good = "abcd";
    char* bad = "qwertyuiopsdfghjklzxcvbnm";
    char* empty = "";
    // Act
    char* c_good = s21_strstr(target1, good);
    char* c_miss = s21_strstr(target2, good);
    char* c_bad = s21_strstr(target1, bad);
    char* c_empty = s21_strstr(target1, empty);
    // Assert
    printf("%s\t%s\t%s\t%s\n", target1, good, c_good, c_good - target1 == 3 ? "SUCCESS" : "FAIL");
    printf("%s\t%s\t%s\t%s\n", target2, good, c_miss, c_miss == NULL ? "SUCCESS" : "FAIL");
    printf("%s\t%s\t%s\t%s\n", target1, bad, c_bad, c_bad == NULL ? "SUCCESS" : "FAIL");
    printf("%s\t%s\t%s\t%s\n", target1, empty, c_empty, c_empty - target1 == 0 ? "SUCCESS" : "FAIL");
}
void s21_strtok_test() {
    // Arrange
    char base[] = "ab.cd.ef";
    char good[] = "ab.cd.ef";
    char bad[] = "qwertyuiopsdfghjklzxcvbnm";
    char empty[] = "";
    char* separators = ".";
    // Act
    char* c_good = s21_strtok(good, separators);
    char* c_bad = s21_strtok(bad, separators);
    char* c_empty = s21_strtok(empty, separators);
    // Assert
    /*while (c_good != NULL)  // пока есть лексемы
    {
        printf("%s\t%s\t%s\t%s\n", good, separators, c_good,
               s21_strcmp(c_good, "cd.ef") == 0 ? "SUCCESS" : "FAIL");
        c_good = strtok(NULL, separators);
    }*/
    printf("%s\t%s\t%s\t%s\n", base, separators, c_good, s21_strcmp(c_good, "ab") == 0 ? "SUCCESS" : "FAIL");
    printf("%s\t%s\t%s\t%s\n", bad, separators, c_bad, s21_strcmp(c_bad, bad) == 0 ? "SUCCESS" : "FAIL");
    printf("%s\t%s\t%s\t%s\n", empty, separators, c_empty, c_empty == NULL ? "SUCCESS" : "FAIL");
}