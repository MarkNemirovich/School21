CC = gcc
FLAGS = -Wall -Werror -Wextra

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

fsanitize:
	$(CC) $(FLAGS) -fsanitize=address -std=c11 s21_grep.c -o s21_grep

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./s21_grep ../tests/leaks.txt

test:
	bash ../tests/test_func_grep.sh

test_long:
	bash ../tests/test_grep.sh

leaks:
	leaks --atExit -- ./s21_grep -f ../tests/leaks.txt ../tests/test_0_grep.txt ../tests/test_1_grep.txt ../tests/test_2_grep.txt