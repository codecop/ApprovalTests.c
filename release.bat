@rem create Windows x86 binaries
setlocal
call ..\setenv.bat
call make clean_all
call test
call make build example
call ant -Darch=x86
endlocal

@rem create Windows x64 binaries
setlocal
call ..\setenv_x64.bat
call make clean_all
call test
call make build example
call ant

@rem leave x64 binaries around
make clean
endlocal

@rem get Linux x64 binaries
start "GitHub" https://github.com/codecop/ApprovalTests.c/actions
@echo "download artefact"

@pause
