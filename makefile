SRC_DIR := ./src
TEST_DIR := ./tests
LIB_DIR := ./lib
EXAMPLE_DIR := ./example

CC := gcc
STD := c99
CFLAGS := -g -std=$(STD) -O -Werror -Wall -Wextra -pedantic -Wno-error=format
# add more from https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
SHARED_FLAGS := -shared
CMOCKA := -lcmocka
APPROVALS := -lapprovals

ifeq ($(OS),Windows_NT)
    detected_OS := Windows
	EXE := .exe
	DLL := ./bin/approvals.dll
    # https://stackoverflow.com/questions/17601949/building-a-shared-library-using-gcc-on-linux-and-mingw-on-windows
	SHARED_FLAGS += -Wl,--out-implib,${LIB_DIR}/libapprovals.a
else
    detected_OS := $(shell uname)
	EXE := .
	DLL := ${LIB_DIR}/libapprovals.so
	CFLAGS += -fPIC
endif

SRC_SRC := $(wildcard $(SRC_DIR)/*.c)
SRC_OBJ := $(SRC_SRC:.c=.o)

TEST_SRC := $(wildcard $(TEST_DIR)/*Test.c)
TEST_EXE := $(TEST_SRC:.c=$(EXE))

EXAMPLE_SRC := $(wildcard $(EXAMPLE_DIR)/*Test.c)
EXAMPLE_EXE := $(EXAMPLE_SRC:.c=$(EXE))

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@
.SECONDARY: $(SRC_OBJ)
# https://stackoverflow.com/questions/15189704/makefile-removes-object-files-for-no-reason

$(TEST_DIR)/%$(EXE): $(TEST_DIR)/%.c ${SRC_OBJ}
	$(CC) $(CFLAGS) ${SRC_OBJ} $< $(CMOCKA) -o $@

.PHONY: test
test: ${TEST_EXE}
	for exe in ${TEST_EXE}; do $$exe || exit; done

${DLL}: ${SRC_OBJ}
	$(CC) $(CFLAGS) $(SHARED_FLAGS) $^ -o ${DLL}

build: clean_all ${DLL}

.PHONY: clean
clean:
	rm -f $(SRC_DIR)/*.o
	rm -f $(TEST_DIR)/*.o $(TEST_DIR)/*$(EXE) $(TEST_DIR)/*.received.*
	rm -f ${EXAMPLE_DIR}/*.o ${EXAMPLE_DIR}/*$(EXE) ${EXAMPLE_DIR}/*.received.*
	rm -r -f Default

.PHONY: clean_all
clean_all: clean
	rm -f ${DLL}
	rm -f $(LIB_DIR)/*.a

$(EXAMPLE_DIR)/%$(EXE): $(EXAMPLE_DIR)/%.c ${DLL}
	$(CC) $(CFLAGS) $< $(CMOCKA) $(APPROVALS) -o $@

.PHONY: example
example: ${EXAMPLE_EXE}
	for exe in ${EXAMPLE_EXE}; do $$exe || exit; done
