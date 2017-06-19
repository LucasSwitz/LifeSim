#!/bin/bash

export GTEST_DIR=/home/pabu/Desktop/LifeSim/include/googletest
export GTEST_LIB_DIR=/home/pabu/Desktop/LifeSim/lib
export LUA_LIB_DIR=/usr/local/lib
export LUA_INCLUDE_DIR=/usr/local/include
export LUA_BRIDGE_INCLUDE=/home/pabu/Desktop/LifeSim/include/LuaBridge/Source
export STD_EXPERIMENTAL_LIB=/usr/lib/gcc/x86_64-linux-gnu/5/

for arg in "$@"
do
    case "$arg" in
        -c)
            cmake ..
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
