#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  // convert bytes to chars
  const unsigned char *buff = (const unsigned char *)str;
  void *out = s21_NULL;
  // go till end of string or find
  for (s21_size_t i = 0; i < n && out == s21_NULL; i++) {
    if (buff[i] == (unsigned char)c) {
      // convert char to byte
      out = (void *)&buff[i];
    }
  }
  return out;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  // convert bytes to chars
  const unsigned char *buff1 = (const unsigned char *)str1;
  const unsigned char *buff2 = (const unsigned char *)str2;
  int result = 0;
  // go till end of string or find different symbols
  for (s21_size_t i = 0; i < n && !result; i++) {
    // compare ascii codes (65- 32 for example)
    result = (int)buff1[i] - (int)buff2[i];
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
  char *buff = (char *)str;             // convert bytes to chars
  for (s21_size_t i = 0; i < n; i++) {  // (unprotected as base func)
    buff[i] = c;                        // just change symbol :)
  }
  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *append = dest;
  // move to the end of string
  for (; *append != '\0'; append++) {
    ;
  }
  // add n elements
  for (; n > 0; n--, append++, src++) {
    *append = *src;
  }
  // and end of string symbol (because we didn't copy it in the loop)
  *append = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  const char *s = s21_NULL;
  s21_size_t i = 0;
  for (i = 0; str[i] != '\0' && s == s21_NULL;
       i++) {  // go to the end of till find symbol
    if ((unsigned char)str[i] == c) {
      s = &str[i];  // get reference!!! not value!
    }
  }
  return (char *)s;  // convert from const char to char
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  s21_size_t i = 0;
  // go to the end of string 1 or limit (n)
  while (i < n && str1[i] != '\0' && str2[i] != '\0' && result == 0) {
    result = (unsigned char)str1[i] - (unsigned char)str2[i];
    i++;  // compare ascii codes
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

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t counter = 0;

  unsigned short match = 0;
  // go to the end of the 1st string till find symbol
  for (const char *a = str1; *a && !match; a++) {
    // go to the end of the 2nd string till find symbol
    for (const char *b = str2; *b && !match; b++) {
      if (*a == *b) {
        match = 1;  // get index of the 1st string :)
      }
    }
    if (!match) {
      counter++;
    }
  }
  return counter;
}

void s21_errstr(int num, char *buf) {
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
  for (s = str; *s != '\0'; s++) {
    ;
  }
  return (s21_size_t)(s - str);  // end - start
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
  s21_size_t length = s21_strlen(str);
  // move to the end of string
  do {
    // remember (rewrite) position!!! of the match symbol
    if (*str == (char)c) {
      end = (char *)str;
    }
    str++;
  } while (length-- > 0);
  return end;
}

char *s21_strstr(const char *haystack, const char *needle) {
  unsigned int i = 0;
  int flag = 1;
  // move to the end of 1st string
  for (i = 0; haystack[i] != '\0' && flag == 1; i++) {
    flag = 0;
    // move to the end of 2nd string
    for (unsigned int j = 0; needle[j] != '\0' && flag == 0; j++) {
      if ((haystack[i + j] == '\0') || (haystack[i + j] != needle[j])) {
        flag = 1;
      }
    }
  }
  if (haystack[0] == '\0' && needle[0] == '\0') {
    flag = 0;
  } else
    i--;
  return flag ? s21_NULL : (char *)&haystack[i];
}

char *s21_strtok(char *str, const char *delim) {
  static char *final;  // Статическая переменная хранит "остаток"
  int ch;
  int empty = 0;
  if (str == 0) {
    str = final;  // Если новая строка, устанавливаем "остаток" в её начало
  }
  do {
    if ((ch = *str++) == '\0') {  // Check is it end
      empty = 1;
    }
  } while (!empty && s21_strchr(delim, ch));  // skip delimeters
  if (!empty) {
    --str;                                  // start point
    final = str + s21_strcspn(str, delim);  // skip delimeters
    if (*final != 0) {                      // cut end
      *final++ = 0;
    }
  } else
    str = s21_NULL;
  return str;
}