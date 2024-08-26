@echo off

setlocal

cd /d %~dp0

set defm=/Dui_main=main

set srcd=               ^
    ../../api/ui        ^
    ../../api/dash      ^
    ../../api/low       ^
    ../../api/reflect

call ..\..\mkwrapper.bat

endlocal
