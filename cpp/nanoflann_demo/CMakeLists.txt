cmake_minimum_required(VERSION 3.5.1)
project(nanoflann_demo VERSION 0.0.0)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)

include_directories(include)


add_executable(${TARGET_NAME}_runner main.cc)
