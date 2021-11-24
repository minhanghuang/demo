cmake_minimum_required(VERSION 3.19)
project(udp_demo)

set(CMAKE_CXX_STANDARD 14)
set(TARGET_NAME ${PROJECT_NAME})

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)

include_directories(
    ${Boost_INCLUDE_DIRS}
)

link_directories (
    ${Boost_LIBRARY_DIRS}
)

add_executable(server server.cc)
add_executable(client client.cc)

target_link_libraries(server
    ${Boost_LIBRARIES}
)
target_link_libraries(client
    ${Boost_LIBRARIES}
)