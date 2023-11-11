CC = gcc -Wall -Wextra -Werror -fsanitize=address
BUILD = ../build

PRINT = print_module
DOCUMENTATION = documentation_module
MAIN_MODULE = main_module_entry_point
BST = bst.c
BST_CREATE = bst_create_test.c
BST_INSERT = bst_insert_test.c
BST_TRAVERSE = bst_traverse_test.c


Q1 = print_module
Q2 = documentation_module
Q3 = bst_create_test
Q4 = bst_insert_test
Q5 = bst_traverse_test


.PHONY: all clean rebuild

all: build

build: $(Q1) $(Q2) $(Q3) $(Q4) $(Q5)

$(Q1): $(PRINT).c $(MAIN_MODULE).c
	$(CC) -DQ1 $(PRINT).c $(MAIN_MODULE).c -o $(BUILD)/Quest_1

$(Q2): $(DOCUMENTATION).c $(PRINT).c $(MAIN_MODULE).c
	$(CC) -DQ2 $(DOCUMENTATION).c $(PRINT).c $(MAIN_MODULE).c -o $(BUILD)/Quest_2

$(Q3): $(BST) $(BST_CREATE)
	$(CC) -DCREATE $(BST) $(BST_CREATE) -o $(BUILD)/Quest_3

$(Q4): $(BST) $(BST_INSERT)
	$(CC) -DINSERT $(BST).c $(BST_INSERT).c -o $(BUILD)/Quest_4

$(Q5): $(BST) $(BST_TRAVERSE)
	$(CC) -DTRAVERSE $(BST) $(BST_TRAVERSE) -o $(BUILD)/Quest_5

format:
	clang-format -n *.c *.h

formating:
	clang-format -i *.c *.h

cppcheck:
	cppcheck —-enable=all —-suppress=missingIncludeSystem *.c *.h

clean:
	rm -f *.o *.out $(BUILD)/Quest*

rebuild: clean all
