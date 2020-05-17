# ApprovalTests.c

Plain/portable C 99 version.

## Building

Create the library stub (in `./lib`) and dynamic library (in `./bin`) with:

    make build

## Usage with cmocka

This approvals support [cmocka](https://cmocka.org/).

### Creating a Test

See `ExampleTest` in `./example`.

### Compiling and Running

Compile and run a test using the sources with:

    gcc -g -Wall -Wextra -pedantic -std=c99 ... ^
        ..\src\approvals.c ..\src\approvals_xml.c ..\src\StringBuilder.c AppTest.c ^
        -l cmocka ^
        -o AppTest.exe
    ./AppTest.exe

If you built the library (`make build`), compile and run a test with:

    gcc -g -Wall -Wextra -pedantic -std=c99 ... ^
        AppTest.c ^
        -l cmocka -l approvals ^
        -o AppTest.exe
    ./AppTest.exe

## License

Copyright (c) 2020, Peter Kofler. All rights reserved.
[New BSD License](https://opensource.org/licenses/BSD-3-Clause), see `LICENSE` in repository.
