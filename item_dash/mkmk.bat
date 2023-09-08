@echo off

setlocal

set _mk_tool=..\mkmk
set _out_exe=app.exe
set _obj_dir=obj

cd %~dp0

if not exist %_mk_tool%.exe (
    cl /nologo /EHsc /std:c++20 /Fo%_mk_tool%.obj /Fe%_mk_tool%.exe %_mk_tool%.cpp
    del %_mk_tool%.obj
)

if not exist %_obj_dir% (
    mkdir %_obj_dir%
)

%_mk_tool%.exe ^
    --compile-cmd "cl /nologo /EHsc /std:c++20 /c /I../src/dash /I../src/reflect /Fo" ^
    --link-cmd    "link /nologo /noimplib /noexp /out:" ^
    --output-file %_out_exe% ^
    --object-dir  %_obj_dir% ^
    --header-dirs   ^
        ../src/dash ^
    --source-dirs   ^
        ../src/dash ^
        .           ^
    > makefile

endlocal
