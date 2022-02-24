cmake_minimum_required(VERSION 3.5)
project(backtrace_demo)

set(CMAKE_CXX_STANDARD 14)
set(TARGET_NAME ${PROJECT_NAME})

add_definitions("-Wall -g")

add_library(${TARGET_NAME} SHARED
    src/stacktrace.cc
)

add_executable(${TARGET_NAME}_runner main.cpp)

target_link_libraries(${TARGET_NAME}_runner
    ${TARGET_NAME}
    bfd
    iberty
)
