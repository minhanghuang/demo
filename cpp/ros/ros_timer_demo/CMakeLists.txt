cmake_minimum_required(VERSION 3.5.1)
project(ros_timer_demo)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(RosCpp REQUIRED roscpp)
pkg_check_modules(StdMsgs REQUIRED std_msgs)

include_directories(
  ${RosCpp_INCLUDE_DIRS}
  ${StdMsgs_INCLUDE_DIRS}
)

link_directories(
  ${RosCpp_LIBRARY_DIRS}
)

add_executable(${PROJECT_NAME} main.cc)

target_link_libraries(${PROJECT_NAME}
  ${RosCpp_LIBRARIES}
)
