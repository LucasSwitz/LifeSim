cmake_minimum_required(VERSION 2.6)
PROJECT(ThunderBiscuit)
find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
set(CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED network audio graphics window system)

include_directories($ENV{LUA_INCLUDE_DIR} ".")
include_directories($ENV{LUA_BRIDGE_INCLUDE} ".")
include_directories($ENV{IMGUI_INCLUDE_DIR} ".")
include_directories($ENV{IMGUI_SFML_INCLUDE_DIR} ".")
include_directories($ENV{PROTOBUF_INCLUDE_DIR} ".")
include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES
    src/*.h
    src/*.cpp
    src/*.cc)

add_library(tb_lib ${SOURCES})
set_target_properties(tb_lib PROPERTIES CXX_STANDARD 14)
add_executable(editor run_editor.cpp)
target_link_libraries(editor tb_lib)

if(SFML_FOUND)
  target_link_libraries(editor ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

target_link_libraries(editor $ENV{LUA_LIB_DIR}/liblua5.3.a)
target_link_libraries(editor $ENV{PROTOBUF_LIB_DIR}/libprotobuf.a)
target_link_libraries(editor $ENV{STD_EXPERIMENTAL_LIB}/libstdc++fs.a)
target_link_libraries(editor ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(editor ${CMAKE_DL_LIBS})
target_link_libraries(editor ${CMAKE_THREAD_LIBS_INIT})

set_property(TARGET editor PROPERTY CXX_STANDARD 14)

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
    
#TESTS
enable_testing()
add_subdirectory($ENV{GTEST_DIR})
include_directories($ENV{GTEST_DIR}/include ".")

file(GLOB_RECURSE TEST_SOURCES
    test/*.h
    test/*.cpp
    test/*.cc)
    
add_library(tb_test ${TEST_SOURCES})
set_target_properties(tb_test PROPERTIES CXX_STANDARD 14)
set_target_properties(tb_test PROPERTIES LINKER_LANGUAGE CXX)    
add_executable(run_tests run_tests.cpp)

target_link_libraries(run_tests tb_lib)
target_link_libraries(run_tests tb_test)
target_link_libraries(run_tests $ENV{GTEST_LIB_DIR}/libgtest.a)
target_link_libraries(run_tests $ENV{LUA_LIB_DIR}/liblua5.3.a)
target_link_libraries(run_tests $ENV{PROTOBUF_LIB_DIR}/libprotobuf.a)
target_link_libraries(run_tests $ENV{STD_EXPERIMENTAL_LIB}/libstdc++fs.a)
target_link_libraries(run_tests ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(run_tests ${CMAKE_DL_LIBS})
target_link_libraries(run_tests ${CMAKE_THREAD_LIBS_INIT})

set_property(TARGET run_tests PROPERTY CXX_STANDARD 14)

add_test(NAME ThunderBiscuitTests COMMAND run_tests)




