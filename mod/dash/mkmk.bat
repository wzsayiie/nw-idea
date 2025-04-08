@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=dash_main

set srcd=               ^
    ../../cppapi/dash   ^
    ../../host/console

call ..\..\mkgen.bat

endlocal
