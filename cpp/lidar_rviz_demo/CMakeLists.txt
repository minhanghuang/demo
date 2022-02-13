cmake_minimum_required(VERSION 3.19)
project(lidar_rviz_demo)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread filesystem)
find_package(PCL REQUIRED)
pkg_check_modules(Roscpp roscpp)
pkg_check_modules(SensorMsgs sensor_msgs)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${Roscpp_INCLUDE_DIRS}
    ${PCL_INCLUDE_DIRS}
    ${SensorMsgs_INCLUDE_DIRS}
)

link_directories (
    ${Boost_LIBRARY_DIRS}
    ${Roscpp_LIBRARY_DIRS}
    ${PCL_LIBRARY_DIRS}
)

add_executable(${TARGET_NAME}_runner main.cpp)

target_link_libraries(${TARGET_NAME}_runner
    ${Boost_LIBRARIES}
    ${Roscpp_LIBRARIES}
    ${PclRos_LIBRARIES}
)
