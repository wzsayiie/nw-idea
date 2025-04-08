@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=dash_main

set srcd=               ^
    ../../capi/dash     ^
    ../../host/console

call ..\..\mkwrapper.bat

endlocal
