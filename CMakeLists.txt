cmake_minimum_required(VERSION 2.6)

set(PROJECT_NAME_STR google-test)
project(${PROJECT_NAME_STR} CXX)

find_package(Threads REQUIRED)

add_subdirectory($ENV{GTEST_DIR})
include_directories($ENV{GTEST_DIR}/include)

add_executable(${PROJECT_NAME_STR} "src/main.cpp")

target_link_libraries(${PROJECT_NAME_STR} $ENV{GTEST_LIB_DIR}/libgtest.a)

target_link_libraries(${PROJECT_NAME_STR} ${CMAKE_THREAD_LIBS_INIT})
