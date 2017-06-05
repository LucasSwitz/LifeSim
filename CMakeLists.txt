cmake_minimum_required(VERSION 2.6)

set(PROJECT_NAME_STR LifeSim-Test)
project(${PROJECT_NAME_STR} CXX)

find_package(Threads REQUIRED)

add_subdirectory($ENV{GTEST_DIR})

include_directories($ENV{GTEST_DIR}/include ".")

file(GLOB_RECURSE SOURCES
    main.cpp
    src/*.h
    src/*.cpp
)

add_executable(${PROJECT_NAME_STR} ${SOURCES})

target_link_libraries(${PROJECT_NAME_STR} $ENV{GTEST_LIB_DIR}/libgtest.a)

target_link_libraries(${PROJECT_NAME_STR} ${CMAKE_THREAD_LIBS_INIT})

target_compile_features(${PROJECT_NAME_STR} PRIVATE cxx_range_for)
