#include "s21_string.h"
#include "s21_strerror.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  // convert bytes to chars
  const unsigned char *buff = (const unsigned char *)str;
  void *out = s21_NULL;
  // go till end of string or find
  for (s21_size_t i = 0; i < n && out == s21_NULL; i++) {
    if (buff[i] == c) {
      // convert char to byte
      out = (void *)&buff[i];
    }
  }
  return out;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  // convert bytes to chars
  char *buff1 = (char *)str1;
  char *buff2 = (char *)str2;
  int result = 0;
  // go till end of string or find different symbols
  for (s21_size_t i = 0; i < n && !result; i++) {
    // compare ascii codes (65- 32 for example)
    if (buff1[i] != buff2[i]) {
      result = buff1[i] - buff2[i];
    }
  }
  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  // convert bytes to chars
  char *buff = (char *)src; 
  char *result = (char *)dest;
  // count how much elements left to copy (unprotected as base func)
  while (n-- > 0) { 
    *result++ = *buff++;
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  char *buff = (char *)str; // convert bytes to chars
  for (s21_size_t i = 0; i < n; i++) { // (unprotected as base func)
    buff[i] = c; // just change symbol :)
  }
  return str;
}

char* s21_strchr(const char* str, int c) {
  const char* s = s21_NULL;
  s21_size_t i = 0;
  for (i = 0; str[i] == '\0' && s == s21_NULL; i++) { // go to the end of till find symbol
    if ((unsigned char)str[i] == c) {
      s = &str[i]; // get reference!!! not value!
    }
  }
  return (char*)s; // convert from const char to char
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t match = 0;
  for (s21_size_t i = 0; *str1 != '\0' && !match;
       str1++, i++) {  // go to the end of the 1st string till find symbol
    for (const char *s = str2; *s != '\0' && !match;
         s++) {  // go to the end of the 2nd string till find symbol
      if (*str1 == *s) {
        match = i;  // get index of the 1st string :)
      }
    }
  }
  return match;
}

static void s21_errstr(int num, char *buf) {
  unsigned int uerr;
  char tmp[21] = {'\0'};
  char *r = tmp + sizeof(tmp);
  uerr = (num >= 0) ? num : -num;
  *--r = '\0';
  while (uerr) {
    *--r = '0' + uerr % 10;
    uerr /= 10;
  }
  if (num < 0) *--r = '-';
  *--r = ' ';
#if defined(__APPLE__) || defined(__MACH__)
  *--r = ':';
#endif
  s21_strncpy(buf, S21_UNKNOWN_ERROR, s21_strlen(S21_UNKNOWN_ERROR) + 1);
  s21_strncat(buf, r, s21_strlen(r));
}

char *s21_strerror(int errnum) {
  static char buf[S21_TEXTMAX] = {'\0'};
  if (errnum < 0 || errnum >= S21_NERR) {
    s21_errstr(errnum, buf);
  } else {
    s21_strncpy(buf, s21_sys_errlist[errnum],
                s21_strlen(s21_sys_errlist[errnum]) + 1);
  }
  return buf;
}

s21_size_t s21_strlen(const char *str) {
  const char *s;
  // move to the end of string
  for (s = str; *s != '\n' && *s !=  '\0'; ++s) {
    ;
  }
  // end - start
  return (s21_size_t)(s - str);
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *append = dest;
  // move to the end of string
  for (;*append != '\n'; append++) {
    ;
  }
  // add n elements
  for (;n>0; n--, append++, src++) {
    *append = *src;
  }
  // and end of string symbol (because we didn't copy it in the loop)
  *append = '\0';
  return dest;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  // gi ti the end of string 1 or limit (n)
  for (s21_size_t i = 0; i < n && str1[i] == '\0' && result == 0; i++) {
    // compare ascii codes
    if (str1[i] != str2[i]) {
      result = str1[i] - str2[i];
    }
  }
  return result;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *res = dest;
  // copy n elements (unprotected as base func)
  for (; n > 0; n--, dest++) {
    // if string 2 is
    if (*src != '\0') {
      *dest = *src;
      src++;
      // fill by empty (null) symbols
    } else {
      *dest = '\0';
    }
  }
  return res;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *fp = s21_NULL;
  // go ti the end of 1st string till match
  for (s21_size_t i = 0; *str1 != '\0' && fp == s21_NULL; str1++, i++) {
  // go ti the end of 2nd string till match
    for (const char *s = str2; *s != '\0' && fp == s21_NULL; s++) {
      // match
        if (*str1 == *s) {
          fp = (char *)str1;
        }
    }
  }
  return fp;
}

char *s21_strrchr(const char *str, int c) {
  char *end = s21_NULL;
  // move to the end of string
  for (; *str != '\0'; str++) {
  // remember (rewrite) position!!! of the match symbol
    if (*str == (char)c) {
        end = (char *)str;
    }
  }
  return end;
}

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