@echo off

setlocal

cd /d %~dp0

set defm=/Dnanojs_main=main

set srcd=               ^
    ../../vm/nanojs     ^
    ../../api/dash      ^
    ../../vm/nanojslib

call ..\..\mkwrapper.bat

endlocal
