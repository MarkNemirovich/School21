#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"

#define MAX_LENGTH 1000
#define LETTERS 26
#define C ".c"
#define H ".h"
#define D "../src/ai_modules"

void clearH(const char* directory, const char* path);
int detectCFiles(const char* name, const char* comparer);
void encrypt(FILE* file, int n);
void encryptC(const char* directory, const char* path);
void nextdir();
int main();

void clearH(const char* directory, const char* path) {
    FILE* file = NULL;
    char* str = malloc(sizeof(char) * (20 + strlen(path)));
    if (str != NULL) {
        strcpy(str, directory);
        strcat(str, "/");
        strcat(str, path);
        file = fopen(str, "w");
    }
    free(str);
    fclose(file);
}

int detectCFiles(const char* name, const char* comparer) {
    int flag = 0;
    int length = strlen(name);
    int point = (strstr(name, comparer) - name);
    if (point == length - 2) flag = 1;
    return flag;
}

void encrypt(FILE* file, int n) {
    int c = fgetc(file);
    while (c != EOF) {
        fseek(file, -1, SEEK_CUR);
        int flag = 0;
        if (c >= 'A' && c <= 'Z') {
            c = c + (n % LETTERS);
            if (c > 'Z') c = 'A' + (c - 'Z') - 1;
            if (c < 'A') c = 'Z' + (c - 'A') + 1;
            fprintf(file, "%c", c);
            flag = 1;
        }
        if (!flag && c >= 'a' && c <= 'z') {
            c = c + (n % LETTERS);
            if (c > 'z') c = 'a' + (c - 'z') - 1;
            if (c < 'a') c = 'z' + (c - 'a') + 1;
            fprintf(file, "%c", c);
            flag = 1;
        }
        if (!flag) fprintf(file, "%c", c);
        c = fgetc(file);
    }
}

void encryptC(const char* directory, const char* path) {
    FILE* file = NULL;
    char* str = malloc(sizeof(char) * (20 + strlen(path)));
    if (str != NULL) {
        strcpy(str, directory);
        strcat(str, "/");
        strcat(str, path);
        file = fopen(str, "r+");
        int shift;
        scanf("%d", &shift);
        encrypt(file, shift);
    }
    free(str);
    fclose(file);
}

void nextdir() {
    DIR* directory;
    struct dirent* entry;
    if ((directory = opendir(D)) != NULL) {
        while ((entry = readdir(directory)) != NULL) {
            int c = detectCFiles(entry->d_name, C);
            int h = detectCFiles(entry->d_name, H);
            if (c) {
                encryptC(D, entry->d_name);
            }
            if (h) {
                clearH(D, entry->d_name);
            }
        }
        if (closedir(directory) == -1) {
            perror("could not close directory");
        }
    } else {
        perror("could not open directory");
    }
}

int main() {
    int mode = 0;
    FILE* fs = NULL;
    FILE* log = log_init("log");
    log_level* debug = create_log(0, "DEBUG");
    log_level* info = create_log(0, "INFO");
    log_level* warning = create_log(0, "WARNING");
    log_level* error = create_log(0, "ERROR");
    char* path = malloc(MAX_LENGTH * sizeof(char));
    while (mode != -1) {
        scanf("%d", &mode);
        char fullPath[MAX_LENGTH + 7] = "../src/";
        char buffer[MAX_LENGTH];
        if (mode == 1) {
            scanf("%s", path);
            strcat(fullPath, path);
            fs = fopen(fullPath, "r");
            if (fs != NULL) {
                *buffer = '\0';
                int count = 0;
                while (fscanf(fs, "%s", buffer) > 0) {
                    count++;
                    printf("%s", buffer);
                }
                if (count == 0) {
                    printf("n/a");
                    logcat(log, "File does not exist", *error);
                }
            } else
                printf("n/a");
            fclose(fs);
            printf("\n");
        }
        if (mode == 2) {
            strcat(fullPath, path);
            fs = fopen(fullPath, "r+");
            if (fs != NULL) {
                fseek(fs, 0, SEEK_END);
                *buffer = '\0';
                scanf("%s", buffer);
                fprintf(fs, "%s", buffer);
                char str[200];
                sprintf(str, "%s %s %s", "File", path, "appended by");
                logcat(log, str, *info);
            } else {
                printf("n/a\n");
                    logcat(log, "File does not exist", *error);
            }
            fclose(fs);
        }
        if (mode == 3) {
            nextdir();
        }
    }
    free(path);
    return 0;
}