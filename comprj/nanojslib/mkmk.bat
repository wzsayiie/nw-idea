@echo off

setlocal

cd /d %~dp0

set defm=/Dnanojslib_main=main

set srcd=               ^
    ../../vm/nanojslib  ^
    ../../api/dash

call ..\..\mkwrapper.bat

endlocal
