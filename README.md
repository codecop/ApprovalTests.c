# ApprovalTests.c

Plain/portable C 99 version - micro Approvals.

## cmocka

This approvals support [cmocka](https://cmocka.org/).

To compile and run a test with:

    gcc -g -Wall -Wextra -pedantic -std=c99 ... ..\src\approvals.c AppTest.c -l cmocka -o AppTest.exe
    ./AppTest.exe

## License

Copyright (c) 2020, Peter Kofler. All rights reserved.
[New BSD License](https://opensource.org/licenses/BSD-3-Clause), see `LICENSE` in repository.
