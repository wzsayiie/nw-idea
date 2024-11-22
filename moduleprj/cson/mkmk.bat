@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=cson_main

set srcd=               ^
    ../../capi/cson     ^
    ../../capi/dash     ^
    ../../host/console

call ..\..\mkwrapper.bat

endlocal
