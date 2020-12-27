# Open

* C way: allow function pointers at certain places for future expansion.

* default approval is last

  * pass __LINE__ to approval and then use cmocka equals as internal reporter
    must be last reporter then
    how do we determine if cmocka is included? #ifdef CMOCKA_H_
    This one is abort when done.

  * add a plain assert reporter by default
    last last reporter is the assert one. This one is abort when done.

* Documentation in Markdown

  * describe features related to usual approvals:
  * cmocka integration, verify text, verify xml,
  * binaries for linux and windows x64

  * 1.1 quiet reporter, diff reporters,
  * binaries for linux and windows x86

* create second Example with reporters in before

* Release with all 4 Platforms
