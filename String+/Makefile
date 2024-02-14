CC = gcc
FLAGS = -Wall -Werror -Wextra

SRC_DIR?=.
INC_DIR?=.
OBJ_DIR?=./obj

INC:=$(shell find $(INC_DIR) -name "s21_*.h")
SRC:=$(shell find $(SRC_DIR) -name "s21_*.c")
OBJ:=$(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

AR:= ar rc
RAN:= ranlib
RM:= rm -f

LIB = s21_string.a
COVER = gcov_report

all: $(LIB) sprintf sscanf

$(LIB): clean
	gcc -c -g s21_string.c
	ar -r libs21_string.a s21_string.o

sprintf:
	gcc -c -g s21_sprintf.c
	gcc -L. -o s21_sprintf s21_sprintf.o -ls21_string -lm

sscanf:
	gcc -c -g s21_sscanf.c
	gcc -L. -o s21_sscanf s21_sscanf.o -ls21_string -lm

# $(OBJS): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC) 
# 	@$(MK) $(OBJ_DIR)
# 	$(CC) $(CFLAGS) -o $@ -c $<

rebuild:
	make all

clean:
	# $(RM) $(OBJS)
	# $(RM) $(GCDA)
	# $(RM) $(GCNO)
	# $(RM) $(TEST_OBJS)
	# $(RM) $(GCOV_OBJS)
	# $(RM) tests/objs/main.o
	$(RM) *.o
	$(RM) s21_sprintf
	$(RM) s21_sscanf

clang:
	clang-format -i --style=Google *.c *.h
	clang-format -n --style=Google *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h