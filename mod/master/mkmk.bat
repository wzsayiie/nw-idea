@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=MMain

set srcd=                   ^
    ../../cppapi/master     ^
    ../../cppapi/dash       ^
    ../../cppapi/low        ^
    ../../cppapi/reflect    ^
    ../../host/console

call ..\..\mkgen.bat

endlocal
