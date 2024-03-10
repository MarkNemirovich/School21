#include "s21_string.h"

void *s21_insert(const char *src, const char *str, size_t start_index) {
  if (src == s21_NULL && str == s21_NULL) return s21_NULL;
  s21_size_t src_len = s21_strlen(src);
  if (str == s21_NULL) return s21_strncpy(malloc(src_len), src, src_len);
  s21_size_t str_len = s21_strlen(str);
  s21_size_t new_len = src_len + str_len + 1;
  s21_size_t i, j;
  if (start_index >= src_len) {
    start_index = src_len;
    new_len = src_len;
  }
  char *new_str = malloc(new_len * sizeof(char));
  new_str = s21_strncpy(new_str, "", 1);
  if (new_str != s21_NULL && str != s21_NULL && new_len > 1) {
    for (i = 0; i < start_index; i++) {
      new_str[i] = src[i];
    }
    for (j = 0; j < str_len && i + j < new_len; j++) {
      new_str[i + j] = str[j];
    }
    for (; i + j < new_len; i++) {
      new_str[i + j] = src[i];
    }
    new_str[i + j] = '\0';
  }
  return new_str;
}

void *s21_to_upper(const char *str) {
  char *str_copy = s21_NULL;

  if (str != s21_NULL) {
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
  }
  return str_copy;
}

void *s21_to_lower(const char *str) {
  char *str_copy = s21_NULL;

  if (str != s21_NULL) {
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
  }
  return str_copy;
}


void *s21_trim(const char *src, const char *trim_chars) {
    char *res = s21_NULL;

    if (src) {
        if (trim_chars && *trim_chars) {
            s21_size_t len = s21_strlen(src);
            s21_size_t chars_len = s21_strlen(trim_chars);

            s21_trim_left(&src, trim_chars, &len, chars_len);
            if (len)
                s21_trim_right(&src, trim_chars, &len, chars_len);

            res = (char *)malloc(sizeof(char) * (len + 1));

            if (res) {
                for (s21_size_t i = 0; i < len + 1; i++) {
                    if (i < len) {
                        res[i] = src[i];
                    } else {
                        res[i] = '\0';
                    }
                }
            }
        } else {
            res = s21_trim(src, " \t\n");
        }
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
            continue;
        }
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
            continue;
        }

        m++;
    }
}