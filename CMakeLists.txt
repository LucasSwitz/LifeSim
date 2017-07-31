cmake_minimum_required(VERSION 2.6)
#[[set(CMAKE_CXX_FLAGS "-llua -ldl -lglut -lGL")]]
set(PROJECT_NAME_STR LifeSim-Test)
project(${PROJECT_NAME_STR} CXX)
find_package(Threads REQUIRED)


add_subdirectory($ENV{GTEST_DIR})

include_directories($ENV{GTEST_DIR}/include ".")
include_directories($ENV{LUA_INCLUDE_DIR} ".")
include_directories($ENV{LUA_BRIDGE_INCLUDE} ".")
include_directories($ENV{IMGUI_INCLUDE_DIR} ".")
include_directories($ENV{IMGUI_SFML_INCLUDE_DIR} ".")
include_directories($ENV{PROTOBUF_INCLUDE_DIR} ".")
include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES
    imgui.cpp
    imgui_draw.cpp
    imgui-SFML.cpp
    main.cpp
    src/*.h
    src/*.cpp
    src/*.cc)

add_executable(${PROJECT_NAME_STR} ${SOURCES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)


set(CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED network audio graphics window system)

if(SFML_FOUND)
  include_directories(SFML_INCLUDE_DIR)
  target_link_libraries(${PROJECT_NAME_STR} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

target_link_libraries(${PROJECT_NAME_STR} $ENV{GTEST_LIB_DIR}/libgtest.a)
target_link_libraries(${PROJECT_NAME_STR} $ENV{LUA_LIB_DIR}/liblua.a)
target_link_libraries(${PROJECT_NAME_STR} $ENV{PROTOBUF_LIB_DIR}/libprotobuf.a)
target_link_libraries(${PROJECT_NAME_STR} $ENV{STD_EXPERIMENTAL_LIB}/libstdc++fs.a)
target_link_libraries(${PROJECT_NAME_STR} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})


target_link_libraries(${PROJECT_NAME_STR} ${CMAKE_DL_LIBS})
target_link_libraries(${PROJECT_NAME_STR} ${CMAKE_THREAD_LIBS_INIT})

set_property(TARGET ${PROJECT_NAME_STR} PROPERTY CXX_STANDARD 14)

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
