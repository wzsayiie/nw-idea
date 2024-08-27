@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=reflect_main

set srcd=               ^
    ../../api/reflect   ^
    ../../api/dash      ^
    ../../host/unix

call ..\..\mkwrapper.bat

endlocal
