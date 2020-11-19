library_name := approvals

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

test_src_files := $(wildcard $(test_dir)/*Test.c)
test_run_files := $(test_src_files:.c=$(exec_extension))

cov_sources := $(src_files:.c=.c.gcov)
cov_files 	:= $(cov_sources:$(src_dir)/%=$(cov_dir)/%)

ifeq ($(OS),Windows_NT)
library := ./bin/$(library_name).dll
else
library := ${lib_dir}/lib$(library_name).so
endif

example_src_files := $(wildcard $(example_dir)/*Test.c)
example_run_files := $(example_src_files:.c=$(exec_extension))

##### tools
CC := gcc
COV := gcov

##### flags
CFLAGS := -g
# user can override with -O

STD := c99
C_BASE_FLAGS = -std=$(STD) -Werror -Wall -Wextra -pedantic -pedantic-errors -Wno-error=format -Wno-error=unused-variable
ifneq ($(OS),Windows_NT)
C_BASE_FLAGS += -fPIC
endif

C_COMPILE_FLAGS = $(C_BASE_FLAGS) -c ${CFLAGS}
ifeq ($(GCOV),on)
	C_COMPILE_FLAGS += --coverage
endif

C_TEST_FLAGS = $(C_BASE_FLAGS) ${CFLAGS}
CMOCKA := -lcmocka

C_LIBRARY_FLAGS := $(C_BASE_FLAGS) ${CFLAGS} -shared
ifeq ($(OS),Windows_NT)
C_LIBRARY_FLAGS += -Wl,--out-implib,${lib_dir}/lib$(library_name).a
# https://stackoverflow.com/questions/17601949/building-a-shared-library-using-gcc-on-linux-and-mingw-on-windows
endif

APPROVALS := -l$(library_name)

##### targets

$(src_dir)/%.o: $(src_dir)/%.c
	$(CC) $(C_COMPILE_FLAGS) $< -o $@

# https://stackoverflow.com/questions/15189704/makefile-removes-object-files-for-no-reason

$(test_dir)/%$(exec_extension): $(test_dir)/%.c ${obj_files}
	$(CC) $(C_TEST_FLAGS) ${obj_files} $< $(CMOCKA) -o $@

# $< will represent the source file wherever it is

.PHONY: check
check: test

.PHONY: test
test: ${test_run_files}
	for exe in ${test_run_files}; do $$exe || exit; done
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
	$(CC) $(C_LIBRARY_FLAGS) $^ -o ${library}

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
	$(CC) $(C_TEST_FLAGS) $< $(CMOCKA) $(APPROVALS) -o $@

.PHONY: example
example: ${example_run_files}
	for exe in ${example_run_files}; do $$exe || exit; done
