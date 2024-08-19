@echo off

setlocal

cd /d %~dp0

set defm=/Dmaster_main=main

set srcd=               ^
    ../../api/master    ^
    ../../api/dash      ^
    ../../api/low       ^
    ../../api/reflect

call ..\..\mkwrapper.bat

endlocal
