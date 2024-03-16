CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

BUILD_DIR=./build

ifeq ($(wildcard $(BUILD_DIR)/.), )
  $(shell mkdir $(BUILD_DIR))
endif

SRC=$(wildcard *.c)
OBJ=$(addprefix $(BUILD_DIR)/,$(SRC:%.c=%.o))
TARGET=s21_math.a

TEST_DIR=unit_tests
TEST_EXE=s21_math_test.exe

.PHONY: all rebuild clean debug debug_flags test test_debug clang
.DELETE_ON_ERROR:

all: $(TARGET)

rebuild: clean all

$(TARGET): $(OBJ)
	ar rcs $@ $(OBJ)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: clean debug_flags $(TARGET) test_debug

debug_flags:
	$(eval CFLAGS += -g)

test: $(TARGET)
	cd $(TEST_DIR) && make
	cd $(TEST_DIR) && ./$(TEST_EXE)

test_debug: debug
	cd $(TEST_DIR) && make debug

gcov_report: clean_obj debug_flags gcov_flags $(TARGET)
	cd $(TEST_DIR) && make gcov

gcov_flags:
	$(eval CFLAGS += $(GCOV_FLAGS))

valgrind_check: debug
	cd $(TEST_DIR) && make valgrind_check

clean_obj:
	cd $(BUILD_DIR) && rm -rf *.o *.a *.exe *.so
	rm -rf *.o *.a *.exe *.so

clean_gcov:
	cd $(BUILD_DIR) && rm -rf *.gcda *.gcno *.info *.out
	cd $(TEST_DIR) && make clean

clean: clean_obj clean_gcov

clang_check:
	cp ../materials/linters/.clang-format ./
	find . -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format -n {} \;
	rm .clang-format

clang:
	cp ../materials/linters/.clang-format ./
	find . -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format -i {} \;
	rm .clang-format
