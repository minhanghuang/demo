cmake_minimum_required(VERSION 3.19)
project(btree_demo)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)

add_library(${TARGET_NAME} SHARED
    src/btree.cc
)

add_executable(${TARGET_NAME}_runner main.cc)

target_link_libraries(${TARGET_NAME}_runner
    ${TARGET_NAME}
)