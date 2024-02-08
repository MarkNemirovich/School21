CC = gcc -Wall -Wextra -Werror -fsanitize=address
BUILD = ../build

C_LIST = list
C_LIST_TEST = list_test
C_STACK = stack
C_STACK_TEST = stack_test


DMANAGER = dmanager_module
LIST = list_test
STACK = stack_test

TARGET = door_struct

.PHONY: all clean rebuild

all: $(TARGET) $(LIST) $(STACK) 

$(TARGET): $(DMANAGER).c
	$(CC) $(DMANAGER).c -o $(BUILD)/Quest_1

$(LIST): $(C_LIST).c $(C_LIST_TEST).c 
	$(CC) -DDEBUG $(C_LIST).c $(C_LIST_TEST).c -o $(BUILD)/Quest_2

$(STACK): $(C_STACK).c $(C_STACK_TEST).c 
	$(CC) -DTESTING $(C_STACK).c $(C_STACK_TEST).c -o $(BUILD)/Quest_3

format:
	clang-format -n *.c *.h

formating:
	clang-format -i *.c *.h

cppcheck:
	cppcheck —enable=all —suppress=missingIncludeSystem *.c *.h

clean:
	rm -f *.o *.out $(BUILD)/Quest*

rebuild: clean all
