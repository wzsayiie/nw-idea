@echo off

::these parameters need to be provided externally:
::  srcd: header and source directories;
::  defm: defined macros.

setlocal EnableDelayedExpansion

::build mkmk tool.
set mkmk=%~dp0\mkmk
if not exist %mkmk%.exe (
    call cl                             ^
        /nologo /Ox /EHsc /std:c++20    ^
        /Fo%mkmk%.obj                   ^
        /Fe%mkmk%.exe                   ^
        %mkmk%.cpp

    del %mkmk%.obj
)

::generate makefile.
set incd=
for %%i in (%srcd%) do (
    set incd=!incd! /I%%i
)

if not exist obj (
    mkdir obj
)

call %mkmk%.exe                                                         ^
    --compile-cmd "cl %defm% %incd% /nologo /EHsc /std:c++20 /c /Fo"    ^
    --link-cmd    "link /nologo /noimplib /noexp /out:"                 ^
    --header-dirs %srcd%                                                ^
    --source-dirs %srcd%                                                ^
    --output-file out.exe                                               ^
    --object-dir  obj                                                   ^
    > makefile

endlocal
