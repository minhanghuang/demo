cmake_minimum_required(VERSION 3.5.1)
project(python_demo VERSION 0.0.0)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Python3 COMPONENTS Interpreter Development)

# https://cmake.org/cmake/help/latest/module/FindPython3.html

message(STATUS "python version: ${Python3_VERSION}")
message(STATUS "python include dirs: ${Python3_INCLUDE_DIRS}")
message(STATUS "python libraries dirs: ${Python3_LIBRARY_DIRS}")
message(STATUS "python libraries: ${Python3_LIBRARIES}")

include_directories(
  ${Python_INCLUDE_DIRS}
)

link_directories(
  ${Python_LIBRARIES_DIRS}
)

add_executable(${TARGET_NAME}_runner main.cc)

target_link_libraries(${TARGET_NAME}_runner
  ${Python_LIBRARIES}
)
