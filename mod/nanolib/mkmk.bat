@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=nanolib_main

set srcd=               ^
    ../../cppvm/nanolib ^
    ../../cppapi/dash   ^
    ../../host/console

call ..\..\mkgen.bat

endlocal
