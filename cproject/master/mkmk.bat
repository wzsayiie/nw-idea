@echo off

setlocal

set _out_exe=app.exe
set _obj_dir=obj

cd /d %~dp0

if not exist %_obj_dir% (
    mkdir %_obj_dir%
)

call ..\..\mksr.bat
call ..\..\mkmk.exe ^
    --compile-cmd "cl /nologo /EHsc /std:c++20 /c /I../../cpp/dash /I../../cpp/master /Fo" ^
    --link-cmd    "link /nologo /noimplib /noexp /out:" ^
    --output-file %_out_exe%    ^
    --object-dir  %_obj_dir%    ^
    --header-dirs           ^
        ../../cpp/dash      ^
        ../../cpp/nanojs    ^
        ../../cpp/reflect   ^
        ../../cpp/sjson     ^
        ../../cpp/master    ^
    --source-dirs           ^
        ../../cpp/dash      ^
        ../../cpp/nanojs    ^
        ../../cpp/reflect   ^
        ../../cpp/sjson     ^
        ../../cpp/master    ^
        .                   ^
    > makefile

endlocal
