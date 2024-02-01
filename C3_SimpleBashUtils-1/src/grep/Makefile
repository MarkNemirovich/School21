CC = gcc 
FLAGS = -Wall -Werror -Wextra -fsanitize=address -std=c11

all: s21_grep
	
mac: clean
	$(CC) $(FLAGS) -DMAC s21_grep.c -o s21_grep

s21_grep: clean
	$(CC) $(FLAGS) s21_grep.c -o s21_grep

rebuild:
	make all

rebuild_mac:
	make mac

clean:
	rm -rf *.o s21_grep *.log

clang:
	clang-format -i --style=Google *.c *.h
	clang-format -n --style=Google *.c *.h 

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./s21_grep leaks.txt

test:
	bash test_func_grep.sh

test_long:
	bash test_grep.sh

leaks:
	leaks --atExit -- ./s21_grep -f leaks.txt test_0_grep.txt test_1_grep.txt test_2_grep.txt