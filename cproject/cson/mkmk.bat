@echo off

setlocal

cd /d %~dp0

set defm=/Dcson_main=main

set srcd=           ^
    ../../cpp/cson  ^
    ../../cpp/dash

call ..\..\mkbuild.bat

endlocal
