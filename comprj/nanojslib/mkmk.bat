@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=nanojslib_main

set srcd=               ^
    ../../vm/nanojslib  ^
    ../../api/dash

call ..\..\mkwrapper.bat

endlocal
