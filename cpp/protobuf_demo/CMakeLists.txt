cmake_minimum_required(VERSION 3.5.1)
project(protobuf_demo VERSION 0.0.0)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Protobuf REQUIRED)

include_directories(
  ${Protobuf_INCLUDE_DIRS}
)

link_directories (
  ${Protobuf_LIBRARY_DIRS}
)

file(GLOB PROTO_SOURCE
  "proto/*.cc"
)

add_executable(${TARGET_NAME}_runner
  main.cc
  ${PROTO_SOURCE}
)

target_link_libraries(${TARGET_NAME}_runner
  ${Protobuf_LIBRARIES}
)
