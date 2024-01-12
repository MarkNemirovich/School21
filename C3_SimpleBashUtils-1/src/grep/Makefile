CC = gcc -Wall -Werror -Wextra -std=c11 -D_GNU_SOURCE

all: s21_grep

s21_grep.o: s21_grep.c
	clang-format -i --style=Google *.c *.h
	$(CC) -c s21_grep.c -o s21_grep.o

s21_grep: s21_grep.o
	$(CC) *.o -o s21_grep

rebuild:
	make clean
	make all

clean:
	rm -rf *.o s21_grep

clang:
	clang-format -n --style=Google *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

leaks:
	leaks -atExit -- ./s21_grep leaks.txt

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./s21_grep leaks.txt