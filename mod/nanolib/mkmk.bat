@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=nanolib_main

set srcd=               ^
    ../../cvm/nanolib   ^
    ../../capi/dash     ^
    ../../host/console

call ..\..\mkwrapper.bat

endlocal
