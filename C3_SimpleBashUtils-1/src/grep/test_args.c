#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_inline_pattern_from_file(const char* filename) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  char* str = NULL;
  size_t str_size = 0;
  char* line = NULL;
  size_t line_size = 0;
  while (getline(&line, &line_size, file) != -1) {
    line_size = strlen(line);
    if (str != NULL) {
      // Увеличиваем на 2 для добавления "\\|"
      str = (char*)realloc(str, str_size + 2);
      if (str == NULL) {
        perror("Memory reallocation failed");
        exit(EXIT_FAILURE);
      }
      strcat(str + str_size, "\\|");
      str_size += 2;
    }
    if (line_size > 0 && line[line_size - 1] == '\n') {
      line[line_size - 1] = '\0';  // Убираем символ новой строки
      line_size--;
    }
    // Перераспределение памяти для увеличения размера строки
    str = (char*)realloc(str, str_size + line_size + 1);
    if (str == NULL) {
      perror("Memory reallocation failed");
      exit(EXIT_FAILURE);
    }
    strcat(str + str_size, line);
    str_size += line_size;
  }
  fclose(file);
  free(line);
  return str;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char* filename = argv[1];
  char* str = get_inline_pattern_from_file(filename);

  if (str != NULL) {
    printf("%s\n", str);
    free(str);
  }

  return EXIT_SUCCESS;
}