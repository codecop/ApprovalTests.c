SRC_DIR := ./src
TEST_DIR := ./tests
DLL_DIR := ./bin
LIB_DIR := ./lib

CC := gcc
STD := c99
CFLAGS := -g -std=$(STD) -O -Werror -Wall -Wextra -pedantic -Wno-error=format
# add more from https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
CMOCKA := -lcmocka

SRC_SRC := $(wildcard $(SRC_DIR)/*.c)
SRC_OBJ := $(SRC_SRC:.c=.o)

TEST_SRC := $(wildcard $(TEST_DIR)/*Test.c)
TEST_EXE := $(TEST_SRC:.c=.exe)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@
.SECONDARY: $(SRC_OBJ)
# https://stackoverflow.com/questions/15189704/makefile-removes-object-files-for-no-reason

$(TEST_DIR)/%.exe: $(TEST_DIR)/%.c ${SRC_OBJ}
	$(CC) $(CFLAGS) ${SRC_OBJ} $< $(CMOCKA) -o $@

.PHONY: test
test: ${TEST_EXE}
#	$(info $$var is [${TEST_EXE}])
	for exe in ${TEST_EXE}; do $$exe || exit; done

build: ${SRC_OBJ}
	rm -f $(DLL_DIR)/*.dll
	rm -f $(LIB_DIR)/*.a
	$(CC) $(CFLAGS) -shared $^ -o ${DLL_DIR}/approvals.dll -Wl,--out-implib,${LIB_DIR}/libapprovals.a

.PHONY: clean
clean:
	rm -f $(SRC_DIR)/*.o
	rm -f $(TEST_DIR)/*.o $(TEST_DIR)/*.exe $(TEST_DIR)/*.received.*
	rm -f example/*.o example/*.exe example/*.received.*
