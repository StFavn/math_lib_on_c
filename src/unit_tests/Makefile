CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose
LIBS=-lcheck

OS=$(shell uname -s)
OS_NAME=$(OS)

ifeq ($(OS), Linux)
  OPEN_CMD = xdg-open
  LIBS += -lm
  OS_NAME=$(shell grep -o 'Ubuntu' /etc/os-release | head -n 1)
endif
ifeq ($(OS_NAME), Ubuntu)
  LIBS += -lsubunit -lrt -lpthread
endif
ifeq ($(OS), Darwin)
  OPEN_CMD = open
endif

BUILD_DIR=build
GCOV_REP_DIR=$(BUILD_DIR)/report

ifeq ($(wildcard $(BUILD_DIR)), )
  $(shell mkdir $(BUILD_DIR))
endif

SRC=$(wildcard *.c)
OBJ=$(addprefix $(BUILD_DIR)/,$(SRC:%.c=%.o))

TARGET_NAME=s21_math_test
TARGET=s21_math_test.exe

S21_MATH_LIB=../s21_math.a

.PHONY: all rebuild gcov gcov_flags debug debug_flags
.DELETE_ON_ERROR:

all: $(TARGET)

gcov: clean_obj debug_flags gcov_flags gcov_$(TARGET)

gcov_flags:
	$(eval CFLAGS += $(GCOV_FLAGS))

rebuild: clean all

debug: clean debug_flags $(TARGET)

debug_flags:
	$(eval CFLAGS += -g)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(S21_MATH_LIB) -o $@ $(LIBS)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

gcov_$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(S21_MATH_LIB) -o $(BUILD_DIR)/$@ $(LIBS)
	$(BUILD_DIR)/$@
	lcov -t "stest" -o $(BUILD_DIR)/$(TARGET_NAME).info -c -d ./$(BUILD_DIR)/ -d ../$(BUILD_DIR)/
	genhtml -o $(GCOV_REP_DIR) $(BUILD_DIR)/$(TARGET_NAME).info
	nohup $(OPEN_CMD) ./$(BUILD_DIR)/report/index.html >/dev/null 2>&1 &

valgrind_check:
	$(shell valgrind $(VALGRIND_FLAGS) --log-file=$(BUILD_DIR)/RESULT_VALGRIND.txt ./$(TARGET))

.PHONY: clean clean_obj clean_gcov

clean_obj:
	cd $(BUILD_DIR) && rm -rf *.o *.a *.exe *.so
	rm -rf *.o *.a *.exe *.so

clean_gcov:
	rm -rf *.out
	cd $(BUILD_DIR) && rm -rf *.gcda *.gcno *.info
	cd $(BUILD_DIR) && rm -rf report

clean: clean_obj clean_gcov
	cd $(BUILD_DIR) && rm -rf *.txt