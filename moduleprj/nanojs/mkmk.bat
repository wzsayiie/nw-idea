@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=nanojs_main

set srcd=               ^
    ../../vm/nanojs     ^
    ../../api/dash      ^
    ../../vm/nanolib    ^
    ../../host/unix

call ..\..\mkwrapper.bat

endlocal