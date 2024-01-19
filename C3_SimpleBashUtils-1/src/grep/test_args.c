#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// test burger

char* get_inline_pattern(int argc, char** argv) {
  int flag = 0;
  char* line = NULL;
  size_t line_size = 0;

  for (int i = 0; i < argc; i++) {
    const char* arg = argv[i];
    printf("%i:%s\n", i, arg);
    if (flag) {
      size_t arg_len = strlen(arg);
      // Перераспределение памяти для увеличения размера строки
      line =
          (char*)realloc(line, line_size + arg_len +
                                   2);  // Увеличиваем на 2 для добавления "\|"
      if (line == NULL) {
        perror("Memory reallocation failed");
        exit(EXIT_FAILURE);
      }
      if (line_size > 0) {
        strcat(line,
               "\\|");  // Добавляем "\|" между паттернами, если строка не пуста
      }
      strcat(line + line_size, arg);
      line_size += arg_len + 2;  // Увеличиваем на 2 для добавления "\|"
      flag = 0;
    }
    if (strcmp(arg, "-e") == 0) flag = 1;
  }

  return line;
}
// test

int main(int argc, char** argv) {
  char* str = get_inline_pattern(argc, argv);
  if (str != NULL) {
    printf("%s\n", str);
    free(str);
  }
  return 0;
}
// burger