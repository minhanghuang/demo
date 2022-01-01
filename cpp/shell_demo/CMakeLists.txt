cmake_minimum_required(VERSION 3.19)
project(shell_demo)

set(CMAKE_CXX_STANDARD 14)
set(TARGET_NAME ${PROJECT_NAME})

add_executable(${TARGET_NAME}_runner main.cpp)

