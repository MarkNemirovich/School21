CC = gcc 
FLAGS = -Wall -Werror -Wextra -fsanitize=address -std=c11
all: s21_cat

mac: clean
	$(CC) $(FLAGS) -DMAC s21_cat.c -o s21_cat

s21_cat: clean
	$(CC) $(FLAGS) s21_cat.c -o s21_cat

rebuild:
	make all

rebuild_mac:
	make mac

clean:
	rm -rf *.o s21_cat *.log

clang:
	clang-format -i --style=Google *.c *.h
	clang-format -n --style=Google *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./s21_cat leaks.txt

test:
	bash test_func_cat.sh

leaks:
	bash test_leak_cat.sh
	