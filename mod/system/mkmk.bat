@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=SMain

set srcd=                   ^
    ../../cppapi/system     ^
    ../../cppapi/dash       ^
    ../../cppapi/low        ^
    ../../cppapi/reflect    ^
    ../../host/console

call ..\..\mkgen.bat

endlocal
