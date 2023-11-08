CC = gcc -Wall -Wextra -Werror -fsanitize=address
BUILD = ../build

S_TEST = s21_string_test
S_LIB = s21_string

LEN = strlen_tests
CMP = strcmp_tests
CPY = strcpy_tests
CAT = strcat_tests
CHR = strchr_tests
STR = strstr_tests
TOK = strtok_tests

.PHONY: all clean rebuild

all: $(LEN) $(CMP) $(CPY) $(CAT) $(CHR) $(STR) $(TOK)

$(LEN): $(S_TEST).c $(S_LIB).c
	$(CC) -DLEN $(S_TEST).c $(S_LIB).c -o $(BUILD)/Quest_1
$(CMP): $(S_TEST).c $(S_LIB).c
	$(CC) -DCMP $(S_TEST).c $(S_LIB).c -o $(BUILD)/Quest_2
$(CPY): $(S_TEST).c $(S_LIB).c
	$(CC) -DCPY $(S_TEST).c $(S_LIB).c -o $(BUILD)/Quest_3
$(CAT): $(S_TEST).c $(S_LIB).c
	$(CC) -DCAT $(S_TEST).c $(S_LIB).c -o $(BUILD)/Quest_4
$(CHR): $(S_TEST).c $(S_LIB).c
	$(CC) -DCHR $(S_TEST).c $(S_LIB).c -o $(BUILD)/Quest_5
$(STR): $(S_TEST).c $(S_LIB).c
	$(CC) -DSTR $(S_TEST).c $(S_LIB).c -o $(BUILD)/Quest_6
$(TOK): $(S_TEST).c $(S_LIB).c
	$(CC) -DTOK $(S_TEST).c $(S_LIB).c -o $(BUILD)/Quest_7

format:
	clang-format -n *.c *.h

formating:
	clang-format -i *.c *.h

cppcheck:
	cppcheck —enable=all —suppress=missingIncludeSystem *.c *.h

clean:
	rm -f *.o *.out $(BUILD)/Quest*

rebuild: clean all
