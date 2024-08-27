@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=dash_main
set srcd=../../api/dash

call ..\..\mkwrapper.bat

endlocal
