@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=nanolib_main

set srcd=               ^
    ../../vm/nanolib    ^
    ../../api/dash      ^
    ../../host/unix

call ..\..\mkwrapper.bat

endlocal
