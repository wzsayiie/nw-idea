@echo off

setlocal

cd /d %~dp0

set defm=/Dui_main=main

set srcd=               ^
    ../../cpp/ui        ^
    ../../cpp/dash      ^
    ../../cpp/reflect

call ..\..\mkbuild.bat

endlocal
