@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=nanojs_main

set srcd=               ^
    ../../cvm/nanojs    ^
    ../../cvm/nanolib   ^
    ../../capi/dash     ^
    ../../host/console

call ..\..\mkwrapper.bat

endlocal
