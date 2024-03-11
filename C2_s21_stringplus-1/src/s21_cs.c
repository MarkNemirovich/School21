#include "s21_string.h"

void *s21_insert(const char *src, const char *str, size_t index) {
  if (src == s21_NULL && str == s21_NULL) return s21_NULL;
  s21_size_t src_len = s21_strlen(src);
  if (str == s21_NULL) {
    char *return_str = malloc((src_len + 1) * sizeof(char));
    if (return_str) {
      return_str = s21_strncpy(return_str, src, src_len + 1);
    }
    return return_str;
  }
  s21_size_t str_len = s21_strlen(str);
  s21_size_t new_len = src_len + str_len + 1;
  if (index >= src_len) {
    index = src_len;
    new_len = src_len + 1;
  }
  char *new_str = malloc(new_len * sizeof(char));
  if (new_str) {
    if (new_str != s21_NULL && str != s21_NULL && new_len > 1) {
      s21_size_t i = 0, j = 0;
      for (; i < index; i++) {
        new_str[i] = src[i];
      }
      for (; j < str_len && i + j < new_len; j++) {
        new_str[i + j] = str[j];
      }
      for (; i + j < new_len - 1; i++) {
        new_str[i + j] = src[i];
      }
      new_str[i + j] = '\0';
    } else
      new_str = s21_strncpy(new_str, "\0", 1);
  }
  return new_str;
}

void *s21_to_upper(const char *str) {
  if (str == s21_NULL) return s21_NULL;
  char *str_copy = s21_NULL;

  s21_size_t len = s21_strlen(str);

  str_copy = (char *)malloc(sizeof(char) * (len + 1));

  if (str_copy) {
    for (s21_size_t i = 0; i <= len; i++) {
      if (str[i] >= 'a' && str[i] <= 'z') {
        str_copy[i] = (str[i] - 'a') + 'A';
      } else {
        str_copy[i] = str[i];
      }
    }
    str_copy[len] = '\0';
  }
  return str_copy;
}

void *s21_to_lower(const char *str) {
  if (str == s21_NULL) return s21_NULL;
  char *str_copy = s21_NULL;

  s21_size_t len = s21_strlen(str);

  str_copy = (char *)malloc(sizeof(char) * (len + 1));

  if (str_copy) {
    for (s21_size_t i = 0; i <= len; i++) {
      if (str[i] >= 'A' && str[i] <= 'Z') {
        str_copy[i] = (str[i] - 'A') + 'a';
      } else {
        str_copy[i] = str[i];
      }
    }
    str_copy[len] = '\0';
  }
  return str_copy;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == s21_NULL) return s21_NULL;

  char *res = s21_NULL;
  if (trim_chars && *trim_chars) {
    s21_size_t len = s21_strlen(src);
    s21_size_t chars_len = s21_strlen(trim_chars);

    s21_trim_left(&src, trim_chars, &len, chars_len);
    if (len) s21_trim_right(&src, trim_chars, &len, chars_len);

    res = (char *)malloc(sizeof(char) * (len + 1));

    if (res) {
      for (s21_size_t i = 0; i < len; i++) {
        res[i] = src[i];
      }
      *(res + len) = '\0';
    }
  } else {
    res = s21_trim(src, " \t\n");
  }
  return res;
}

void s21_trim_left(const char **src, const char *trim_chars,
                   s21_size_t *src_len, const s21_size_t trim_chars_len) {
  s21_size_t m = 0;

  while (src && m != trim_chars_len) {
    if ((**src) == trim_chars[m]) {
      (*src)++;
      (*src_len) -= 1;
      m = 0;
    } else
      m++;
  }
}

void s21_trim_right(const char **src, const char *trim_chars,
                    s21_size_t *src_len, const s21_size_t trim_chars_len) {
  s21_size_t m = 0;
  s21_size_t i = (*src_len) - 1;

  while (src && m != trim_chars_len) {
    if ((*src)[i] == trim_chars[m]) {
      i--;
      (*src_len)--;
      m = 0;
    } else
      m++;
  }
}