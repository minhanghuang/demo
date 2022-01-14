cmake_minimum_required(VERSION 3.5)
project(velodyne_demo)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread filesystem)
find_package(PCL REQUIRED)
pkg_check_modules(Roscpp roscpp)
pkg_check_modules(Rosbag rosbag)
pkg_check_modules(TmapsMsg tmaps_msg)

include_directories(
#    /opt/ros/melodic/include
    /opt/ros/kinetic/include
    /opt/tmaps/include
    ${Boost_INCLUDE_DIRS}
    ${Roscpp_INCLUDE_DIRS}
    ${Rosbag_INCLUDE_DIRS}
    ${PCL_INCLUDE_DIRS}
    ${TmapsMsg_INCLUDE_DIRS}
)

link_directories (
    ${Boost_LIBRARY_DIRS}
    ${Roscpp_LIBRARY_DIRS}
    ${Rosbag_LIBRARY_DIRS}
    ${PCL_LIBRARY_DIRS}
)

add_executable(${TARGET_NAME}_runner main.cpp)

target_link_libraries(${TARGET_NAME}_runner
    ${Boost_LIBRARIES}
    ${Roscpp_LIBRARIES}
    ${Rosbag_LIBRARIES}
    ${PclRos_LIBRARIES}
)