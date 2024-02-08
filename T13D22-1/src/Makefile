CC = gcc -Wall -Wextra -Werror -fsanitize=address
BUILD = ../build

CIPHER = cipher.c

Q1 = cipher

.PHONY: all clean rebuild

all: build

build: $(Q1)

$(Q1): $(CIPHER)
	$(CC) $(CIPHER) -o $(BUILD)/$(Q1)

git:
	git add --all
	git commit -m 'update by makefile'
	git push origin develop

format:
	clang-format -n *.c *.h */*.c */*.h

formating:
	clang-format -i *.c *.h */*.c */*.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

clean:
	rm -f *.o *.out $(BUILD)/$(Q1)

rebuild: clean all
