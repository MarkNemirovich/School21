#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  // static allow us to remember part of string we cutted last time
  static char *last;
  int length = 0;
  int end_line = -1;
  int start_last = -1;
  char *ref = str;
  if (ref == s21_NULL)  // check is it a new string
    ref = last;
  if (ref != s21_NULL)  // check is there anything left in the previous string
    for (int i = 0; ref[i] != '\0' && ref[i] != '\n'; i++) {  // get length
      length++;
    }
  // go till the end of string or meet the delimiter (group them)
  for (int i = 0; i < length && start_last == -1; i++) {
    int match = 0;
    for (int j = 0; delim[j] != '\0' && !match; j++) {
      if (ref[i] == delim[j]) {  // is string symbol presents in the delimiter
        match = 1;
      }
    }
    if (match && end_line == -1) {  // if we met 1st dilimeter
      end_line = i;
    }
    if (end_line != -1 && !match && start_last == -1) {  // last one
      start_last = i;
    }
  }
  if (length > 0) {
    str = ref;
    str[end_line] = '\0';     // cut left part till first delimiter (in group)
    last = ref + start_last;  // left right part from last delimiter for future
  }
  if (end_line == length - 1) {  // if string is over
    last = s21_NULL;
  }
  return str;
}