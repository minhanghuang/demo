cmake_minimum_required(VERSION 3.5)
project(protobuf_demo)

set(TARGET_NAME ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)
find_package(PkgConfig REQUIRED)
find_package(Protobuf REQUIRED)

include_directories(
    ${Protobuf_INCLUDE_DIRS}
)

link_directories (
    ${Protobuf_LIBRARY_DIRS}
)

aux_source_directory(src PROTOSRC)

add_library(${TARGET_NAME} SHARED
    ${PROTOSRC}
)

target_link_libraries(${TARGET_NAME}
    ${Protobuf_LIBRARIES}
)

add_executable(${TARGET_NAME}_runner main.cc)

target_link_libraries(${TARGET_NAME}_runner
    ${TARGET_NAME}
)