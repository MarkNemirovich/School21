#include "s21_grep.h"

int main(int argc, char** argv) {
  int errcode = NO_MATCHES_FOUND;
  if (argc > 2) {
    Flags flags = parse_flags(argc, argv);
    if ((flags.regex_flag || flags.regex_file) & (argc < 4)) {
      errcode = ERROR;
    } else {
      grep(argc, argv, flags);
    }
  }
  return errcode;
}

Flags parse_flags(int argc, char** argv) {
  int symbol;
  Flags flags = {0};
  const char* short_flags_names = "eivclnhsfo";
  while ((symbol = getopt(argc, argv, short_flags_names)) != -1) {
    switch (symbol) {
      case 'e':
        flags.regex_flag |= REG_EXTENDED;
        break;
      case 'i':  // done
        flags.regex_flag |= REG_ICASE;
        break;
      case 'v':  // done
        flags.invert = 1;
        break;
      case 'c':  // done
        flags.count = 1;
        break;
      case 'l':  // done
        flags.files_match = 1;
        break;
      case 'n':  // done
        flags.number_line = 1;
        break;
      case 's':  // done
        flags.suppress = 1;
        break;
      case 'h':  // done
        flags.headers_suppress = 1;
        break;
      case 'f':
        break;
      case 'o':  // done
        flags.overlap = 1;
        break;
      default:
        printf("incorrect flag \n");
        break;
    }
  }
  return flags;
}

void grep(int argc, char** argv, Flags flags) {
  char** pattern = &argv[1];
  char** end = &argv[argc];
  regex_t preg_storage;
  regex_t* preg = &preg_storage;
  int file_count = 0;
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
  for (char** filename = pattern + 1; filename != end && file_count < 2;
       filename++) {
    if (**filename == '-') continue;
    file_count++;
  }
  if (file_count < 2) flags.headers_suppress = 1;
  for (char** filename = pattern + 1; filename != end; filename++) {
    if (**filename == '-') continue;
    FILE* file = fopen(*filename, "rb");
    if (file == NULL) {
      char error_message[LITTLE_SIZE] = "grep: ";
      strcat(error_message, *filename);
      if (!flags.suppress) perror(error_message);
      continue;
    }
    if (flags.files_match)
      grep_file_name(file, flags, preg, *filename);
    else if (flags.count)
      grep_count(file, *filename, flags, preg);
    else if (flags.invert)
      grep_file_inverted(file, flags, preg, *filename);
    else
      grep_file(file, flags, preg, *filename);
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
      printf("%.*s\n", match.rm_eo - match.rm_so, remaining + match.rm_so);
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