# Open

* pass __LINE__ to approval and then use cmocka equals as internal reporter
  must be last reporter then
  how do we determine if cmocka is included? #ifdef CMOCKA_H_

* find all array and use pointer arith instead
  "An expression that evaluates to an object is inherently more subtle and error-prone than the address of that object. Correct use of pointers can simplify code:"

* allow function pointers at certain places for future expansion.

* #ifndef __approval_assert_equals add a plain assert reporter by default

* Documentation

  * describe features related to usual approvals:
  * cmocka integration, verify text, verify xml,
  * binaries for linux and windows x64

  * 1.1 quiet reporter, diff reporters,
  * binaries for linux and windows x86

* create second Example with reporters in before
