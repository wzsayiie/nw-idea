@echo off

setlocal

cd /d %~dp0

set defm=/Ddash_main=main
set srcd=../../api/dash

call ..\..\mkwrapper.bat

endlocal
