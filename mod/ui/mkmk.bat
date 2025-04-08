@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=UMain

set srcd=                   ^
    ../../cppapi/ui         ^
    ../../cppapi/dash       ^
    ../../cppapi/low        ^
    ../../cppapi/reflect    ^
    ../../host/console

call ..\..\mkgen.bat

endlocal
