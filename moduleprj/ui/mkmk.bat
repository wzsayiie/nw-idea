@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=UMain

set srcd=               ^
    ../../api/ui        ^
    ../../api/dash      ^
    ../../api/low       ^
    ../../api/reflect   ^
    ../../host/unix

call ..\..\mkwrapper.bat

endlocal