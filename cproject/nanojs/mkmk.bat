@echo off

setlocal

cd /d %~dp0

set defm=/Dnanojs_main=main

set srcd=               ^
    ../../cpp/nanojs    ^
    ../../cpp/dash

call ..\..\mkbuild.bat

endlocal
