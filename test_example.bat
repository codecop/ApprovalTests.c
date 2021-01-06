@setlocal
@rem compile time
@set C_INCLUDE_PATH=%C_INCLUDE_PATH%;.\include
@rem linking time
@set LIBRARY_PATH=%LIBRARY_PATH%;.\lib
@rem run time for dynamic link library
@set PATH=%PATH%;.\bin
@call make example
@endlocal
