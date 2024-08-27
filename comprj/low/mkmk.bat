@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=low_main

set srcd=           ^
    ../../api/low   ^
    ../../api/dash

call ..\..\mkwrapper.bat

endlocal
