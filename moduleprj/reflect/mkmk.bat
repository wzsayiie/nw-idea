@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=reflect_main

set srcd=               ^
    ../../capi/reflect  ^
    ../../capi/dash     ^
    ../../host/unix

call ..\..\mkwrapper.bat

endlocal
