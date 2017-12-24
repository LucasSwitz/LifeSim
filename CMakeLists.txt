cmake_minimum_required(VERSION 2.6)
PROJECT(ThunderBiscuit)
find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(Lua51 REQUIRED)
find_package(Protobuf REQUIRED)

set(CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED network audio graphics window system)

include_directories(${LUA_INCLUDE_DIR} ".")

include_directories($ENV{LUA_BRIDGE_INCLUDE} ".")
include_directories($ENV{IMGUI_INCLUDE_DIR} ".")
include_directories($ENV{IMGUI_SFML_INCLUDE_DIR} ".")
include_directories(${PROTOBUF_INCLUDE_DIRS} ".")
include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES
    src/*.h
    src/*.cpp
    src/*.cc)

add_library(tb_lib ${SOURCES})
set_target_properties(tb_lib PROPERTIES CXX_STANDARD 14)
add_executable(editor run_editor.cpp)
target_link_libraries(editor
    tb_lib
    ${LUA_LIBRARIES}
    ${PROTOBUF_LIBRARIES}
    ${OPENGL_LIBRARIES} 
    ${GLUT_LIBRARY}
    ${CMAKE_DL_LIBS}
    ${CMAKE_THREAD_LIBS_INIT}
    $ENV{STD_EXPERIMENTAL_LIB}/libstdc++fs.a
    $ENV{GTEST_LIB_DIR}/libgtest.a
)

if(SFML_FOUND)
  target_link_libraries(editor ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

set_property(TARGET editor PROPERTY CXX_STANDARD 17)

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
    
##TESTS
enable_testing()

file(GLOB_RECURSE TEST_SOURCES
    test/*.h
    test/*.cpp
    test/*.cc)
    

add_subdirectory($ENV{GTEST_DIR})
include_directories($ENV{GTEST_DIR}/include ".")

add_library(tb_test ${TEST_SOURCES})
set_target_properties(tb_test PROPERTIES CXX_STANDARD 17)
set_target_properties(tb_test PROPERTIES LINKER_LANGUAGE CXX)    
add_executable(run_tests run_tests.cpp)


target_link_libraries(run_tests
    tb_lib
    tb_test
    ${LUA_LIBRARIES}
    ${PROTOBUF_LIBRARIES}
    ${OPENGL_LIBRARIES} ${GLUT_LIBRARY}
    ${CMAKE_DL_LIBS}
    ${CMAKE_THREAD_LIBS_INIT}
    $ENV{STD_EXPERIMENTAL_LIB}/libstdc++fs.a
    $ENV{GTEST_LIB_DIR}/libgtest.a
)

if(SFML_FOUND)
    target_link_libraries(run_tests ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

set_property(TARGET run_tests PROPERTY CXX_STANDARD 17)

add_test(NAME ThunderBiscuitTests COMMAND run_tests)




