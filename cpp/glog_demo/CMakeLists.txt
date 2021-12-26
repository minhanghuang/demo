cmake_minimum_required(VERSION 3.19)
project(glog_demo)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread filesystem)
pkg_check_modules(Glog REQUIRED libglog)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${Glog_INCLUDE_DIRS}
)

link_directories (
    ${Boost_LIBRARY_DIRS}
    ${Glog_LIBRARY_DIRS}
)

aux_source_directory(utils LOGSRC)

add_library(${TARGET_NAME} SHARED
    ${LOGSRC}
)

target_link_libraries(${TARGET_NAME}
    ${Boost_LIBRARIES}
    ${Glog_LIBRARIES}
)

add_executable(${TARGET_NAME}_runner main.cpp)

target_link_libraries(${TARGET_NAME}_runner
    ${TARGET_NAME}
)