LIB_DIR := ./src
TEST_DIR := ./tests

CC := gcc
STD := c99
CFLAGS := -g -std=$(STD) -O -Werror -Wall -Wextra -pedantic -Wno-error=format
# add more from https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
CMOCKA := -lcmocka

LIB_SRC := $(wildcard $(LIB_DIR)/*.c)
LIB_OBJ := $(LIB_SRC:.c=.o)

TEST_SRC := $(wildcard $(TEST_DIR)/*Test.c)
TEST_EXE := $(TEST_SRC:.c=.exe)

$(LIB_DIR)/%.o: $(LIB_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@
.SECONDARY: $(LIB_OBJ)
# https://stackoverflow.com/questions/15189704/makefile-removes-object-files-for-no-reason

$(TEST_DIR)/%.exe: $(TEST_DIR)/%.c ${LIB_OBJ}
	$(CC) $(CFLAGS) ${LIB_OBJ} $< $(CMOCKA) -o $@

.PHONY: test
test: ${TEST_EXE}
#	$(info $$var is [${TEST_EXE}])
	for exe in ${TEST_EXE}; do $$exe || exit; done

.PHONY: clean
clean:
	rm -f $(LIB_DIR)/*.o
	rm -f $(TEST_DIR)/*.o $(TEST_DIR)/*.exe $(TEST_DIR)/*.received.*
	rm -f example/*.o example/*.exe example/*.received.*
