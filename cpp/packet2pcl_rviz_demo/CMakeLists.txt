cmake_minimum_required(VERSION 3.19)
project(packet2pcl_rviz_demo)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread filesystem)
find_package(PCL REQUIRED)
pkg_check_modules(YamlCpp REQUIRED yaml-cpp)
pkg_check_modules(Roscpp roscpp)
pkg_check_modules(SensorMsgs sensor_msgs)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${Roscpp_INCLUDE_DIRS}
    ${PCL_INCLUDE_DIRS}
    ${SensorMsgs_INCLUDE_DIRS}
    ${YamlCpp_INCLUDE_DIRS}
    /opt/tmaps/include
)

link_directories (
    ${Boost_LIBRARY_DIRS}
    ${Roscpp_LIBRARY_DIRS}
    ${PCL_LIBRARY_DIRS}
    ${YamlCpp_LIBRARY_DIRS}
)

add_library(${TARGET_NAME} SHARED
    src/transform.cc
)

target_link_libraries(${TARGET_NAME}
    ${Boost_LIBRARIES}
    ${Roscpp_LIBRARIES}
    ${PCL_LIBRARIES}
    ${YamlCpp_LIBRARIES}
)

add_executable(${TARGET_NAME}_runner main.cpp)

target_link_libraries(${TARGET_NAME}_runner
    ${TARGET_NAME}
)

file(COPY conf/VLP-32C.yaml DESTINATION ${CMAKE_BINARY_DIR}/conf)

