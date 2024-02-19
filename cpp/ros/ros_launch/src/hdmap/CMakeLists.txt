cmake_minimum_required(VERSION 3.0.2)
project(hdmap)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED)
find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(ROSCPP roscpp)
pkg_check_modules(STD_MSGS std_msgs)

include_directories(
    ${ROSCPP_INCLUDE_DIRS}
    ${STD_MSGS_INCLUDE_DIRS}
)

link_directories (
    ${ROSCPP_LIBRARY_DIRS}
)

catkin_package()

add_executable(pub main.cc)

target_link_libraries(pub
    ${ROSCPP_LIBRARIES}
)
