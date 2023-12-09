@echo off

setlocal

set _file=mkmk

cd /d %~dp0

if not exist %_file%.exe (
    call cl ^
        /nologo /Ox /EHsc /std:c++20 ^
        /Fo%_file%.obj ^
        /Fe%_file%.exe ^
        %_file%.cpp

    del %_file%.obj
)

endlocal
