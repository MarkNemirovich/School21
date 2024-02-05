#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *position = s21_NULL;
  // move to the end of 1st string
  for (; *haystack != '\0' && position == s21_NULL; haystack++) {
    // if match - start to look next symbols (and remember the start position)
    if (*haystack == *needle) {
      char *str = (char *)haystack;
      // move to the end of 2nd string
      for (; *needle != '\0' && *str == *needle; str++, needle++) {
        ;
      }
      // copy in a case if out by 1st codition in the loop above
      if (*needle == '\0') position = (char *)haystack;
    }
  }
  return position;
}