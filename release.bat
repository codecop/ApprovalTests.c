setlocal
call ..\setenv.bat
call make clean_all
call test
call make build example
call ant -Darch=x86
endlocal

setlocal
call ..\setenv_x64.bat
call make clean_all
call test
call make build example
call ant

@rem leave x64 binaries around
make clean
endlocal

@pause
