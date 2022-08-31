cmake_minimum_required(VERSION 3.5.1)
project(flann_demo VERSION 0.0.0)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(Flann REQUIRED flann)
pkg_check_modules(LZ4 REQUIRED liblz4)

include_directories(
  ${Flann_INCLUDE_DIRS}
  ${LZ4_INCLUDE_DIRS}
)

link_directories (
  ${Flann_LIBRARY_DIRS}
  ${LZ4_LIBRARY_DIRS}
)

add_executable(${TARGET_NAME}_runner main.cc)

target_link_libraries(${TARGET_NAME}_runner
  ${Flann_LIBRARIES}
  ${LZ4_LIBRARIES}
)
