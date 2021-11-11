cmake_minimum_required(VERSION 3.17)
project(thread_demo)

set(CMAKE_CXX_STANDARD 14)
set(TARGET_NAME ${PROJECT_NAME})

find_package(PkgConfig REQUIRED)
find_package (Boost REQUIRED COMPONENTS system thread)

include_directories(
    ${Boost_INCLUDE_DIRS}
)
link_directories (
    ${Boost_LIBRARY_DIRS}
)

aux_source_directory(src THREAD_SOURCE_DIRS)

add_library(${TARGET_NAME} SHARED
    ${THREAD_SOURCE_DIRS}
)

target_link_libraries(${TARGET_NAME}
    ${Boost_LIBRARIES}
)

add_executable(${TARGET_NAME}_runner main.cc)

target_link_libraries(${TARGET_NAME}_runner
    ${TARGET_NAME}
)
