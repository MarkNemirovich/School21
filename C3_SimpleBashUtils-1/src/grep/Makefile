CC = gcc -Wall -Werror -Wextra -fsanitize=address -std=c11
MAC_OS = uname -av | grep -e mac -e Mac -e MAC -e Darwin -e darwin -e DARWIN -o
EMPTY = ""
ifeq ($(MAC_OS),$(EMPTY))
    FLAG=
else   
    FLAG=-DMAC
endif   

all: s21_grep

s21_grep: s21_grep.c
	$(CC) $(FLAG) s21_grep.c -o s21_grep
	
rebuild:
	make clean
	make all

clean:
	rm -rf *.o s21_grep *.log

clang:
	clang-format -i --style=Google *.c *.h
	clang-format -n --style=Google *.c *.h 

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

leaks:
	leaks -atExit -- ./s21_grep leaks.txt

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./s21_grep leaks.txt