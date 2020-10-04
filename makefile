SRC_DIR := ./src
TEST_DIR := ./tests
DLL_DIR := ./bin
LIB_DIR := ./lib
EXAMPLE_DIR := ./example

CC := gcc
STD := c99
CFLAGS := -g -std=$(STD) -O -Werror -Wall -Wextra -pedantic -Wno-error=format
# add more from https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
CMOCKA := -lcmocka
APPROVALS := -lapprovals

SRC_SRC := $(wildcard $(SRC_DIR)/*.c)
SRC_OBJ := $(SRC_SRC:.c=.o)

TEST_SRC := $(wildcard $(TEST_DIR)/*Test.c)
TEST_EXE := $(TEST_SRC:.c=.exe)

EXAMPLE_SRC := $(wildcard $(EXAMPLE_DIR)/*Test.c)
EXAMPLE_EXE := $(EXAMPLE_SRC:.c=.exe)

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

${DLL_DIR}/approvals.dll: ${SRC_OBJ}
	$(CC) $(CFLAGS) -fPIC -shared $^ -o ${DLL_DIR}/approvals.dll -Wl,--out-implib,${LIB_DIR}/libapprovals.a

build: clean_all ${DLL_DIR}/approvals.dll

.PHONY: clean
clean:
	rm -f $(SRC_DIR)/*.o
	rm -f $(TEST_DIR)/*.o $(TEST_DIR)/*.exe $(TEST_DIR)/*.received.*
	rm -f ${EXAMPLE_DIR}/*.o ${EXAMPLE_DIR}/*.exe ${EXAMPLE_DIR}/*.received.*

.PHONY: clean_all
clean_all: clean
	rm -f $(DLL_DIR)/*.dll
	rm -f $(LIB_DIR)/*.a

$(EXAMPLE_DIR)/%.exe: $(EXAMPLE_DIR)/%.c ${DLL_DIR}/approvals.dll
	$(CC) $(CFLAGS) $< $(CMOCKA) $(APPROVALS) -o $@

.PHONY: example
example: ${EXAMPLE_EXE}
	for exe in ${EXAMPLE_EXE}; do $$exe || exit; done
