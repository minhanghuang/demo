cmake_minimum_required(VERSION 3.5.1)
project(core_dump)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE DEBUG)

add_executable(${TARGET_NAME}_runner main.cc)

