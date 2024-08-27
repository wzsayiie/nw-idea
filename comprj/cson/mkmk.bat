@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=cson_main

set srcd=           ^
    ../../api/cson  ^
    ../../api/dash

call ..\..\mkwrapper.bat

endlocal
