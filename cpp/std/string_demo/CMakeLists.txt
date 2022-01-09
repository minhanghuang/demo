cmake_minimum_required(VERSION 3.19)
project(string_demo)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)

add_executable(${TARGET_NAME}_runner main.cpp)
