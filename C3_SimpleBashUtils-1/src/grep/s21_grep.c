#include "s21_grep.h"

int main(int argc, char** argv) {
  if (argc > 2) {
    int file_count = 0;
    Flags flags = {0};
    char** file_names = get_file_names(argc, argv, &file_count, &flags);
    parse_flags(argc, argv, &flags);
    if ((flags.regex_flag || flags.regex_file) & (argc < 4)) {
      if (!flags.suppress) perror("incorrect pattern\n");
    } else {
      grep(argc, argv, file_names, file_count, flags);
    }
    if (flags.pattern != NULL) free(flags.pattern);
    free_files(file_names, file_count, flags);
  }
  return 0;
}

char** get_file_names(int argc, char** argv, int* file_count, Flags* flags) {
  char** files = NULL;
  *file_count = 0;
  for (int i = 1; i < argc; i++) {
    const char* arg = argv[i];
    if (arg[0] == '-') {
      i++;
      continue;
    }
    if (i == 1) flags->incorrect_place = 1;
    // Увеличиваем размер массива указателей на строки
    files = (char**)realloc(files, (*file_count + 1) * sizeof(char*));
    if (files == NULL) {
      perror("Memory reallocation failed");
      exit(EXIT_FAILURE);
    }
    // Выделяем память и копируем строку
    files[*file_count] = strdup(arg);
    if (files[*file_count] == NULL) {
      perror("Memory allocation failed");
      exit(EXIT_FAILURE);
    }
    (*file_count)++;
  }
  (void)flags;
  return files;
}

void free_files(char** files, int file_count, Flags flags) {
  for (int i = flags.incorrect_place; i < file_count; i++) {
    free(files[i]);
  }
  free(files);
}

void parse_flags(int argc, char** argv, Flags* flags) {
  int symbol;
  flags->pattern = NULL;
  flags->pattern_size = 0;
  const char* short_flags_names = "eivclnhsfo";
  while ((symbol = getopt(argc, argv, short_flags_names)) != -1) {
    switch (symbol) {
      case 'e':  // done
        if (flags->pattern == NULL)
          flags->pattern = get_inline_pattern(argc, argv);
        flags->incorrect_place = 0;
        break;
      case 'i':  // done
        flags->regex_flag |= REG_ICASE;
        break;
      case 'v':  // done
        flags->invert = 1;
        break;
      case 'c':  // done
        flags->count = 1;
        break;
      case 'l':  // done
        flags->files_match = 1;
        break;
      case 'n':  // done
        flags->number_line = 1;
        break;
      case 's':  // done
        flags->suppress = 1;
        break;
      case 'h':  // done
        flags->headers_suppress = 1;
        break;
      case 'f':  // done
        get_inline_pattern_from_file(argv[optind], flags);
        flags->incorrect_place = 0;
        break;
      case 'o':  // done
        flags->overlap = 1;
        break;
      default:
        printf("incorrect flag \n");
        break;
    }
  }
}

char* get_inline_pattern(int argc, char** argv) {
  int flag = 0;
  char* line = NULL;
  size_t line_size = 0;
  for (int i = 0; i < argc; i++) {
    const char* arg = argv[i];
    if (flag) {
      if (line_size > 0) {  // Увеличиваем на 2 для добавления "\|" Чтобы регекс
                            // компилировал по каждому из слов
        line = (char*)realloc(line, line_size + 2);
        if (line == NULL) {
          perror("Memory reallocation failed");
          exit(EXIT_FAILURE);
        }
        line_size += 2;
        strcat(line,
               "\\|");  // Добавляем "\|" между паттернами, если строка не пуста
      }
      size_t arg_len = strlen(arg);
      // Перераспределение памяти для увеличения размера строки
      line = (char*)realloc(
          line,
          line_size +
              arg_len);  // Увеличиваем на 2 для добавления "\|" Чтобы регекс
                         // компилировал и искал совпадения по каждому из слов
      if (line == NULL) {
        perror("Memory reallocation failed");
        exit(EXIT_FAILURE);
      }
      strcat(line + line_size, arg);
      line_size += arg_len;
      flag = 0;
      line[line_size] = '\0';
    }
    if (strcmp(arg, "-e") == 0) flag = 1;
  }
  return line;
}

void get_inline_pattern_from_file(const char* filename, Flags* flags) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  char* line = NULL;
  size_t line_size = 0;
  while (getline(&line, &line_size, file) != -1) {
    if (strcmp(line, "\n") == 0) continue;
    line_size = strlen(line);
    if (flags->pattern != NULL) {
      // Увеличиваем на 2 для добавления "\\|"
      flags->pattern = (char*)realloc(flags->pattern, flags->pattern_size + 2);
      strcat(flags->pattern + flags->pattern_size, "\\|");
      flags->pattern_size += 2;
    }
    if (line_size > 0 && line[line_size - 1] == '\n') {
      line[line_size - 1] = '\0';  // Убираем символ новой строки
      line_size--;
    }
    // Перераспределение памяти для увеличения размера строки
    flags->pattern =
        (char*)realloc(flags->pattern, flags->pattern_size + line_size + 1);
    if (flags->pattern == NULL) {
      perror("Memory reallocation failed");
      exit(EXIT_FAILURE);
    }
    strcat(flags->pattern + flags->pattern_size, line);
    flags->pattern_size += line_size;
  }
  fclose(file);
  free(line);
}

void grep(int argc, char** argv, char** file_names, int file_count,
          Flags flags) {
  char** pattern = &argv[1];
  char** end = &argv[argc];
  regex_t preg_storage;
  regex_t* preg = &preg_storage;
  if (flags.pattern == NULL) {
    for (; pattern != end && pattern[0][0] == '-'; pattern++)
      ;
    if (pattern == end) {
      if (!flags.suppress) perror("no pattern\n");
      exit(1);
    }
    if (regcomp(preg, *pattern, flags.regex_flag)) {
      if (!flags.suppress) perror("failed to compile regex\n");
      exit(1);
    }
  } else {
    if (regcomp(preg, flags.pattern, flags.regex_flag)) {
      if (!flags.suppress) perror("failed to compile regex\n");
      exit(1);
    }
  }
  if (file_count < (2 + flags.incorrect_place)) flags.headers_suppress = 1;
  for (int i = flags.incorrect_place; i < file_count; i++) {
    FILE* file = fopen(file_names[i], "rb");
    if (file == NULL) {
      char error_message[LITTLE_SIZE] = "grep: ";
      strcat(error_message, file_names[i]);
      if (!flags.suppress) perror(error_message);
      continue;
    }
    if (flags.files_match)
      grep_file_name(file, flags, preg, file_names[i]);
    else if (flags.count)
      grep_count(file, file_names[i], flags, preg);
    else if (flags.invert)
      grep_file_inverted(file, flags, preg, file_names[i]);
    else
      grep_file(file, flags, preg, file_names[i]);
    fclose(file);
  }
}

void grep_file_name(FILE* file, Flags flags, regex_t* preg, char* filename) {
  char* line = 0;
  size_t length = 0;
  regmatch_t match;
  int count = 0;
  while (getline(&line, &length, file) > 0 && count == 0) {
    if (regexec(preg, line, 1, &match, 0) == flags.invert) count++;
  }
  if (count > 0) printf("%s\n", filename);
}

void grep_file(FILE* file, Flags flags, regex_t* preg, char* filename) {
  char* line = 0;
  size_t length = 0;
  regmatch_t match;
  int count = 0;
  while (getline(&line, &length, file) > 0) {
    count++;
    if (!regexec(preg, line, 1, &match, 0)) {
      if (flags.overlap)
        grep_file_overlaped(line, flags, preg, filename, count);
      else {
        if (!flags.headers_suppress) printf("%s:", filename);
        if (flags.number_line) printf("%i:", count);
        printf("%s", line);
        if (line[strlen(line) - 1] != '\n') printf("\n");
      }
    }
  }
  free(line);
  (void)flags;
}

void grep_file_inverted(FILE* file, Flags flags, regex_t* preg,
                        char* filename) {
  char* line = 0;
  size_t length = 0;
  regmatch_t match;
  int count = 0;
  while (getline(&line, &length, file) > 0) {
    count++;
    if (regexec(preg, line, 1, &match, 0)) {
      if (flags.overlap)
        ;
      else {
        if (!flags.headers_suppress) printf("%s:", filename);
        if (flags.number_line) printf("%i:", count);
        printf("%s", line);
        if (line[strlen(line) - 1] != '\n') printf("\n");
      }
    }
  }
  free(line);
  (void)flags;
}

void grep_file_overlaped(char* line, Flags flags, regex_t* preg, char* filename,
                         int line_count) {
  regmatch_t match;
  if (!regexec(preg, line, 1, &match, 0)) {
    char* remaining = line;
    while (!regexec(preg, remaining, 1, &match, 0)) {
      if (!flags.headers_suppress) printf("%s:", filename);
      if (flags.number_line) printf("%i:", line_count);
      printf("%lld %s\n", match.rm_eo - match.rm_so, remaining + match.rm_so);
      remaining = remaining + match.rm_eo;
    }
  }
}

void grep_count(FILE* file, char const* filename, Flags flags, regex_t* preg) {
  char* line = 0;
  size_t length = 0;
  regmatch_t match;
  int count = 0;
  while (getline(&line, &length, file) > 0) {
    if (regexec(preg, line, 1, &match, 0) == flags.invert) {
      if (strcmp(line, "\n") != 0 || flags.invert) count++;
    }
  }
  free(line);
  if (!flags.headers_suppress) printf("%s:", filename);
  printf("%i\n", count);
  (void)flags;
  (void)filename;
}