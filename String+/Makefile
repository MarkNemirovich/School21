CC = gcc
FLAGS = -Wall -Werror -Wextra

all: s21_string.a

s21_string.a: clean
	gcc -c -g s21_string.c s21_common.c s21_sprintf.c
	ar -r libs21_string.a s21_string.o s21_common.o

# test:
	# gcc -c -g unit_tests
	# gcc -L. -o unit_tests -ls21_string -lm

# gcov_report:

rebuild:
	make all

clean:
	rm -f *.o *.a

clang:
	clang-format -i --style=Google *.c *.h
	clang-format -n --style=Google *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h