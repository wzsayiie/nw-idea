@echo off

setlocal

cd /d %~dp0

set defm=/Dcson_main=main

set srcd=           ^
    ../../api/cson  ^
    ../../api/dash

call ..\..\mkwrapper.bat

endlocal
