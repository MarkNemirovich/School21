#include "s21_sprintf.h"

s21_size_t get_num(char **format) {
  s21_size_t num = 0;
  int power = 1;
  for (; **format >= '0' && **format <= '9';(*format)++) {
      num *= power;
      num += ((**format)-'0');
      power*=10;
  }
  return num;
}

void modificate_specificator(char **format, int *minus_flag, s21_size_t *padding, int *accuracy) {
    if (**format == '-') {
        *minus_flag = 1;
        (*format)++;
      }
      if (**format >= '0' && **format <= '9') {
        *padding = get_num(format);
      }
      if (**format == '.') {
        (*format)++;
        *accuracy = get_num(format);
      }
}

void add_spaces(char *str, int *i, s21_size_t padding) {
  while (padding > 0) {
    str[*i] = ' ';
    (*i)++;
    padding--;
  }
}

void print_number(char *str, int *i, int number, int length, int accuracy, int power) {
    while (accuracy > length) {
        str[*i] = '0';
        (*i)++;
        accuracy--;
    }
    if (number < 0) {
        str[*i] = '-';
        (*i)++;
        number *= -1;
    }
    int rest = number;
    for (; power > 1; power /= 10) {
                    printf("pow = %i, %i\t %i\n", rest, power, rest/(power/10));
        str[*i] = rest/(power/10) + '0';
        (*i)++;
        rest = number%(power/10);
    }
}

int c_specific(char *str, int *i, char symbol, int minus_flag, s21_size_t padding) {
                    if (minus_flag) {
                        str[*i] = symbol;
                        (*i)++;
                        add_spaces(str, i, padding-1);
                    }
                    else {
                        add_spaces(str, i, padding-1);
                        str[*i] = symbol;
                        (*i)++;
                    }
                    return padding - minus_flag - 1;
                }
                

int d_specific(char *str, int *i, int number, int minus_flag, s21_size_t padding, int accuracy) {
                    int length = 0, power = 1;
                    for (int n = number; n/power != 0; length++) {
                        power *= 10;
                    }
                    if (number == 0) {
                        length = 1;
                    }
                    if (number < 0) {
                        length++;
                    }
                    if (minus_flag) {
                        print_number(str, i, number, length, accuracy, power);
                        if (length > accuracy)
                            add_spaces(str, i, padding-length);
                        else 
                            add_spaces(str, i, padding-accuracy);
                    }
                    else {
                        if (length > accuracy)
                            add_spaces(str, i, padding-length);
                        else 
                            add_spaces(str, i, padding-accuracy);
                    printf("rest = %i\t \n", length);
                        print_number(str, i, number, length, accuracy, power);
                    printf("rest = %i\t \n", length);
                    }
                    printf("rest = %i\t \n", length);
                    if (accuracy > length) length = accuracy;
                    if (padding > length) length = accuracy;
                    printf("rest = %i\t \n", length);
                    return length - minus_flag;
                }
                

int transform_specificator(char *str, int *i, va_list list, char **format, int minus_flag, s21_size_t padding, int accuracy) {
    int length_change = 0;
    switch (**format) {
        case 'c':
          length_change = c_specific(str, i, va_arg(list, int), minus_flag, padding);
          (*format)++;
          break;
        case 'd':
          length_change = d_specific(str, i, va_arg(list, int), minus_flag, padding, accuracy);
          (*format)++;
          break;
        case 'f':
          break;
        case 's':
          break;
        case 'u':
            break;
        default: break;
      }
      return length_change;
}

int s21_sprintf(char* str, const char* format, ...) {
  va_list list;
  va_start(list, format);
  int size = (int)strlen(format);
  int i = 0;
  
  while (*format != 0 && i < size) {
    if (*format++ == '%') {
  int minus_flag = 0;
  s21_size_t padding = 0;
  int accuracy = 0;
        modificate_specificator((char**)&format, &minus_flag, &padding, &accuracy);
        size += transform_specificator(str, &i, list, (char**)&format, minus_flag, padding, accuracy);
    } else {
      str[i++] = *(format - 1);
      str[i] = '\0';
    }
  }
  va_end(list);
  return 0;
}

int main()
{
    char buffer[50];
    
    s21_sprintf(buffer, "sum of %5d and 20 is 30", -123);
 
    printf("%s", buffer);
    return 0;
}