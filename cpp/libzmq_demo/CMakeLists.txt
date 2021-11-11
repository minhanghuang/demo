cmake_minimum_required(VERSION 3.17)
project(libzmq_demo)

set(CMAKE_CXX_STANDARD 14)
set(TARGET_NAME ${PROJECT_NAME})

find_package(PkgConfig REQUIRED)
find_package(Protobuf REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)
pkg_check_modules(LIBZMQ REQUIRED libzmq)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${LIBZMQ_INCLUDE_DIRS}
)

link_directories (
    ${Boost_LIBRARY_DIRS}
    ${LIBZMQ_LIBRARY_DIRS}
)

add_executable(simple_server simple/server.cc)
add_executable(simple_client simple/client.cc)

target_link_libraries(simple_server
    ${Boost_LIBRARIES}
    ${LIBZMQ_LIBRARIES}
    )
target_link_libraries(simple_client
    ${Boost_LIBRARIES}
    ${LIBZMQ_LIBRARIES}
    )
