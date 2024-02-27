CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

SOURCES = $(wildcard s21_*.c)
OBJECTS = $(SOURCES:.c=.o)

s21_decimal.a: clean $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib s21_decimal.a
	@rm -rf *.o

test: clean
	gcc $(CFLAGS) $(SOURCES) tests/s21_test.c -lm -o test -lcheck -lsubunit -lgcov
	@./test

gcov_report: clean
	gcc $(CFLAGS) -fprofile-arcs -ftest-coverage $(SOURCES) tests/s21_test.c -lm -o test -lcheck -lsubunit -lgcov
	@mkdir -p gcov_report
	@./test
	gcovr -r . --html --html-details -o gcov_report/coverage.html
	@rm -rf $(OBJECTS) s21_decimal.a test *.gc* test_gcov/*.gc*

clean:
	@rm -rf *.o *.a *.gc* test gcov_report

all: s21_decimal.a

cpp:
	@cppcheck —enable=all —suppress=missingIncludeSystem functions/*.c

clang:
	@clang-format -n *.c *.h *./*.c *./*.h

valgrind: test
	@valgrind ./test