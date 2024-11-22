@echo off

setlocal

cd /d %~dp0

set defm=

set srcd=               ^
    ../../host/unix     ^
    ../../api/cson      ^
    ../../api/dash      ^
    ../../api/low       ^
    ../../api/master    ^
    ../../api/net       ^
    ../../api/reflect   ^
    ../../api/system    ^
    ../../api/ui        ^
    ../../vm/nanojs     ^
    ../../vm/nanojslib

call ..\..\mkwrapper.bat

endlocal
