cmake_minimum_required(VERSION 3.5)
project(quart2rpy)

set(CMAKE_CXX_STANDARD 14)
find_package(PkgConfig REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
pkg_check_modules(Roscpp REQUIRED roscpp)
pkg_check_modules(Tf REQUIRED tf)


include_directories(
    ${Boost_INCLUDE_DIRS}
    ${Roscpp_INCLUDE_DIRS}
    ${Tf_INCLUDE_DIRS}
)

link_directories(
    ${Boost_LIBRARY_DIRS}
    ${Roscpp_LIBRARY_DIRS}
    ${Tf_LIBRARY_DIRS}
)

add_executable(quart2rpy main.cpp)

target_link_libraries(quart2rpy
    ${Boost_LIBRARIES}
    ${Roscpp_LIBRARIES}
)
