CC = gcc
CHECK_INCLUDE_PATH = $(shell brew --prefix check)/include
FLAGS = -Wall -Werror -Wextra -I$(CHECK_INCLUDE_PATH)

SOURCES=s21_*.c
LIBA=s21_decimal.a
LIBO=*.o
BUILD_PATH=build/
EXE=./$(BUILD_PATH)unittests.out
GCOV_LIBS=-fprofile-arcs -ftest-coverage 
GCOV_FOLDER=report/
UNITTEST=unittests

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


all: s21_decimal.a test gcov_report

s21_decimal.a: clean
	$(CC) -c $(SOURCES)
	ar rcs $(LIBA) $(LIBO)
	ranlib $(LIBA)
	@rm -rf *.o

test: s21_decimal.a $(UNITTEST)
	mkdir build
	$(CC) $(FLAGS) $(UNITTEST).c -L. $(LIBA) $(TST_LIBS) -ggdb3 -o $(EXE)
	$(EXE)

gcov_report: test
	$(CC) $(GCOV_LIBS) $(UNITTEST).c $(SOURCES) $(LIBA) -L. $(LIBA) $(TST_LIBS) -o $(EXE) -I$(CHECK_INCLUDE_PATH)
	$(EXE)
	lcov -t "test" -c -d $(BUILD_PATH) --output-file $(BUILD_PATH)coverage.info
	genhtml $(BUILD_PATH)coverage.info --output-directory $(GCOV_FOLDER)
	open $(GCOV_FOLDER)index.html

clean:
	rm -rf *.a *.o *.txt $(UNITTEST).c
	rm -rf *.info *.gcda *.gcno *.gcov
	rm -rf $(GCOV_FOLDER)
	rm -rf $(BUILD_PATH)

clang:	
	clang-format -i --style=Google *.c *.h .*/*.c .*/*.h

rebuild: clean all

check:
	@echo
	@echo ===CPPCHECK===
	@echo
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	@echo
	@echo ===STYLE TEST===
	@echo
	clang-format -n --style=Google *.c *.h .*/*.c .*/*.h
	@echo
	@echo ===VALGRIND TEST===
	@echo
	valgrind --leak-check=full --log-file=valgrind.txt $(EXE)

include check.mk