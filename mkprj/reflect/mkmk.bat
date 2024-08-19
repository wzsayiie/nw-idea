@echo off

setlocal

cd /d %~dp0

set defm=/Dreflect_main=main

set srcd=               ^
    ../../api/reflect   ^
    ../../api/dash

call ..\..\mkwrapper.bat

endlocal
