cmake_minimum_required(VERSION 3.5.1)
project(ptr VERSION 0.0.0)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${TARGET_NAME}_runner main.cc)

