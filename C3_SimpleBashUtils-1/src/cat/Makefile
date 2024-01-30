CC = gcc -Wall -Werror -Wextra -fsanitize=address -std=c11
MAC =
all: s21_cat

s21_cat: s21_cat.c
	$(CC) $(MAC) s21_cat.c -o s21_cat

rebuild:
	make clean
	make all

clean:
	rm -rf *.o s21_cat *.log

clang:
	clang-format -i --style=Google *.c *.h
	clang-format -n --style=Google *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

leaks:
	leaks -atExit -- ./s21_cat leaks.txt

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./s21_cat leaks.txt