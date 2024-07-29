@echo off

setlocal

cd /d %~dp0

set defm=/Dlow_main=main

set srcd=           ^
    ../../cpp/low   ^
    ../../cpp/dash

call ..\..\mkbuild.bat

endlocal
