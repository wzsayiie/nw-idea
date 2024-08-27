@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=cson_main

set srcd=           ^
    ../../api/cson  ^
    ../../api/dash  ^
    ../../host/unix

call ..\..\mkwrapper.bat

endlocal
