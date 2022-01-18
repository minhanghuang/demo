cmake_minimum_required(VERSION 3.5)
project(py_build_demo)

set(CMAKE_CXX_STANDARD 14)

execute_process(COMMAND mkdir yyy
        OUTPUT_VARIABLE ls_ret)
message(STATUS "ls output:\n${ls_ret}")

add_executable(py_build_demo main.cpp)

