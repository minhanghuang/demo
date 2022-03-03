cmake_minimum_required(VERSION 3.5)
project(backtrace_demo)

set(CMAKE_CXX_STANDARD 14)
set(TARGET_NAME ${PROJECT_NAME})

add_definitions("-Wall -g")

add_executable(${TARGET_NAME}_runner main.cc)

