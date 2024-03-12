cmake_minimum_required(VERSION 3.5.1)
project(cat VERSION 0.0.0)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_SHARED_LIBS ON)

add_library(${TARGET_NAME} main.cc)

