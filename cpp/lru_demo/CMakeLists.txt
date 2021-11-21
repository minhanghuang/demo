cmake_minimum_required(VERSION 3.19)
project(lru_demo)

set(CMAKE_CXX_STANDARD 14)

set(TARGET_NAME ${PROJECT_NAME})

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)

aux_source_directory(src DEMO_SOURCE_DIRS)

add_library(${TARGET_NAME} SHARED
    ${DEMO_SOURCE_DIRS}
)

add_executable(${TARGET_NAME}_runner main.cc)

target_link_libraries(${TARGET_NAME}_runner
    ${TARGET_NAME}
)
