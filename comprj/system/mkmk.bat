@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=SMain

set srcd=               ^
    ../../api/system    ^
    ../../api/dash      ^
    ../../api/low       ^
    ../../api/reflect

call ..\..\mkwrapper.bat

endlocal
