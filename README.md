# ApprovalTests.c.cmocka

Plain/portable C 99 version - micro Approvals.

This approvals support [cmocka](https://cmocka.org/).

To compile and run a test:

    gcc -g -Wall -Wextra -pedantic -std=c99 ... AppTest.c Approvals.c -l cmocka -o AppTest
    ./AppTest

## License

Copyright (c) 2020, Peter Kofler. All rights reserved.
[New BSD License](https://opensource.org/licenses/BSD-3-Clause), see `LICENSE` in repository.
