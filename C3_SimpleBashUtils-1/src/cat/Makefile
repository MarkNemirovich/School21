CC = gcc -Wall -Werror -Wextra -std=c11 #-D_GNU_SOURCE

all: s21_cat

cat.o: s21_cat.c
	clang-format -i --style=Google *.c *.h
	$(CC) -c s21_cat.c -o s21_cat.o

s21_cat: cat.o
	$(CC) *.o -o s21_cat

rebuild:
	make clean
	make all

clean:
	rm -rf *.o s21_cat

clang:
	clang-format -n --style=Google *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

leaks:
	leaks -atExit -- ./s21_cat leaks.txt

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./s21_cat leaks.txt