cmake_minimum_required(VERSION 3.18)
project(grpc_demo)
set(TARGET_NAME ${PROJECT_NAME})


set(CMAKE_CXX_STANDARD 14)
find_package(PkgConfig REQUIRED)
find_package(Protobuf REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)
pkg_check_modules(GRPCPP REQUIRED grpc++)


include_directories(
    proto
    ${Boost_INCLUDE_DIRS}
    ${Protobuf_INCLUDE_DIRS}
    ${GRPCPP_INCLUDE_DIRS}
)

link_directories (
    ${Boost_LIBRARY_DIRS}
    ${Protobuf_LIBRARY_DIRS}
    ${GRPCPP_LIBRARY_DIRS}
)

aux_source_directory(proto PROTO_SOURCE_DIRS)

add_library(${TARGET_NAME} SHARED
    ${PROTO_SOURCE_DIRS}
)

target_link_libraries(${TARGET_NAME}
    ${Boost_LIBRARIES}
    ${Protobuf_LIBRARIES}
    ${GRPCPP_LIBRARIES}
)

add_executable(simple_server simple/server.cc)
add_executable(simple_client simple/client.cc)


target_link_libraries(simple_server
    ${TARGET_NAME}
)
target_link_libraries(simple_client
    ${TARGET_NAME}
)
