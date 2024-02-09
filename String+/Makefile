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

all: $(LIB)

$(LIB): clean
	$(AR) $(LIB) $(OBJS)
	$(RAN) $(LIB)

$(OBJS): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC) 
	@$(MK) $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

rebuild:
	make all

clean:
	$(RM) $(OBJS)
	$(RM) $(GCDA)
	$(RM) $(GCNO)
	$(RM) $(TEST_OBJS)
	$(RM) $(GCOV_OBJS)
	$(RM) tests/objs/main.o

clang:
	clang-format -i --style=Google *.c *.h
	clang-format -n --style=Google *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h