CC = gcc -Wall -Werror -Wextra -std=c11
MAC_OS = uname -av | grep -e mac -e Mac -e MAC -e Darwin -e darwin -e DARWIN -o
EMPTY = ""
ifeq ($(MAC_OS),$(EMPTY))
    FLAG=
else   
    FLAG=-DMAC
endif   

all: s21_cat

cat.o: s21_cat.c
	$(CC) $(FLAG) -c s21_cat.c -o s21_cat

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