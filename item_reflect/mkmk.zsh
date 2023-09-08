#!/bin/zsh

declare _mk_tool=../mkmk
declare _out_exe=app.exe
declare _obj_dir=obj

cd `dirname $0`

if [ ! -f $_mk_tool.exe ]; then
    c++ --std=c++20 $_mk_tool.exe $_mk_tool.cpp
fi

mkdir -p $_obj_dir

$_mk_tool.exe \
    --compile-cmd "c++ --std=c++20 -c -o " \
    --link-cmd    "c++ -o " \
    --output-file $_out_exe \
    --object-dir  $_obj_dir \
    --header-dirs      \
        ../src/dash    \
        ../src/reflect \
    --source-dirs      \
        ../src/dash    \
        ../src/reflect \
        .              \
    > makefile
