@echo off

::these parameters need to be provided externally:
::  _exec_: excutable file;
::  _objd_: object directory;
::  _mkmk_: mkmk tool;
::  _dirs_: source directories.

setlocal EnableDelayedExpansion

::create object directory.
if not exist %_objd_% (
    mkdir %_objd_%
)

::build mkmk tool.
if not exist %_mkmk_%.exe (
    call cl ^
        /nologo /Ox /EHsc /std:c++20 ^
        /Fo%_mkmk_%.obj ^
        /Fe%_mkmk_%.exe ^
        %_mkmk_%.cpp

    del %_mkmk_%.obj
)

::generate makefile:
set _incs_=
for %%i in (%_dirs_%) do (
    set _incs_=!_incs_! /I%%i
)

call %_mkmk_%.exe ^
    --compile-cmd "cl /nologo /EHsc /std:c++20 /c %_incs_% /Fo" ^
    --link-cmd    "link /nologo /noimplib /noexp /out:" ^
    --output-file %_exec_%   ^
    --object-dir  %_objd_%   ^
    --header-dirs %_dirs_%   ^
    --source-dirs %_dirs_% . ^
    > makefile

endlocal
