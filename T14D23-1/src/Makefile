CC = gcc -Wall -Wextra -Werror -fsanitize=address
BUILD = ../build

SORT = state_sort.c

Q1 = state_sort
NAME1 = Quest_1

.PHONY: all clean rebuild

all: build

build: $(Q1)

$(Q1): $(SORT)
	$(CC) $(SORT) -o $(BUILD)/$(NAME1)

git:
	git add --all
	git commit -m 'update by makefile'
	git push origin develop

format:
	clang-format -n *.c *.h

formating:
	clang-format -i *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

clean:
	rm -f *.o *.out $(BUILD)/$(NAME1)

rebuild: clean all
