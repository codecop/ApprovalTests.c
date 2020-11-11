# Open

* assert based approvals without testing framework

* More reporters
  * https://github.com/approvals/ApprovalTests.Java/tree/master/approvaltests/src/main/java/org/approvaltests/reporters
  * kdiff reporter
  * generic diff with all tools:
  * https://github.com/approvals/ApprovalTests.Java/blob/master/approvaltests/src/main/java/org/approvaltests/reporters/DiffPrograms.java
    * struct with all tools for each OS

Windows test
* Kdiff installation
  C:\Program Files (x86)\KDiff3\kdiff3.exe
* TortoiseHg installation
  C:\Program Files\TortoiseHg\bin\kdiff3.exe
* Windows SDK 7.1
  "C:\Program Files\Microsoft SDKs\Windows\v7.1\Bin\x64\WinDiff.Exe"

public static DiffInfo KDIFF3 = new DiffInfo("{ProgramFiles}KDiff3\\kdiff3.exe", TEXT);
public static DiffInfo VISUAL_STUDIO_CODE  = new DiffInfo("{ProgramFiles}Microsoft VS Code\\Code.exe", "-d %s %s", TEXT);