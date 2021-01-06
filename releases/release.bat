@if exist "%~n0%~x0" @cd ..

@set V=1.1
@rem rmdir /S /Q releases\v%V%
mkdir releases\v%V%

@echo ----- create Windows x86 binaries -----
@setlocal
call ..\setenv.bat
call make build test example
call ant -f releases\build.xml -Darch=x86 -Dversion=%V%
@endlocal

@echo ----- create Windows x64 binaries -----
@setlocal
call ..\setenv_x64.bat
call make build test example
call ant -f releases\build.xml -Dversion=%V%
@rem leave x64 binaries around
make clean
@endlocal

@echo ----- create Linux x86 binaries -----
@setlocal
set PATH=%PATH%;C:\Progra~2\msysGit-1.8.5\bin
call ssh pkofler@anthill "cd ApprovalTests.c && git pull && make build test && ant -f releases/build.xml -Dos=Linux -Darch=x86 -Dversion=%V%"
call scp pkofler@anthill:~/ApprovalTests.c/releases/v%V%/Binaries_Linux_x86.zip releases\v%V%\
@endlocal

@echo ----- download Linux x64 binaries -----
start "GitHub" https://github.com/codecop/ApprovalTests.c/actions?query=workflow%3A%22CI+Workflow+C+Make%22
@echo click latest job, download binaries
explorer "releases\v%V%"
@pause
