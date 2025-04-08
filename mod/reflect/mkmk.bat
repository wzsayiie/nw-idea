@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=reflect_main

set srcd=                   ^
    ../../cppapi/reflect    ^
    ../../cppapi/dash       ^
    ../../host/console

call ..\..\mkgen.bat

endlocal
