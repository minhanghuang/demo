cmake_minimum_required(VERSION 3.19)
project(libunwind_demo)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread filesystem)

include_directories(
    ${Boost_INCLUDE_DIRS}
)

link_directories (
    ${Boost_LIBRARY_DIRS}
)

add_library(${TARGET_NAME} SHARED
    src/symbolize.cc
    src/demangle.cc
)

target_link_libraries(${TARGET_NAME}
    ${Boost_LIBRARIES}
)

add_executable(${TARGET_NAME}_runner main.cpp)

target_link_libraries(${TARGET_NAME}_runner
    ${TARGET_NAME}
)