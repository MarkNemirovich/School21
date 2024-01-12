#include "s21_grep.h"

int main(int argc, char** argv) {
  flags flags = {0};
  char templates[argc][BUFFER];
  char files[argc][BUFFER];
  char file_templates[argc][BUFFER];
  int templates_amount = 0;
  int files_amount = 0;
  int file_templates_amount = 0;
  if (argc >= 3 &&
      parseFlags(argv, &flags, argc, templates, &templates_amount, files,
                 &files_amount, file_templates, &file_templates_amount) != 1) {
    merge_templates(templates, &templates_amount, file_templates,
                    &file_templates_amount);
    grep(templates, templates_amount, files, files_amount, &flags);
  }
  return 0;
}

int parse_flags(char** argv, flags* flags, int argc, char (*templates)[BUFFER],
                int* templates_amount, char (*files)[BUFFER], int* files_amount,
                char (*file_templates)[BUFFER], int* file_templates_amount) {
  const char* flags = "eivclnhsfo";
  int error = 0;
  int template_file = 0;
  for (int j = 1; j < argc; j++) {
    int check_f = 0;
    if (argv[j][0] == '-') {
      for (size_t i = 1; i < strlen(argv[j]) && check_f == 0; i++) {
        if (strchr(flags, (int)argv[j][i]) == NULL && check_f == 0) {
          error = 1;
          break;
        }
        if (argv[j][i] == 'e')
          error = e_flag_parse(argv, &check_f, argc, templates,
                               &templates_amount, &template_file);
        else if (argv[j][i] == 'i')
          flags->i = 1;
        else if (argv[j][i] == 'v')
          flags->v = 1;
        else if (argv[j][i] == 'c')
          flags->c = 1;
        else if (argv[j][i] == 'l')
          flags->l = 1;
        else if (argv[j][i] == 'n')
          flags->n = 1;
        else if (argv[j][i] == 'h')
          flags->h = 1;
        else if (argv[j][i] == 's')
          flags->s = 1;
        else if (argv[j][i] == 'f')
          error = f_flag_parse(argv, &check_f, argc, file_templates,
                               &file_templates_amount, &template_file);
        else if (argv[j][i] == 'o')
          flags->o = 1;
      }
    } else if (template_file == 1 && check_f == 0) {
      strcpy(files[(*files_amount)++], argv[j]);
      continue;
    } else if (template_file == 0 && check_f == 0) {
      template_file = 1;
      strcpy(templates[(*templates_amount)++], argv[j]);
      continue;
    }
  }
  if (flags->v == 1) flags->o = 0;
  return error;
}

int e_flag_parse(char** argv, int* check_f, int argc, char (*templates)[BUFFER],
                 int** templates_amount, int* template_file) {
  int error = 0;
  for (int j = 1; j < argc; j++) {
    for (size_t i = 1; i < strlen(argv[j]) && *check_f == 0; i++) {
      if (strlen(argv[j]) == i + 1 && *check_f == 0) {
        if (!(j == argc - 1)) {
          strcpy(templates[(**templates_amount)++], argv[++j]);
          *template_file = 1;
          *check_f = 1;
        } else {
          error = 1;
        }
      } else if (*check_f == 0) {
        *check_f = 1;
        strcpy(templates[(**templates_amount)++], (argv[j] + i + 1));
        *template_file = 1;
      }
    }
  }
  return error;
}

int f_flag_parse(char** argv, int* check_f, int count,
                 char (*file_templates)[BUFFER], int** file_templates_amount,
                 int* template_file) {
  int error = 0;
  for (int j = 1; j < count; j++) {
    for (size_t i = 1; i < strlen(argv[j]) && *check_f == 0; i++) {
      if (strlen(argv[j]) == i + 1 && *check_f == 0) {
        if (!(j == count - 1)) {
          strcpy(file_templates[(**file_templates_amount)++], argv[++j]);
          *check_f = 1;
          *template_file = 1;
        } else {
          error = 1;
        }
      } else if (check_f == 0) {
        *check_f = 1;
        strcpy(file_templates[(**file_templates_amount)++], (argv[j] + i + 1));
        *template_file = 1;
      }
    }
  }
  return error;
}

void merge_templates(char (*templates)[BUFFER], int* templates_amount,
                     char (*file_templates)[BUFFER],
                     int* file_templates_amount) {
  for (int i = 0; i < (*file_templates_amount); i++) {
    FILE* fp = fopen(file_templates[i], "r");
    if (fp != NULL) {
      char str[BUFFER];
      while (fgets(str, BUFFER, fp) != NULL) {
        int length = strlen(str);
        if (length > 1 && str[length - 1] == '\n') str[length - 1] = '\0';
        strcpy(templates[(*templates_amount)++], str);
      }
      fclose(fp);
    } else {
      // printf("grep: %s: No such file or directory\n", argv[1]);
    }
  }
}

void grep(char (*templates)[BUFFER], int templates_amount,
          char (*files)[BUFFER], int files_amount, flags* flags) {
  int reg_flag = REG_EXTENDED;              // extended regix
  if (flags->i == 1) reg_flag = REG_ICASE;  // ignore upper/low case
  for (int i = 0; i < files_amount; i++) {
    FILE* fp = fopen(files[i], "r");
    if (fp != NULL) {
      int line_matches = 0, line_number = 1;
      char text[FILE_BUFFER] = {0};
      while (fgets(text, FILE_BUFFER - 1, fp) != NULL) {
        int match = 0, o_repeater = 0;
        regex_t reg;  // structure with founded elements
        int line_check = 0;
        for (int j = 0; j < templates_amount; j++) {
          regmatch_t pmatch[1] = {0};
          regcomp(&reg, templates[j], reg_flag);
          int success = regexec(&reg, text, 1, pmatch, 0);
          prepare_for_search(success, text, &match, &line_check, flags);
          o_flag_print(match, &o_repeater, line_number, flags, pmatch, text,
                       files, files_amount, i);
          if (line_check == 1) match = 0;
          regfree(&reg);
        }
        print_n_flag(match, flags, line_number, text, files, files_amount,
                     i);  // text output
        line_matches += match;
        line_number++;
      }
      print_f_flag(flags, files, files_amount, line_matches, i);
      if (flags->l == 1 && line_matches > 0) printf("%s\n", files[i]);
      print_matches(flags, files, files_amount, line_matches, i);
      fclose(fp);
    } else {
      if (flags->s != 1)
        fprintf(stderr, "grep: %s: No such file or directory\n", files[i]);
    }
  }
}

void prepare_for_search(int success, char* text, int* match, int* line_check,
                        flags* flags) {
  if (strchr(text, '\n') == NULL) strcat(text, "\n");
  if (success == 0 && flags->v != 1) *match = 1;
  if (success == 0 && flags->v == 1) *line_check = 1;
  if ((success = REG_NOMATCH) && flags->v == 1) *match = 1;
}

void o_flag_print(int match, int* o_repeater, int line_number, flags* flags,
                  regmatch_t* pmatch, char* text, char (*files)[BUFFER],
                  int files_amount, int i) {
  if (match == 1 && flags->o == 1 && flags->l != 1 && flags->c != 1) {
    if (flags->n == 1 && *o_repeater == 0) {  // обработка флагa o
      printf("%d:", line_number);
      *o_repeater = 1;
    }
    for (int j = pmatch[0].rm_so; j < pmatch[0].rm_eo; j++)
      printf("%c", text[j]);
    if (pmatch[0].rm_so != pmatch[0].rm_eo) printf("\n");
    if (files_amount > 1 && flags->h != 1 && pmatch[0].rm_eo != pmatch[0].rm_so)
      printf("%s:", files[i]);
  }
}

void print_n_flag(int match, flags* flags, int line_number, char* text,
                  char (*files)[BUFFER], int files_amount, int i) {
  if (match == 1 && flags->l != 1 && flags->c != 1 && flags->o != 1) {
    if (flags->h != 1 && flags->l != 1 && files_amount > 1)
      printf("%s:", files[i]);
    if (match == 1 && flags->l != 1 && flags->c != 1 && flags->n == 1)
      printf("%d:", line_number);
    printf("%s", text);
  }
}

void print_f_flag(flags* flags, char (*files)[BUFFER], int files_amount,
                  int line_matches, int i) {
  if (flags->l == 1 && flags->c == 1) {
    if (files_amount > 1 && flags->h != 1) printf("%s:", files[i]);
    if (line_matches >= 1)
      printf("1\n");
    else
      printf("0\n");
  }
}

void print_matches(flags* flags, char (*files)[BUFFER], int files_amount,
                  int line_matches, int i) {
  if (flags->c == 1 && flags->l != 1) {
    if (flags->h != 1 && flags->l != 1 && files_amount > 1)
      printf("%s:", files[i]);
    printf("%d\n", line_matches); 
  }
}