# ApprovalTests.c

Approval Tests for C99. This is a plain/portable C 99 version of [Approval Tests](https://approvaltests.com/).

> Unit testing asserts can be difficult to use. Approval tests simplify this by taking a snapshot of the results, and confirming that they have not changed.
>
> In normal unit testing, you say `assert_int_equal(5, person->age)`. Approvals allow you to do this when the thing that you want to assert is no longer a primitive but a complex object. For example, you can say, `verify_txt(person_to_string(person))`.

## Features

### V1.0

* Verify using `verify_txt()` and `verify_xml()` macros with [cmocka](https://cmocka.org/).
* Format XML before verification, so approved file is readable.
* See `example/ExampleTest`.
* Release binaries for Windows x64 and Linux x64.

### V1.1

* Add reporters: quiet reporter prints the copy command and
  diff reporters open an external diff tool.
* Extensive list of predefined diff tools for `approval_first_working_diff`.
* See `example/ReporterExampleTest`.
* Verify without cmocka using plain `assert`.
* See `example/NoFrameworkExampleTest`.
* Release binaries for Windows x86 and Linux x86, too.

## Usage

### Creating a Test

See the tests in `./example` folder.

### Compiling and Running

Compile and run a [cmocka](https://cmocka.org/) test which uses approvals using the [binary distribution](https://github.com/codecop/ApprovalTests.c/releases):

    gcc -std=c99 -pedantic -pedantic-errors -Wall -Wextra ...
        ExampleTest.c
        -l cmocka -l approvals
        -o ExampleTest.exe

    ./ExampleTest.exe

## Building

Building under Windows creates the library stub (in `./lib`) and thd dynamic library (in `./bin`).
For Linux this command creates the shared library (in `./lib`).

    make build

## License

Copyright (c) 2020, Peter Kofler. All rights reserved.
[New BSD License](https://opensource.org/licenses/BSD-3-Clause), see `LICENSE` in repository.
