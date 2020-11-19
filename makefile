##### folders
src_dir 	:= ./src
test_dir 	:= ./tests
cov_dir 	:= ./gcov
lib_dir 	:= ./lib
example_dir := ./example

##### files
src_files 	:= $(wildcard $(src_dir)/*.c)
obj_files 	:= $(src_files:.c=.o)

ifeq ($(OS),Windows_NT)
exec_extension := .exe
else
exec_extension := .
endif

test_sources := $(wildcard $(test_dir)/*Test.c)
test_runners := $(test_sources:.c=$(exec_extension))

cov_sources := $(src_files:.c=.c.gcov)
cov_files 	:= $(cov_sources:$(src_dir)/%=$(cov_dir)/%)

ifeq ($(OS),Windows_NT)
library := ./bin/approvals.dll
else
library := ${lib_dir}/libapprovals.so
endif

example_sources := $(wildcard $(example_dir)/*Test.c)
example_runners := $(example_sources:.c=$(exec_extension))

##### tools
CC := gcc
COV := gcov

##### flags
STD := c99
BASE_FLAGS = -std=$(STD) -Werror -Wall -Wextra -pedantic -pedantic-errors -Wno-error=format -Wno-error=unused-variable
# add more from https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html

ifneq ($(OS),Windows_NT)
BASE_FLAGS += -fPIC
endif

CFLAGS := -g
# user can override with -O
COMPILE_FLAGS = $(BASE_FLAGS) -c
# -c ... Compile and assemble, but do not link.
TEST_FLAGS = $(BASE_FLAGS)
SHARED_FLAGS := $(BASE_FLAGS) -shared

ifeq ($(OS),Windows_NT)
    # https://stackoverflow.com/questions/17601949/building-a-shared-library-using-gcc-on-linux-and-mingw-on-windows
	SHARED_FLAGS += -Wl,--out-implib,${lib_dir}/libapprovals.a
endif

CMOCKA := -lcmocka
APPROVALS := -lapprovals


ifeq ($(GCOV),on)
	COMPILE_FLAGS += --coverage
endif

$(src_dir)/%.o: $(src_dir)/%.c
	$(CC) $(COMPILE_FLAGS) ${CFLAGS} $< -o $@

# https://stackoverflow.com/questions/15189704/makefile-removes-object-files-for-no-reason

$(test_dir)/%$(exec_extension): $(test_dir)/%.c ${obj_files}
	$(CC) $(TEST_FLAGS) ${CFLAGS} ${obj_files} $< $(CMOCKA) -o $@

# $< will represent the source file wherever it is

# Target names should use lower case letters. Words are separated with a hyphen

.PHONY: check
check: test

.PHONY: test
test: ${test_runners}
	for exe in ${test_runners}; do $$exe || exit; done
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

coverage: test ${cov_files}
	rm -f $(src_dir)/*.gcno $(src_dir)/*.gcda

${library}: ${obj_files}
	$(CC) $(SHARED_FLAGS) $(CFLAGS) $^ -o ${library}

lib: build
# alias "to create the libraries"
build: very-clean ${library}

.PHONY: clean
clean:
	rm -f $(src_dir)/*.o
	rm -f $(test_dir)/*.o $(test_dir)/*$(exec_extension) $(test_dir)/*.received.*
	rm -f ${example_dir}/*.o ${example_dir}/*$(exec_extension) ${example_dir}/*.received.*
	rm -f $(src_dir)/*.gcno
	rm -f $(src_dir)/*.gcda
	rm -r -f ${cov_dir}
#   Eclipse folder
	rm -r -f ./Default

.PHONY: very-clean
very-clean: clean
	rm -f ${library}
	rm -f $(lib_dir)/*.a

$(example_dir)/%$(exec_extension): $(example_dir)/%.c ${library}
	$(CC) $(TEST_FLAGS) $(CFLAGS) $< $(CMOCKA) $(APPROVALS) -o $@

.PHONY: example
example: ${example_runners}
	for exe in ${example_runners}; do $$exe || exit; done
