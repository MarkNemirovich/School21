CC = gcc -Wall -Wextra -Werror -fsanitize=address
BUILD = ../build/

all: build

build: *.c
	$(CC) $(CFLAGS) *.c -o $(BUILD)graph


format:
	clang-format -n *.c *.h

formating:
	clang-format -i *.c *.h

cppcheck:
	cppcheck —-enable=all —-suppress=missingIncludeSystem *.c *.h

clean:
	rm -f *.o *.out $(BUILD)graph

rebuild: clean all
