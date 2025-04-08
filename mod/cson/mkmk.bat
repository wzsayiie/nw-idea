@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=cson_main

set srcd=               ^
    ../../cppapi/cson   ^
    ../../cppapi/dash   ^
    ../../host/console

call ..\..\mkgen.bat

endlocal
