cmake_minimum_required(VERSION 3.5.1)
project(ros_pubsub_demo)

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

link_directories (
  ${RosCpp_LIBRARY_DIRS}
)

add_executable(sub sub.cc)
add_executable(pub pub.cc)

target_link_libraries(pub
  ${RosCpp_LIBRARIES}
)
target_link_libraries(sub
  ${RosCpp_LIBRARIES}
)
