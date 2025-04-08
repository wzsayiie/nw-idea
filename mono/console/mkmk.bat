@echo off

setlocal

cd /d %~dp0

set defm=

set srcd=               ^
    ../../host/console  ^
    ../../capi/cson     ^
    ../../capi/dash     ^
    ../../capi/low      ^
    ../../capi/master   ^
    ../../capi/net      ^
    ../../capi/reflect  ^
    ../../capi/system   ^
    ../../capi/ui       ^
    ../../cvm/nanojs    ^
    ../../cvm/nanolib

call ..\..\mkwrapper.bat

endlocal
