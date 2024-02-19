cmake_minimum_required(VERSION 3.5.1)
project(ros_service_demo)

set(CMAKE_CXX_STANDARD 14)
set(TARGET_NAME ${PROJECT_NAME})

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(ROSCPP roscpp)
pkg_check_modules(STD_MSGS std_msgs)

include_directories(
    ${ROSCPP_INCLUDE_DIRS}
    ${ADS_MSGS_INCLUDE_DIRS}
)

link_directories (
    ${ROSCPP_LIBRARY_DIRS}
)

add_executable(server server.cc)
add_executable(client client.cc)

target_link_libraries(server
    ${ROSCPP_LIBRARIES}
)
target_link_libraries(client
    ${ROSCPP_LIBRARIES}
)

