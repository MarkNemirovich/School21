#include <stdio.h>
#include <limits.h>
#include <stdarg.h>
#include "s21_string.h"
#include <string.h>

#define s21_NULL ((void *)0)
#define S21_TEXTMAX 2048

typedef long unsigned s21_size_t;

typedef struct specificator {
    int minus, plus, space;
} specificator;

s21_size_t
get_num (char **format)
{
  s21_size_t num = 0;
  int power = 1;
  for (; **format >= '0' && **format <= '9'; (*format)++)
	{
	  num *= power;
	  num += ((**format) - '0');
	  power *= 10;
	}
  return num;
}

void
modificate_specificator (char **format, specificator *specificators, s21_size_t * padding,
						 int *accuracy)
{
  if (**format == '-')
	{
	  specificators->minus = 1;
	  (*format)++;
	}
    else if (**format == '+') {
	  specificators->plus = 1;
	  (*format)++;
      } 
    else if (**format == ' ') {
	  specificators->space = 1;
	  (*format)++;
      }
  if (**format >= '0' && **format <= '9')
	{
	  *padding = get_num (format);
	}
  if (**format == '.')
	{
	  (*format)++;
	  *accuracy = get_num (format);
	}
}

void
add_spaces (char *str, int *i, s21_size_t padding)
{
  while (padding > 0)
	{
	  str[*i] = ' ';
	  (*i)++;
	  padding--;
	}
}

void
print_number (char *str, int *i, int number, int length, int accuracy,
			  int power, specificator specificators)
{
  if (number < 0)
	{
	  str[*i] = '-';
	  (*i)++;
	  number *= -1;
	}
	else if (specificators.plus)
	{
	  str[*i] = '+';
	  (*i)++;
	}
	else if (specificators.space)
	{
	  str[*i] = ' ';
	  (*i)++;
	}
  while (accuracy > length)
	{
	  str[*i] = '0';
	  (*i)++;
	  accuracy--;
	}
  int rest = number;
  for (; power > 1; power /= 10)
	{
	  str[*i] = rest / (power / 10) + '0';
	  (*i)++;
	  rest = number % (power / 10);
	}
}

int
c_specific (char *str, int *i, char symbol, specificator specificators,
			s21_size_t padding)
{
  if (specificators.minus)
	{
	  str[*i] = symbol;
	  (*i)++;
	  add_spaces (str, i, padding - 1);
	}
  else
	{
	  add_spaces (str, i, padding - 1);
	  str[*i] = symbol;
	  (*i)++;
	}
  return padding - specificators.minus - 1;
}


int
d_specific (char *str, int *i, int number, specificator specificators, s21_size_t padding,
			int accuracy)
{
  int length = 0, power = 1;
  for (int n = number; n / power != 0; length++)
	{
	  power *= 10;
	}
  if (number == 0)
	{
	  length = 1;
	}
  if (specificators.minus)
	{
	  print_number (str, i, number, length, accuracy, power, specificators);
	  if (length > accuracy)
		add_spaces (str, i, padding - length - specificators.plus - specificators.space);
	  else
		add_spaces (str, i, padding - accuracy - specificators.plus - specificators.space);
	}
  else
	{
	  if (length > accuracy)
		add_spaces (str, i, padding - length - specificators.plus - specificators.space);
	  else
		add_spaces (str, i, padding - accuracy - specificators.plus - specificators.space);
	  print_number (str, i, number, length, accuracy, power, specificators);
	}
  if (accuracy > length)
	length = accuracy;
  if (padding > length)
	length = accuracy;
  return length - specificators.minus;
}


int
f_specific (char *str, int *i, int number, specificator specificators, s21_size_t padding,
			int accuracy)
{
  int length = 0, power = 1;
  for (int n = number; n / power != 0; length++)
	{
	  power *= 10;
	}
  if (number == 0)
	{
	  length = 1;
	}
  if (specificators.minus)
	{
	  print_number (str, i, number, length, accuracy, power, specificators);
	  if (length > accuracy)
		add_spaces (str, i, padding - length);
	  else
		add_spaces (str, i, padding - accuracy);
	}
  else
	{
	  if (length > accuracy)
		add_spaces (str, i, padding - length);
	  else
		add_spaces (str, i, padding - accuracy);
	  print_number (str, i, number, length, accuracy, power, specificators);
	}
  if (accuracy > length)
	length = accuracy;
  if (padding > length)
	length = accuracy;
  return length - specificators.minus;
}

int
transform_specificator (char *str, int *i, va_list list, char **format,
						specificator specificators, s21_size_t padding, int accuracy)
{
  int length_change = 0;
  switch (**format)
	{
	case 'c':
	  length_change =
		c_specific (str, i, va_arg (list, int), specificators, padding);
	  (*format)++;
	  break;
	case 'd':
	  length_change =
		d_specific (str, i, va_arg (list, int), specificators, padding,
					accuracy);
	  (*format)++;
	  break;
	case 'f':
	  length_change =
		f_specific (str, i, va_arg (list, int), specificators, padding,
					accuracy);
	  (*format)++;
	  break;
	case 's':
	  break;
	case 'u':
	  break;
	default:
	  break;
	}
  return length_change;
}

int
s21_sprintf (char *str, const char *format, ...)
{
  va_list list;
  va_start (list, format);
  int size = (int)strlen(format); // (int)s21_strlen(format);
  int i = 0;
    specificator specificators = {0};
  while (*format != 0 && i < size)
	{
	  if (*format++ == '%')
		{
		  specificators = (specificator){0};
		  s21_size_t padding = 0;
		  int accuracy = 0;
		  modificate_specificator ((char **) &format, &specificators, &padding,
								   &accuracy);
		  size +=
			transform_specificator (str, &i, list, (char **) &format,
									specificators, padding, accuracy);
		}
	  else
		{
		  str[i++] = *(format - 1);
		  str[i] = '\0';
		}
	}
  va_end (list);
  return 0;
}

int
main ()
{
  char buffer[50];

  s21_sprintf (buffer, "sum of %5.3f and 20 is 30\n", 12);
  printf ("%s", buffer);
  
  sprintf(buffer, "sum of %5.3f and 20 is 30\n", 12.2);
  printf ("%s", buffer);
  return 0;
}