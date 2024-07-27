@echo off

setlocal

cd /d %~dp0

set _exec_=app.exe
set _objd_=obj
set _mkmk_=..\..\mkmk

set _dirs_=           ^
    ../../cpp/master  ^
    ../../cpp/dash    ^
    ../../cpp/low     ^
    ../../cpp/reflect

call ..\..\mkbuild.bat

endlocal
