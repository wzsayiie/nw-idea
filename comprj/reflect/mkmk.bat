@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=reflect_main

set srcd=               ^
    ../../api/reflect   ^
    ../../api/dash

call ..\..\mkwrapper.bat

endlocal
