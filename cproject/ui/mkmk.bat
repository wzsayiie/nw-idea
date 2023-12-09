@echo off

setlocal

set _out_exe=app.exe
set _obj_dir=obj

cd /d %~dp0

if not exist %_obj_dir% (
    mkdir %_obj_dir%
)

call ..\..\mbuild.bat
call ..\..\mkmk.exe ^
    --compile-cmd "cl /nologo /EHsc /std:c++20 /c /I../../cpp/dash /I../../cpp/ui /Fo" ^
    --link-cmd    "link /nologo /noimplib /noexp /out:" ^
    --output-file %_out_exe%    ^
    --object-dir  %_obj_dir%    ^
    --header-dirs           ^
        ../../cpp/dash      ^
        ../../cpp/reflect   ^
        ../../cpp/ui        ^
    --source-dirs           ^
        ../../cpp/dash      ^
        ../../cpp/reflect   ^
        ../../cpp/ui        ^
        .                   ^
    > makefile

endlocal
