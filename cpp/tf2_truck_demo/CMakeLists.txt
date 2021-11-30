cmake_minimum_required(VERSION 3.5)
project(tf2_truck_demo)
set(TARGET_NAME ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread filesystem)
pkg_check_modules(ROSCPP roscpp)
pkg_check_modules(HADMAP_MSGS hadmap_msgs)
pkg_check_modules(LOCALIZATION_MSGS localization_msgs)
pkg_check_modules(TF2_GEOMETRY_MSGS tf2_geometry_msgs)
pkg_check_modules(GEOMETRY_MSGS geometry_msgs)
pkg_check_modules(TF2_MSGS tf2_msgs)
pkg_check_modules(TF2 tf2)

include_directories(
    /opt/trunk/include
    /opt/ros/kinetic/include
    ${ROSCPP_INCLUDE_DIRS}
    ${HADMAP_MSGS_INCLUDE_DIRS}
    ${LOCALIZATION_MSGS_INCLUDE_DIRS}
    ${TF2_GEOMETRY_MSGS_INCLUDE_DIRS}
    ${GEOMETRY_MSGS_INCLUDE_DIRS}
    ${TF2_MSGS_INCLUDE_DIRS}
    ${TF2_INCLUDE_DIRS}
)

link_directories (
    ${Boost_LIBRARY_DIRS}
    ${ROSCPP_LIBRARY_DIRS}
    ${TF2_LIBRARY_DIRS}
)

add_executable(${TARGET_NAME}_runner main.cpp)

target_link_libraries(${TARGET_NAME}_runner
    ${ROSCPP_LIBRARIES}
    ${TF2_LIBRARIES}
)