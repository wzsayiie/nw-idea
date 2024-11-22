@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=UMain

set srcd=               ^
    ../../capi/ui       ^
    ../../capi/dash     ^
    ../../capi/low      ^
    ../../capi/reflect  ^
    ../../host/unix

call ..\..\mkwrapper.bat

endlocal
