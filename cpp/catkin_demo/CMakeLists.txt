cmake_minimum_required(VERSION 3.5)
project(catkin_demo)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread filesystem)
pkg_check_modules(ROSCPP roscpp)
pkg_check_modules(STD_MSGS std_msgs)
find_package(catkin)

include_directories(
    /opt/ros/kinetic/include
    ${Boost_INCLUDE_DIRS}
    ${catkin_INCLUDE_DIRS}
    ${ROSCPP_INCLUDE_DIRS}
    ${STD_MSGS_INCLUDE_DIRS}
)

catkin_package()

link_directories (
    ${Boost_LIBRARY_DIRS}
    ${ROSCPP_LIBRARY_DIRS}
)

add_executable(${TARGET_NAME} main.cpp)

target_link_libraries(${TARGET_NAME}
    ${Boost_LIBRARIES}
    ${ROSCPP_LIBRARIES}
)

install(TARGETS ${TARGET_NAME}
    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

file(COPY conf launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

message("CATKIN_PACKAGE_SHARE_DESTINATION: "${CATKIN_PACKAGE_SHARE_DESTINATION}) # share/catkin_demo
message("CATKIN_PACKAGE_LIB_DESTINATION: "${CATKIN_PACKAGE_LIB_DESTINATION}) # lib
message("CATKIN_PACKAGE_BIN_DESTINATION: "${CATKIN_PACKAGE_BIN_DESTINATION}) # lib/catkin_demo
message("CMAKE_BINARY_DIR: "${CMAKE_BINARY_DIR}) # /home/trunk/work/code/macos/demo/cpp/cat/src/catkin_demo/build