#include "s21_cat.h"

int main(int argc, char** argv) {
  flags flags = {0};
  parseFlags(argc, argv, &flags);
  while (optind < argc) {  // optind is an argv elements' index
    readFile(argv, &flags);
    optind++;
  }
  return 0;
}

int parseFlags(int argc, char** argv, flags* flags) {
  int symbol;
  const char* shortFlagsNames = "beEnsTtv";
  static struct option nameConvertOption[] = {
      // converter long GNU flags to the short
      {"number-nonblank", 0, 0, 'b'},
      {"number", 0, 0, 'n'},
      {"squeeze-blank", 0, 0, 's'},
      {0, 0, 0, 0},
  };
  while ((symbol = getopt_long(argc, argv, shortFlagsNames, nameConvertOption,
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

void readFile(char** argv, flags* flags) {
  FILE* fp = fopen(argv[optind], "r");
  if (fp != NULL) {
    int lineCount = 1, endCount = 0, previousSymbol = '\n';
    while (!feof(fp)) {
      int c = fgetc(fp);
      if (c == EOF) break;
      if (flags->s && c == '\n' && previousSymbol == '\n') {
        endCount++;
        if (endCount > 1) continue;
      } else {
        endCount = 0;
      }
      if (previousSymbol == '\n' && ((flags->b && c != '\n') || flags->n))
        printf("%6d\t", lineCount++);
      if (flags->t && c == '\t') {
        printf("^");
        c = 'I';
      }
      if (flags->e && c == '\n') printf("$");
      if (flags->v &&
          ((c >= 0 && c < 9) || (c > 10 && c < 32) || (c > 126 && c <= 160))) {
        printf("^");
        if (c > 126) {
          c -= 64;
        } else {
          c += 64;
        }
      }
      printf("%c", c);
      previousSymbol = c;
    }
    fclose(fp);
  } else {
    // printf("cat: %s: No such file or directory\n", argv[1]);
  }
}