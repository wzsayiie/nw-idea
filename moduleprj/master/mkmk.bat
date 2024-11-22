@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=MMain

set srcd=               ^
    ../../api/master    ^
    ../../api/dash      ^
    ../../api/low       ^
    ../../api/reflect   ^
    ../../host/unix

call ..\..\mkwrapper.bat

endlocal
