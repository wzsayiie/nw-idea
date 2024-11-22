@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=low_main

set srcd=           ^
    ../../capi/low  ^
    ../../capi/dash

call ..\..\mkwrapper.bat

endlocal
