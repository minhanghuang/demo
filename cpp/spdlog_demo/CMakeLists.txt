cmake_minimum_required(VERSION 3.5)
project(spdlog_demo)

set(TARGET_NAME ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)
find_package(PkgConfig REQUIRED)
pkg_check_modules(Spdlog REQUIRED spdlog)

include_directories(
    ${Spdlog_INCLUDE_DIRS}
)

link_directories(
    ${Spdlog_LIBRARY_DIRS}
)

add_library(${TARGET_NAME} SHARED
    src/log.cc
)

target_link_libraries(${TARGET_NAME}
    ${Spdlog_LIBRARIES}
)

add_executable(${TARGET_NAME}_runer main.cpp)

target_link_libraries(${TARGET_NAME}_runer
    ${TARGET_NAME}
)
