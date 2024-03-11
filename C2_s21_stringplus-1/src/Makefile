CC = gcc
CHECK_INCLUDE_PATH = $(shell brew --prefix check)/include
FLAGS = -Wall -Werror -Wextra -I$(CHECK_INCLUDE_PATH)


SOURCES=s21_*.c
LIBA=s21_string.a
LIBO=*.o
BUILD_PATH=./
EXE=$(BUILD_PATH)test.out
GCOV_LIBS=-fprofile-arcs -ftest-coverage 
GCOV_FOLDER=report/

OS:=$(shell uname -s)

ifeq ($(OS),Linux)
	CC+=-D LINUX_OS
	TST_LIBS=-lcheck -lsubunit -lm -lpthread
else ifeq ($(OS),Darwin)
	CC+=-D MAC_OS
	TST_LIBS=-lcheck -lpthread
else
	CC+=-D DEFAULT_OS
endif


all: s21_string.a test gcov_report

s21_string.a: clean
	$(CC) -c $(SOURCES)
	ar rcs $(LIBA) $(LIBO)
	ranlib $(LIBA)

test: unittests s21_string.a
	$(CC) $(FLAGS) unittests.c -L. $(LIBA) $(TST_LIBS) -ggdb3 -o $(EXE)
	$(EXE)

gcov_report: unittests test
	$(CC) $(GCOV_LIBS) test.c $(SOURCES) $(LIBA) -L. $(LIBA) $(TST_LIBS) -o $(EXE) -I$(CHECK_INCLUDE_PATH)
	$(EXE)
	lcov -t "test" -c -d $(BUILD_PATH) --output-file $(BUILD_PATH)coverage.info
	genhtml $(BUILD_PATH)coverage.info --output-directory $(BUILD_PATH)$(GCOV_FOLDER)
	open report/index.html
	
rebuild: clean all


check:
	@echo
	@echo ===CPPCHECK===
	@echo
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	@echo
	@echo ===STYLE TEST===
	@echo
	clang-format -n --style=Google *.c *.h
	@echo
	@echo ===VALGRIND TEST===
	@echo
	valgrind --leak-check=full --log-file=valgrind.txt $(EXE)

clean:
	rm -rf *.a *.o *.txt
	rm -rf *.info *.gcda *.gcno *.gcov
	rm -rf $(GCOV_FOLDER) *.out

clang:
	clang-format -i --style=Google *.c *.h

include check.mk