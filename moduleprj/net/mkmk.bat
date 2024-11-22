@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=UMain

set srcd=               ^
    ../../capi/net      ^
    ../../capi/dash     ^
    ../../capi/low      ^
    ../../capi/reflect  ^
    ../../host/unix

call ..\..\mkwrapper.bat

endlocal
