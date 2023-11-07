CC = gcc -Wall -Wextra -Werror

FOLDER_L = ../data_libs
FOLDER_M = ../data_module
FOLDER_Y = ../yet_another_decision_module
BUILD = ../../build

STAT = $(FOLDER_L)/data_stat
IO = $(FOLDER_L)/data_io
PROCESS = $(FOLDER_M)/data_process
MODULE = $(FOLDER_M)/data_module_entry
DECISION = $(FOLDER_Y)/decision
YET = $(FOLDER_Y)/yet_another_decision_module_entry

#SRCS_LIBS = $(wildcard $(FOLDER_L)/*.c)
#SRCS_MODULE = $(wildcard $(FOLDER_M)/*.c)
#SRCS_YET_ANOTHER = $(wildcard $(FOLDER_Y)/decision.c)

#OBJS_LIBS = $(SRCS_LIBS:.c=.o)
#OBJS_MODULE = $(SRCS_MODULE:.c=.o)
#OBJS_YET_ANOTHER = $(SRCS_YET_ANOTHER:.c=.o)

TARGET = Quest_3
STATIC_TARGET = build_with_static
STAT_LIB = data_stat.a
DYN_LIB = data_process.so
DYNAMIC_TARGET = build_with_dynamic

.PHONY: all clean rebuild build_with_static

all: $(TARGET)


$(TARGET): $(IO).o $(STAT).o $(PROCESS).o $(MODULE).o $(DECISION).o
	$(CC) $(IO).o $(STAT).o $(PROCESS).o $(MODULE).o $(DECISION).o -o $(BUILD)/Quest_3

$(STATIC_TARGET): $(IO).o $(PROCESS).o $(MODULE).o $(DECISION).o $(STAT_LIB)
	$(CC) $(IO).o $(STAT).o $(PROCESS).o $(MODULE).o $(DECISION).o -o $(BUILD)/Quest_5 -L. -data_stat

$(DYNAMIC_TARGET): $(IO).o $(STAT).o $(MODULE).o $(DECISION).o $(DYN_LIB)
	$(CC) -DDYNAMIC $(IO).o $(STAT).o $(MODULE).o $(DECISION).o $(DYN_LIB) -o $(BUILD)/Quest_6 -L. -data_process -Wl,-rpath,.

$(STAT_LIB): $(STAT).o
	ar r $(STAT_LIB) $(STAT).o

$(DYN_LIB): $(PROCESS).c $(STAT).c
	$(CC) -fPIC -shared $(PROCESS).c $(STAT).c -o $(DYN_LIB)


$(IO).o: $(IO).c
	$(CC) -c $(IO).c -o $(IO).o

$(STAT).o: $(STAT).c
	$(CC) -c $(STAT).c -o $(STAT).o

$(PROCESS).o: $(PROCESS).c
	$(CC) -c $(PROCESS).c -o $(PROCESS).o

$(MODULE).o: $(MODULE).c
	$(CC) -c $(MODULE).c -o $(MODULE).o

$(DECISION).o: $(DECISION).c
	$(CC) -c $(DECISION).c -o $(DECISION).o

$(YET).o: $(YET).c
	$(CC) -c $(YET).c -o $(YET).o

format:
	clang-format -n $(FOLDER_L)/*.c $(FOLDER_M)/*.c $(FOLDER_Y)/*.c $(FOLDER_L)/*.h $(FOLDER_M)/*.h $(FOLDER_Y)/*.h *.c *.h

formating:
	clang-format -i $(FOLDER_L)/*.c $(FOLDER_M)/*.c $(FOLDER_Y)/*.c $(FOLDER_L)/*.h $(FOLDER_M)/*.h $(FOLDER_Y)/*.h *.c *.h

cppcheck:
	cppcheck —enable=all —suppress=missingIncludeSystem $(FOLDER_L)/*.c $(FOLDER_M)/*.c $(FOLDER_Y)/*.c $(FOLDER_L)/*.h $(FOLDER_M)/*.h $(FOLDER_Y)/*.h *.c *.h

clean:
	rm -f $(STAT_LIB) $(DYN_LIB) $(BUILD)/Quest_3 $(BUILD)/Quest_5 $(BUILD)/Quest_6 \
	$(IO).o $(STAT).o $(PROCESS).o $(MODULE).o $(DECISION).o $(YET).o


rebuild: clean all
