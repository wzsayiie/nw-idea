@echo off

setlocal

cd /d %~dp0

set defm=/Dcustom_main=SMain

set srcd=               ^
    ../../capi/system   ^
    ../../capi/dash     ^
    ../../capi/low      ^
    ../../capi/reflect  ^
    ../../host/console

call ..\..\mkwrapper.bat

endlocal
