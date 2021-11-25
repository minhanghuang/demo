cmake_minimum_required(VERSION 3.5)
project(tf2_demo)

set(CMAKE_CXX_STANDARD 14)
set(TARGET_NAME ${PROJECT_NAME})

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GEOMETRY_MSGS geometry_msgs)
pkg_check_modules(TF2_GEOMETRY_MSGS tf2_geometry_msgs)
pkg_check_modules(TF2 tf2)

include_directories(
    /opt/trunk/include
    /opt/ros/kinetic/include
    ${GEOMETRY_MSGS_INCLUDE_DIRS}
    ${TF2_GEOMETRY_MSGS_INCLUDE_DIRS}
    ${ROSCPP_INCLUDE_DIRS}
    ${TF2_INCLUDE_DIRS}
)

link_directories (
    ${TF2_LIBRARY_DIRS}
)

add_executable(${TARGET_NAME} main.cc)

target_link_libraries(${TARGET_NAME}
    ${TF2_LIBRARIES}
)