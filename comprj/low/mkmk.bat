@echo off

setlocal

cd /d %~dp0

set defm=/Dlow_main=main

set srcd=           ^
    ../../api/low   ^
    ../../api/dash

call ..\..\mkwrapper.bat

endlocal
