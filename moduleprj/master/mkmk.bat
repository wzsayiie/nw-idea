@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=MMain

set srcd=               ^
    ../../capi/master   ^
    ../../capi/dash     ^
    ../../capi/low      ^
    ../../capi/reflect  ^
    ../../host/unix

call ..\..\mkwrapper.bat

endlocal
