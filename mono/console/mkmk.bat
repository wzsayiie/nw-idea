@echo off

setlocal

cd /d %~dp0

set defm=

set srcd=                   ^
    ../../host/console      ^
    ../../cppapi/cson       ^
    ../../cppapi/dash       ^
    ../../cppapi/low        ^
    ../../cppapi/master     ^
    ../../cppapi/net        ^
    ../../cppapi/reflect    ^
    ../../cppapi/system     ^
    ../../cppapi/ui         ^
    ../../cppvm/nanojs      ^
    ../../cppvm/nanolib

call ..\..\mkgen.bat

endlocal
