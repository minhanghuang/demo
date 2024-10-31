cmake_minimum_required(VERSION 3.5.1)
project(alpaca_demo VERSION 0.0.0)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(Alpaca REQUIRED alpaca)

include_directories(
  ${Alpaca_INCLUDE_DIRS}
)

add_executable(${TARGET_NAME}_runner main.cc)
