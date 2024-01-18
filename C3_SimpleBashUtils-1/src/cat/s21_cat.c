#include "s21_cat.h"

int main(int argc, char** argv) {
  Flags flags = parse_flags(argc, argv);
  char error_message[BUFFER] = "cat: ";
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

Flags parse_flags(int argc, char** argv) {
  int symbol;
  Flags flags = {0};
  const char* short_flags_names = "beEnsTtv";
  static struct option name_convert_option[] = {
      {"number-nonblank", 0, 0, 'b'},
      {"number", 0, 0, 'n'},
      {"squeeze-blank", 0, 0, 's'},
      {0, 0, 0, 0},
  };
  while ((symbol = getopt_long(argc, argv, short_flags_names,
                               name_convert_option, NULL)) != -1) {
    switch (symbol) {
      case 'b':
        flags.b = 1;
        break;
      case 'E':
        flags.e = 1;
        break;
      case 'e':
        flags.e = 1;
        flags.v = 1;
        break;
      case 'n':
        flags.n = 1;
        break;
      case 's':
        flags.s = 1;
        break;
      case 'T':
        flags.t = 1;
        break;
      case 't':
        flags.t = 1;
        flags.v = 1;
        break;
      case 'v':
        flags.v = 1;
        break;
      default:
        printf("incorrect flag \n");
        break;
    }
    if (flags.b) flags.n = 0;
  }
  return flags;
}

int read_file(char** argv, Flags* flags) {
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
        if (flags->v) c = v_transform(c);
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

int v_transform(int ch) {
  if (ch == '\n' || ch == '\t') return ch;  // return is allowed in the pre-check
  if ((ch >= 0 && ch < 9) || (ch > 10 && ch < 32) || (ch > 126 && ch <= 160)) {
    printf("^");
    if (ch > 126) {
      ch -= 64;
    } else {
      ch += 64;
    }
  }
  return ch;
}