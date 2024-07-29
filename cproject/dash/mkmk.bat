@echo off

setlocal

cd /d %~dp0

set defm=/Ddash_main=main
set srcd=../../cpp/dash

call ..\..\mkbuild.bat

endlocal
