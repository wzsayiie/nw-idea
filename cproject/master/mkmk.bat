@echo off

setlocal

cd /d %~dp0

set defm=/Dmaster_main=main

set srcd=               ^
    ../../cpp/master    ^
    ../../cpp/dash      ^
    ../../cpp/low       ^
    ../../cpp/reflect

call ..\..\mkbuild.bat

endlocal
