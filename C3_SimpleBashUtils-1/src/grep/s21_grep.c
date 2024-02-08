#include "s21_grep.h"

int main(int argc, char** argv) {
  int file_count = 0;
  Flags flags = {0};
  flags.pattern = NULL;
  if (argc > 2) {
    char** file_names = get_file_names(argc, argv, &file_count, &flags);
    if (file_names != NULL) {
#ifdef MAC
      parse_flags_Mac(argc, argv, &flags);
#else
      parse_flags(argc, argv, &flags);
      if (flags.files_match) flags.headers_suppress = 0;
#endif
      if ((flags.regex_flag || flags.regex_file) & (argc < 4)) {
        if (!flags.suppress) perror("incorrect pattern\n");
      } else {
        grep(argc, argv, file_names, file_count, flags);
      }
      free(flags.pattern);
      free_files(file_names, file_count);
    }
  }
  return 0;
}

int add_file(char*** files, int* file_count, const char* line) {
  int error = 0;
  (*files) = (char**)realloc((*files), (*file_count + 1) * sizeof(char*));
  if (*files == NULL)
    error = 1;
  else {
    (*files)[*file_count] = (char*)malloc(strlen(line) + 1);
    if ((*files)[*file_count] == NULL)
      error = 1;
    else {
      strcpy((*files)[*file_count], line);
      (*files)[*file_count][strlen(line)] = '\0';
      (*file_count)++;
    }
  }
  return error;
}

char** get_file_names(int argc, char** argv, int* file_count, Flags* flags) {
  char** files = NULL;
  char* match_word = NULL;
  char match_word_flag = 0;
  *file_count = 0;
  int error = 0;
  for (int i = 1; i < argc && error == 0; i++) {
    const char* arg = argv[i];
    if (arg[0] == '-') {
      if (arg[1] == 'f' || arg[1] == 'e') {
        i++;
        if (match_word != NULL) {
          error = add_file(&files, file_count, match_word);
        } else
          match_word_flag = 1;
      }
    } else {
      if (!match_word_flag) {
        match_word = (char*)malloc(strlen(arg) + 1);
        if (match_word == NULL)
          error = 1;
        else {
          strcpy(match_word, arg);
          match_word[strlen(arg)] = '\0';
          match_word_flag = 1;
        }
      } else {
        error = add_file(&files, file_count, arg);
      }
    }
  }
  (void)flags;
  char** str = (char**)realloc(files, (*file_count + 1) * sizeof(char*));
  if (str == NULL)
    error = 1;
  else {
    files = str;
    files[*file_count] = NULL;
  }
  free(match_word);
  if (error) {
    free_files(files, *file_count);
  }
  return files;
}

void free_files(char** files, int file_count) {
  for (int i = 0; i < file_count; i++) {
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
        get_inline_pattern(argv[optind], flags);
        flags->incorrect_place = 0;
        break;
      case 'i':  // done
        flags->regex_flag = REG_ICASE;
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

void parse_flags_Mac(int argc, char** argv, Flags* flags) {
  flags->pattern = NULL;
  flags->pattern_size = 0;
  for (int i = 1; i < argc; i++) {
    const char* arg = argv[i];
    if (arg[0] == '-') {
      if (strchr(arg, 'e') != NULL) {
        i++;
        get_inline_pattern(argv[i], flags);
        flags->incorrect_place = 0;
      }
      if (strchr(arg, 'i') != NULL) flags->regex_flag = REG_ICASE;
      if (strchr(arg, 'v') != NULL) flags->invert = 1;
      if (strchr(arg, 'c') != NULL) flags->count = 1;
      if (strchr(arg, 'l') != NULL) flags->files_match = 1;
      if (strchr(arg, 'n') != NULL) flags->number_line = 1;
      if (strchr(arg, 's') != NULL) flags->suppress = 1;
      if (strchr(arg, 'h') != NULL) flags->headers_suppress = 1;
      if (strchr(arg, 'f') != NULL) {
        i++;
        get_inline_pattern_from_file(argv[i], flags);
        flags->incorrect_place = 0;
      }
      if (strchr(arg, 'o') != NULL) flags->overlap = 1;
    }
  }
}

void get_inline_pattern(const char* expression, Flags* flags) {
  char* str = NULL;
  size_t line_size = strlen(expression);
  size_t new_pattern_size =
      flags->pattern_size + line_size + (flags->pattern_size > 0 ? 2 : 1);
  str = realloc(flags->pattern, new_pattern_size);
  if (str == NULL) {
    perror("Memory reallocation failed");
    free(str);
    free(flags->pattern);
  } else {
    flags->pattern = str;
    if (flags->pattern_size > 0) {
      strcat(flags->pattern, "|");
      strcat(flags->pattern, expression);
    } else
      strcpy(flags->pattern, expression);
    flags->pattern_size = new_pattern_size;  // Update the pattern size
    flags->pattern[flags->pattern_size - 1] = '\0';
  }
}

void get_inline_pattern_from_file(const char* filename, Flags* flags) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file sas a pattern");
  } else {
    char* line = NULL;
    char* str = NULL;
    size_t line_size = 0;
    int error = 0;
    while (getline(&line, &line_size, file) != -1 && error == 0) {
      if (strcmp(line, "\n") == 0) line[0] = '.';
      line_size = strlen(line);
      if (line[line_size - 1] == '\n') {
        line[line_size - 1] = '\0';
      }
      size_t new_pattern_size =
          flags->pattern_size + line_size + (flags->pattern_size > 0 ? 2 : 1);
      str = realloc(flags->pattern, new_pattern_size);
      if (str == NULL) {
        perror("Memory reallocation failed");
        free(str);
        free(flags->pattern);
        error = 1;
      } else {
        flags->pattern = str;
        if (flags->pattern_size > 0) {
          strcat(flags->pattern, "|");
          strcat(flags->pattern, line);
        } else
          strcpy(flags->pattern, line);
        flags->pattern_size = new_pattern_size;  // Update the pattern size
      }
    }
    if (error == 0) flags->pattern[flags->pattern_size - 1] = '\0';
    fclose(file);
    free(line);
  }
}

void print_error(char* file_name) {
  char* error_message = (char*)malloc(strlen("grep: ") + strlen(file_name) + 1);
  strcpy(error_message, "grep: ");
  strcat(error_message, file_name);
  perror(error_message);
  free(error_message);
}

void grep(int argc, char** argv, char** file_names, int file_count,
          Flags flags) {
  char** pattern = &argv[1];
  char** end = &argv[argc];
  regex_t preg_storage;
  regex_t* preg = &preg_storage;
  int error = 0;
  if (flags.pattern == NULL) {
    for (; pattern != end && pattern[0][0] == '-'; pattern++)
      ;
    if (pattern == end)
      error = 1;
    else if (regcomp(preg, *pattern, flags.regex_flag | REG_EXTENDED))
      error = 1;
  } else {
    if (regcomp(preg, flags.pattern, flags.regex_flag | REG_EXTENDED))
      error = 1;
  }
  if (file_count < 2) flags.headers_suppress = 1;
  for (int i = 0; i < file_count && error == 0; i++) {
    FILE* file = fopen(file_names[i], "rb");
    if (file == NULL) {
      if (!flags.suppress) print_error(file_names[i]);
    } else {
#ifdef MAC
      if (flags.count) grep_count(file, file_names[i], flags, preg);
      if (flags.files_match) grep_file_name(file, flags, preg, file_names[i]);
      if (!flags.files_match) {
        if (flags.invert)
          grep_file_inverted(file, flags, preg, file_names[i]);
        else
          grep_file(file, flags, preg, file_names[i]);
      }
#else
      if (flags.files_match)
        grep_file_name(file, flags, preg, file_names[i]);
      else if (flags.count)
        grep_count(file, file_names[i], flags, preg);
      else if (flags.invert)
        grep_file_inverted(file, flags, preg, file_names[i]);
      else
        grep_file(file, flags, preg, file_names[i]);
#endif
      fclose(file);
    }
  }
  regfree(preg);  // Освобождаем ресурсы, выделенные regcomp
}

void grep_file_name(FILE* file, Flags flags, regex_t* preg, char* filename) {
  char* line = NULL;
  size_t length = 0;
  regmatch_t match;
  int count = 0;
  while (getline(&line, &length, file) > 0 && count == 0) {
    if (regexec(preg, line, 1, &match, 0) == flags.invert) count++;
  }
  free(line);
  if (count > 0) printf("%s\n", filename);
}

void grep_file(FILE* file, Flags flags, regex_t* preg, char* filename) {
  char* line = NULL;
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
        if (!flags.files_match) printf("%s", line);
        if (line[strlen(line) - 1] != '\n') printf("\n");
      }
    }
  }
  free(line);
  (void)flags;
}

void grep_file_inverted(FILE* file, Flags flags, regex_t* preg,
                        char* filename) {
  char* line = NULL;
  size_t length = 0;
  regmatch_t match;
  int count = 0;
  while (getline(&line, &length, file) > 0) {
    count++;
    if (!regexec(preg, line, 1, &match, 0)) {
    } else {
      if (flags.overlap) {
#ifdef MAC
        if (!flags.headers_suppress) printf("%s:", filename);
        if (flags.number_line) printf("%i:", count);
        if (!flags.files_match) printf("%s", line);
        if (line[strlen(line) - 1] != '\n') printf("\n");
#endif
      } else {
        if (!flags.headers_suppress) printf("%s:", filename);
        if (flags.number_line) printf("%i:", count);
        if (!flags.files_match) printf("%s", line);
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
      for (char* p = remaining + match.rm_so; p < remaining + match.rm_eo; p++)
        if (!flags.files_match) printf("%c", *p);
      printf("\n");
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
#ifdef MAC
  if (!flags.headers_suppress) printf("%s:", filename);
  if (flags.files_match) {
    printf("%d\n", count > 0);
    if (count > 0) printf("%s\n", filename);
  } else
    printf("%i\n", count);
#else
  if ((flags.files_match && count > 0) || !flags.files_match) {
    if (!flags.headers_suppress) printf("%s:", filename);
    printf("%i\n", count);
  }
#endif
  (void)flags;
  (void)filename;
}