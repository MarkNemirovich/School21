CC = gcc
CFLAGS = -Wall -Werror -Wextra
C11 = -std=c11

CPP = cppcheck --enable=all --suppress=missingIncludeSystem

MAIN = main.c

BUILD_BRICKS = build

CFILES_BACK_LIB = $(shell find brick_game -name '*.c')
OBJS_BACK_LIB = $(CFILES_BACK_LIB:%.c=%.o)

CFILES_GUI_LIB = $(shell find gui -name '*.c')
OBJS_GUI_LIB = $(CFILES_GUI_LIB:%.c=%.o)

CFILES_TEST_LIB = $(shell find tests -name '*.c')
OBJS_TEST_LIB = $(CFILES_TEST_LIB:%.c=%.o)

CHECK_LIBS = -lcheck -lsubunit -lm -lncurses

all: s21_bricks

s21_bricks: s21_bricks.a gui_lib final
	find . \( -name "*.c" -o -name "*.h" \) -print0 | xargs -0 clang-format -i

$(OBJS_BACK_LIB): %.o: %.c
	$(CC) $(CFLAGS) $(C11) -c $< -o $@

$(OBJS_GUI_LIB): %.o: %.c
	$(CC) $(CFLAGS) $(C11) -c $< -o $@

$(OBJS_TEST_LIB): %.o: %.c
	$(CC) $(CFLAGS) $(C11) -c $< -o $@

s21_bricks.a: $(OBJS_BACK_LIB)

gui_lib: $(OBJS_GUI_LIB)

test_lib: $(OBJS_TEST_LIB)

final:
	$(CC) $(CFLAGS) $(C11) main.c $(OBJS_BACK_LIB) $(OBJS_GUI_LIB) -o s21_bricks $(CHECK_LIBS)
	rm -rf $(OBJS_GUI_LIB)
	rm -rf $(OBJS_BACK_LIB)

test: s21_bricks.a gui_lib test_lib
	$(CC) $(CFLAGS) $(C11) $(OBJS_BACK_LIB) $(OBJS_GUI_LIB) $(OBJS_TEST_LIB) -o s21_bricks_tests $(CHECK_LIBS) 
	rm -rf $(OBJS_GUI_LIB)
	rm -rf $(OBJS_BACK_LIB)
	rm -rf $(OBJS_TEST_LIB)

gcov_report:
	$(CC) --coverage $(CFLAGS) $(CFILES_BACK_LIB) $(CFILES_GUI_LIB) $(CFILES_TEST_LIB) -o test -lcheck -lsubunit -lm -lncurses
	./test
	lcov -t "test" -o test.info -c -d ./
	genhtml -o report test.info

cppcheck:
	$(CPP) $(CFILES)

clang:
	find . \( -name "*.c" -o -name "*.h" \) -print0 | xargs -0 clang-format -n

clean:
	rm -f s21_bricks $(OBJS_BACK_LIB) $(OBJS_GUI_LIB) $(OBJS_TEST_LIB) build/main.o $(MY_LIB)
	rm -rf *.gcda *.info *.gcno
	rm -rf *.out report/* test
	rm -rf s21_bricks_tests
	rm -rf deb_bricks debug_test
	rm -rf latex/ html/ BricksGame-1.tar.gz BricksGame-1/
	rm -rf Doxyfile refman.log texput.log

rebuild: clean s21_bricks