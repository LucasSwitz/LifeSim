#!/bin/bash

export GTEST_DIR=/home/lucas/Desktop/LifeSim/include/googletest
export GTEST_LIB_DIR=/home/lucas/Desktop/LifeSim/lib
export LUA_LIB_DIR=/usr/local/lib
export LUA_INCLUDE_DIR=/usr/local/include
export LUA_BRIDGE_INCLUDE=/home/lucas/Desktop/LifeSim/include/LuaBridge/Source

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

export GTEST_OUTPUT="xml:/home/lucas/Desktop/LifeSim/test/output/test_output"
make
./LifeSim-Test

exit 0
