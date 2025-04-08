@echo off

::these parameters need to be provided externally:
::  srcd: header and source directories;
::  defm: defined macros.

setlocal EnableDelayedExpansion

::build mkout tool.
set mkout=%~dp0\mkout
if not exist %mkout%.exe (
    call cl                             ^
        /nologo /Ox /EHsc /std:c++20    ^
        /Fo%mkout%.obj                  ^
        /Fe%mkout%.exe                  ^
        %mkout%.cpp

    del %mkout%.obj
)

::generate makefile.
set incd=
for %%i in (%srcd%) do (
    set incd=!incd! /I%%i
)

if not exist obj (
    mkdir obj
)

call %mkout%.exe                                                        ^
    --compile-cmd "cl %defm% %incd% /nologo /EHsc /std:c++20 /c /Fo"    ^
    --link-cmd    "link /nologo /noimplib /noexp /out:"                 ^
    --header-dirs %srcd%                                                ^
    --source-dirs %srcd%                                                ^
    --output-file out.exe                                               ^
    --object-dir  obj                                                   ^
    > makefile

endlocal
