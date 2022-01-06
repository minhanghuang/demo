cmake_minimum_required(VERSION 3.5.1)
project(ros_bag_demo)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread filesystem)
pkg_check_modules(ROSCPP roscpp)
pkg_check_modules(ROSBAG rosbag)
pkg_check_modules(STD_MSGS std_msgs)

include_directories(
    /opt/ros/kinetic/include
    ${ROSCPP_INCLUDE_DIRS}
    ${ROSBAG_INCLUDE_DIRS}
    ${ADS_MSGS_INCLUDE_DIRS}
)

link_directories (
    ${ROSCPP_LIBRARY_DIRS}
    ${ROSBAG_LIBRARY_DIRS}
)

add_executable(${TARGET_NAME}_runner main.cpp)

target_link_libraries(${TARGET_NAME}_runner
    ${Boost_LIBRARIES}
    ${ROSCPP_LIBRARIES}
    ${ROSBAG_LIBRARIES}
)


