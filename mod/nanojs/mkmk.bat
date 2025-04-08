@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=nanojs_main

set srcd=               ^
    ../../cppvm/nanojs  ^
    ../../cppvm/nanolib ^
    ../../cppapi/dash   ^
    ../../host/console

call ..\..\mkgen.bat

endlocal
