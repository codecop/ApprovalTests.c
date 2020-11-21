# ApprovalTests.c

Approval Tests for C99. This is a plain/portable C 99 version of [Approval Tests](https://approvaltests.com/).

> Unit testing asserts can be difficult to use. Approval tests simplify this by taking a snapshot of the results, and confirming that they have not changed.
>
> In normal unit testing, you say `assert_int_equal(5, person->age)`. Approvals allow you to do this when the thing that you want to assert is no longer a primitive but a complex object. For example, you can say, `verify_txt(person_to_string(person))`.

## Usage with cmocka

This approvals support [cmocka](https://cmocka.org/).

### Creating a Test

See the tests in `./example` folder.

### Compiling and Running

Compile and run a [cmocka](https://cmocka.org/) test which uses approvals using the [binary distribution](https://github.com/codecop/ApprovalTests.c/releases):

    gcc -std=c99 -pedantic -pedantic-errors -Wall -Wextra ...
        AppTest.c
        -l cmocka -l approvals
        -o AppTest.exe

    ./AppTest.exe

## Building

Building under Windows creates the library stub (in `./lib`) and thd dynamic library (in `./bin`).
For Linux this command creates the shared library (in `./lib`).

    make build

## License

Copyright (c) 2020, Peter Kofler. All rights reserved.
[New BSD License](https://opensource.org/licenses/BSD-3-Clause), see `LICENSE` in repository.
