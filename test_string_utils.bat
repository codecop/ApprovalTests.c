@cls
@color 02
@setlocal
@set F=StringUtilsTest

@if exist tests\%F%.exe del tests\%F%.exe
gcc -g -Wall -Wextra -pedantic -std=c99 -O src\string_utils.c tests\%F%.c -l cmocka -o tests\%F%.exe
@if errorlevel 1 @color 04 && @echo FAILED: %errorlevel% && goto end

tests\%F%.exe
@if errorlevel 1 @color 04 && @echo FAILED: %errorlevel% && goto end

:end
@endlocal
