@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=low_main

set srcd=               ^
    ../../cppapi/low    ^
    ../../cppapi/dash   ^
    ../../host/console

call ..\..\mkgen.bat

endlocal
