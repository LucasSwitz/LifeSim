#!/bin/bash

export GTEST_DIR=/home/pabu/Desktop/LifeSim/include/googletest
export GTEST_LIB_DIR=/home/pabu/Desktop/LifeSim/lib
export LUA_LIB_DIR=/usr/lib/x86_64-linux-gnu
export LUA_INCLUDE_DIR=/usr/include/lua5.2/
export LUA_BRIDGE_INCLUDE=/home/pabu/Desktop/LifeSim/include/LuaBridge/Source
export STD_EXPERIMENTAL_LIB=/usr/lib/gcc/x86_64-linux-gnu/5/
export IMGUI_INCLUDE_DIR=/home/pabu/Desktop/LifeSim/include/imgui
export IMGUI_SFML_INCLUDE_DIR=/home/pabu/Desktop/LifeSim/include/imgui-sfml

for arg in "$@"
do
    case "$arg" in
        -c)
            cmake -DCMAKE_PREFIX_PATH="lib/SFML" ..
        ;;
        -s)
            python MakeStatics.py
        ;;
    esac
done

export GTEST_OUTPUT="xml:/home/pabu/Desktop/LifeSim/test/output/test_output"
make
./LifeSim-Test

exit 0
