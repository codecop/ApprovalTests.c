# Variables which are not special to make or inherited from the environment should be in lowercase. Words should be separated with underscore symbol ‘_’

# folders
src_dir 	:= ./src
test_dir 	:= ./tests
lib_dir 	:= ./lib
example_dir := ./example
cov_dir 	:= ./gcov

# files

CC := gcc
STD := c99
CFLAGS := -g -std=$(STD) -Werror -Wall -Wextra -pedantic -Wno-error=format -Wno-error=unused-variable
# add more from https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
SHARED_FLAGS := -shared
CMOCKA := -lcmocka
APPROVALS := -lapprovals
COV := gcov

ifeq ($(OS),Windows_NT)
    detected_OS := Windows
	EXE := .exe
	DLL := ./bin/approvals.dll
    # https://stackoverflow.com/questions/17601949/building-a-shared-library-using-gcc-on-linux-and-mingw-on-windows
	SHARED_FLAGS += -Wl,--out-implib,${lib_dir}/libapprovals.a
else
    detected_OS := $(shell uname)
	EXE := .
	DLL := ${lib_dir}/libapprovals.so
	CFLAGS += -fPIC
endif

ifeq ($(GCOV),on)
	CFLAGS += --coverage
else
	CFLAGS += -O
endif

SRC_SRC := $(wildcard $(src_dir)/*.c)
SRC_OBJ := $(SRC_SRC:.c=.o)

SRC_COV := $(SRC_SRC:.c=.c.gcov)
COV_DAT := $(SRC_COV:$(src_dir)/%=$(cov_dir)/%)

TEST_SRC := $(wildcard $(test_dir)/*Test.c)
TEST_EXE := $(TEST_SRC:.c=$(EXE))

EXAMPLE_SRC := $(wildcard $(example_dir)/*Test.c)
EXAMPLE_EXE := $(EXAMPLE_SRC:.c=$(EXE))

$(src_dir)/%.o: $(src_dir)/%.c
	$(CC) -c $(CFLAGS) $< -o $@
# -c                       Compile and assemble, but do not link
# .SECONDARY: $(SRC_OBJ)
# https://stackoverflow.com/questions/15189704/makefile-removes-object-files-for-no-reason

$(test_dir)/%$(EXE): $(test_dir)/%.c ${SRC_OBJ}
	$(CC) $(CFLAGS) ${SRC_OBJ} $< $(CMOCKA) -o $@

# $< will represent the source file wherever it is

# Target names should use lower case letters. Words are separated with a hyphen

.PHONY: check
check: test

.PHONY: test
test: ${TEST_EXE}
	for exe in ${TEST_EXE}; do $$exe || exit; done
ifeq ($(GCOV),on)
    # no need for coverage on tests
	rm -f ./*Test.gcno ./*Test.gcda
endif

$(cov_dir)/%.c.gcov: $(src_dir)/%.c $(cov_dir)
	${COV} $<
	# https://gcc.gnu.org/onlinedocs/gcc/Invoking-Gcov.html#Invoking-Gcov
	mv *.c.gcov ${cov_dir}/

$(cov_dir):
	mkdir $(cov_dir)

coverage: test ${COV_DAT}
	rm -f $(src_dir)/*.gcno $(src_dir)/*.gcda

${DLL}: ${SRC_OBJ}
	$(CC) $(CFLAGS) $(SHARED_FLAGS) $^ -o ${DLL}

lib: build
# alias "to create the libraries"
build: very-clean ${DLL}

.PHONY: clean
clean:
	rm -f $(src_dir)/*.o
	rm -f $(test_dir)/*.o $(test_dir)/*$(EXE) $(test_dir)/*.received.*
	rm -f ${example_dir}/*.o ${example_dir}/*$(EXE) ${example_dir}/*.received.*
	rm -f $(src_dir)/*.gcno
	rm -f $(src_dir)/*.gcda
	rm -r -f ${cov_dir}
#   Eclipse folder
	rm -r -f ./Default

.PHONY: very-clean
very-clean: clean
	rm -f ${DLL}
	rm -f $(lib_dir)/*.a

$(example_dir)/%$(EXE): $(example_dir)/%.c ${DLL}
	$(CC) $(CFLAGS) $< $(CMOCKA) $(APPROVALS) -o $@

.PHONY: example
example: ${EXAMPLE_EXE}
	for exe in ${EXAMPLE_EXE}; do $$exe || exit; done
