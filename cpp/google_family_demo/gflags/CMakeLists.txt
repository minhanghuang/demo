cmake_minimum_required(VERSION 3.5.1)

project(gflags_demo)

set(TARGET_NAME ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(Glog REQUIRED gflags)

include_directories(
  ${Glog_INCLUDE_DIRS}
)

link_directories (
  ${Glog_LIBRARY_DIRS}
)

add_executable(${TARGET_NAME}_runner main.cc)

target_link_libraries(${TARGET_NAME}_runner
  ${Glog_LIBRARIES}
)
