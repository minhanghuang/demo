cmake_minimum_required(VERSION 3.5)
project(znode_demo)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)

find_package(Protobuf REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)
pkg_check_modules(Trunk_msgs trunk_msgs)
pkg_check_modules(Cater_node cater_node)

include_directories(
    /opt/trunk30/include
    ${Boost_INCLUDE_DIRS}
    ${Protobuf_INCLUDE_DIRS}
    ${Trunk_msgs_INCLUDE_DIRS}
    ${Cater_node_INCLUDE_DIRS}
)

link_directories(
    ${Boost_LIBRARY_DIRS}
    ${Protobuf_LIBRARY_DIRS}
    ${Trunk_msgs_LIBRARY_DIRS}
    ${Cater_node_LIBRARY_DIRS}
)

add_executable(${TARGET_NAME}_pub pub.cc)
add_executable(${TARGET_NAME}_sub sub.cc)

target_link_libraries(${TARGET_NAME}_pub
    libzmq.so
    ${Boost_LIBRARIES}
    ${Protobuf_LIBRARIES}
    ${Trunk_msgs_LIBRARIES}
    ${Cater_node_LIBRARIES}
)

target_link_libraries(${TARGET_NAME}_sub
    libzmq.so
    ${Boost_LIBRARIES}
    ${Protobuf_LIBRARIES}
    ${Trunk_msgs_LIBRARIES}
    ${Cater_node_LIBRARIES}
)

