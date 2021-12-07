cmake_minimum_required(VERSION 3.19)
project(gtest_demo)

set(CMAKE_CXX_STANDARD 14)
set(TARGET_NAME ${PROJECT_NAME})

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(Gtest REQUIRED gtest)


include_directories(
    ${Gtest_INCLUDE_DIRS}
)

link_directories (
    ${Gtest_LIBRARY_DIRS}
)

add_library(${TARGET_NAME} SHARED
    src/env.cc
    src/test_1.cc
)

target_link_libraries(${TARGET_NAME}
    ${Gtest_LIBRARIES}
)

add_executable(${TARGET_NAME}_runner main.cpp)

target_link_libraries(${TARGET_NAME}_runner
    ${TARGET_NAME}
)
