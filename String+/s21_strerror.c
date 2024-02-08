#include "s21_strerror.h"

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