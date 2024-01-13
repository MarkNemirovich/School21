#include "s21_cat.h"

int main(int argc, char** argv) {
  flags flags = {0};
  parse_flags(argc, argv, &flags);
  char error_message[100] = "cat: ";
  while (optind < argc) {  // optind is an argv elements' index
    if (read_file(argv, &flags) == 1) {
      strcat(error_message, argv[optind]);
      perror(error_message);
      optind = argc;
    }
    optind++;
  }
  return 0;
}

int parse_flags(int argc, char** argv, flags* flags) {
  int symbol;
  const char* short_flags_names = "beEnsTtv";
  static struct option name_convert_option[] = {
      {"number-nonblank", 0, 0, 'b'},
      {"number", 0, 0, 'n'},
      {"squeeze-blank", 0, 0, 's'},
      {0, 0, 0, 0},
  };
  while ((symbol = getopt_long(argc, argv, short_flags_names, name_convert_option,
                               NULL)) != -1) {
    switch (symbol) {
      case 'b':
        flags->b = 1;
        break;
      case 'E':
        flags->e = 1;
        break;
      case 'e':
        flags->e = 1;
        flags->v = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 'T':
        flags->t = 1;
        break;
      case 't':
        flags->t = 1;
        flags->v = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      default:
        printf("incorrect flag \n");
        break;
    }
    if (flags->b) flags->n = 0;
  }
  return 0;
}

int read_file(char** argv, flags* flags) {
  int error = 0;
  FILE* fp = fopen(argv[optind], "r");
  if (fp != NULL) {
    int line_count = 1, end_count = 0, previous_symbol = '\n';
    while (!feof(fp)) {
      int c = fgetc(fp);
      if (c != EOF) {
        if (flags->s && c == '\n' && previous_symbol == '\n') {
          end_count++;
        } else {
          end_count = 0;
        }
        if (end_count > 1) continue;
        if (previous_symbol == '\n' && ((flags->b && c != '\n') || flags->n))
          printf("%6d\t", line_count++);
        if (flags->t && c == '\t') {
          printf("^");
          c = 'I';
        }
        if (flags->e && c == '\n') printf("$");
        if (flags->v && ((c >= 0 && c < 9) || (c > 10 && c < 32) ||
                         (c > 126 && c <= 160))) {
          printf("^");
          if (c > 126) {
            c -= 64;
          } else {
            c += 64;
          }
        }
        printf("%c", c);
        previous_symbol = c;
      }
    }
    fclose(fp);
  } else {
    error = 1;
  }
  return error;
}