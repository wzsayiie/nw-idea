@echo off

setlocal

cd /d %~dp0

set defm=/Dreflect_main=main

set srcd=               ^
    ../../cpp/reflect   ^
    ../../cpp/dash

call ..\..\mkbuild.bat

endlocal
